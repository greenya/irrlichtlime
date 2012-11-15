using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Scene;
using IrrlichtLime.Video;
using System.Diagnostics;
using System.Threading;

namespace L15.AbstractTrace
{
	class AbstractTrace
	{
		public const int GridDim = 500; // defines size of the grid: GridDim x GridDim; if we would place cube into each cell, that would be also cube count for single grid (but actual cube count is much much less)
		public const int GridLayerCount = 200; // defines trace length and total number of distinct meshes
		public const float CubeSize = 10;
		private const int maxCubesPerBuffer = 3600; // maximum is 65536 div 8 (where 8 is number of vertices per cube); we could pick 8000+ and reduce number of meshbuffers, but on some video cards fully loaded meshbuffers works much slower

		int[,] grid = new int[GridDim, GridDim]; // actual state of the grid
		int[,] gridPrev = new int[GridDim, GridDim]; // previous state of the grid; needed for generating Conway's Game of Life algorithm (see implementation in meshGeneratorThread_generateGrid())
		int gridCubeCount = 0; // here we store number of "1"s in grid array; we count them while generating next step and cache this value, so we don't need to calc again when needed
		int gridGeneration = 0; // actual generation of the grid; this number increases each time grid regenerates in meshGeneratorThread_generateGrid(); we use this value when picking next free GridLayer in Step()

		Color cubeColor = new Color(50, 150, 250, 25); // color of the cubes; we could change it over time giving nice transitions; we even can give each single cube different color: if you want to implement this - simply add color to Vertex3D constructors and remove SetVertexColors() call of MeshManipulator at the end of mesh generation in meshGeneratorThread_generateMesh()
		Material cubeMaterial = new Material(); // material used to draw all grid layers; if you want separate material for each GridLayer - simple move this material definition inside GridLayer class and use that value in Draw() for each GridLayer

		IrrlichtDevice device;
		GridLayer[] layers = new GridLayer[GridLayerCount];

		Thread meshGeneratorThread = null;

		public AbstractTrace(IrrlichtDevice device)
		{
			this.device = device;
			device.Grab();

			cubeMaterial.Type = MaterialType.TransparentVertexAlpha;
			cubeMaterial.Lighting = false;

			for (int i = 0; i < layers.Length; i++)
				layers[i] = new GridLayer();
		}

		public void Init()
		{
			gridGeneration = 0;
			gridCubeCount = 0;

			Random r = new Random();
			for (int i = 0; i < GridDim; i++)
			{
				for (int j = 0; j < GridDim; j++)
				{
					if (r.Next(100) < 50)
					{
						grid[i, j] = 1;
						gridCubeCount++;
					}
					else
					{
						grid[i, j] = 0;
					}
				}
			}
		}

		public void Step()
		{
			if (meshGeneratorThread != null)
				return;

			meshGeneratorThread = new System.Threading.Thread(new ParameterizedThreadStart(delegate(object i)
			{
				meshGeneratorThread_generateGrid();
				meshGeneratorThread_generateMesh((int)i);
				meshGeneratorThread = null;
			}));

			// search for layer with oldest generation

			int gmin = int.MaxValue;
			int igmin = -1;

			for (int i = 0; i < layers.Length; i++)
			{
				if (layers[i].Generation < gmin)
				{
					gmin = layers[i].Generation;
					igmin = i;
				}
			}

			// start mesh generation

			layers[igmin].MeshIsReady = false;
			meshGeneratorThread.Start(igmin);
		}

		private void meshGeneratorThread_generateGrid()
		{
			gridGeneration++;
			gridCubeCount = 0;

			int[,] t = grid;
			grid = gridPrev;
			gridPrev = t;

			// process grid with Conway's Game of Life algorithm (details: http://en.wikipedia.org/wiki/Conway's_Game_of_Life)

			for (int i = 0; i < GridDim; i++)
			{
				for (int j = 0; j < GridDim; j++)
				{
					// calc number of neighbours

					int n = 0;

					int il = i > 0 ? i - 1 : GridDim - 1;
					int ir = i < GridDim - 1 ? i + 1 : 0;
					int jt = j > 0 ? j - 1 : GridDim - 1;
					int jb = j < GridDim - 1 ? j + 1 : 0;

					if (gridPrev[il, j] == 1) n++; // left
					if (gridPrev[ir, j] == 1) n++; // right

					if (gridPrev[i, jt] == 1) n++; // top
					if (gridPrev[i, jb] == 1) n++; // bottom

					if (gridPrev[il, jt] == 1) n++; // left-top
					if (gridPrev[il, jb] == 1) n++; // left-bottom

					if (gridPrev[ir, jt] == 1) n++; // right-top
					if (gridPrev[ir, jb] == 1) n++; // right-bottom

					// update cell

					if ((n == 2 && gridPrev[i, j] == 1) ||
						(n == 3 && gridPrev[i, j] == 0))
					{
						grid[i, j] = 1;
						gridCubeCount++;
					}
					else
					{
						grid[i, j] = 0;
					}
				}
			}
		}

		private void meshGeneratorThread_generateMesh(int layerIndex)
		{
			GridLayer l = layers[layerIndex];

			if (l.Mesh != null)
				l.Mesh.Drop();

			l.Mesh = Mesh.Create();

			if (gridCubeCount > 0)
			{
				Vertex3D[] cubeVerts = null;
				ushort[] cubeInds = null;
				int cubeIndex = maxCubesPerBuffer; // this way we force buffers to be recreated at next new cube
				int totalCubesAdded = 0;

				float baseX = -(CubeSize * GridDim) / 2;
				float baseZ = -(CubeSize * GridDim) / 2;

				for (int i = 0; i < GridDim; i++)
				{
					for (int j = 0; j < GridDim; j++)
					{
						if (grid[i, j] == 0)
							continue;

						// check if current buffer is out of room, if so make a mesh buffer and attach it to the gridMesh and init next cubeVerts&Inds

						if (cubeIndex == maxCubesPerBuffer)
						{
							if (cubeVerts != null && cubeInds != null)
							{
								MeshBuffer b = MeshBuffer.Create(VertexType.Standard, IndexType._16Bit);
								b.Append(cubeVerts, cubeInds);
								l.Mesh.AddMeshBuffer(b);
								b.Drop();

								totalCubesAdded += cubeIndex;
							}

							int cubeCount = gridCubeCount - totalCubesAdded;
							if (cubeCount > maxCubesPerBuffer)
								cubeCount = maxCubesPerBuffer;

							cubeIndex = 0;
							cubeVerts = new Vertex3D[cubeCount * 8]; // 8 verts per cube
							cubeInds = new ushort[cubeCount * 3 * 2 * 6]; // 3 indices per triangle; 2 triangles per face; 6 faces per cube
						}

						// build the cube and add it
						// note: we build 8 vertices cube because we don't need to texture it; if you want to change that (to use texture instead of vertex colors) - you need to build 12 vertices cube and initialize UV coords

						float x = baseX + i * CubeSize;
						float y = 0;
						float z = baseZ + j * CubeSize;
						int iv = cubeIndex * 8;

						cubeVerts[iv + 0] = new Vertex3D(x, y, z);
						cubeVerts[iv + 1] = new Vertex3D(x + CubeSize, y, z);
						cubeVerts[iv + 2] = new Vertex3D(x + CubeSize, y + CubeSize, z);
						cubeVerts[iv + 3] = new Vertex3D(x, y + CubeSize, z);
						cubeVerts[iv + 4] = new Vertex3D(x, y, z + CubeSize);
						cubeVerts[iv + 5] = new Vertex3D(x + CubeSize, y, z + CubeSize);
						cubeVerts[iv + 6] = new Vertex3D(x + CubeSize, y + CubeSize, z + CubeSize);
						cubeVerts[iv + 7] = new Vertex3D(x, y + CubeSize, z + CubeSize);

						int ii = cubeIndex * 3 * 2 * 6;

						// top
						cubeInds[ii + 0] = (ushort)(iv + 3);
						cubeInds[ii + 1] = (ushort)(iv + 7);
						cubeInds[ii + 2] = (ushort)(iv + 6);
						cubeInds[ii + 3] = (ushort)(iv + 3);
						cubeInds[ii + 4] = (ushort)(iv + 6);
						cubeInds[ii + 5] = (ushort)(iv + 2);

						// front
						cubeInds[ii + 6] = (ushort)(iv + 0);
						cubeInds[ii + 7] = (ushort)(iv + 3);
						cubeInds[ii + 8] = (ushort)(iv + 2);
						cubeInds[ii + 9] = (ushort)(iv + 0);
						cubeInds[ii + 10] = (ushort)(iv + 2);
						cubeInds[ii + 11] = (ushort)(iv + 1);

						// right
						cubeInds[ii + 12] = (ushort)(iv + 1);
						cubeInds[ii + 13] = (ushort)(iv + 2);
						cubeInds[ii + 14] = (ushort)(iv + 6);
						cubeInds[ii + 15] = (ushort)(iv + 1);
						cubeInds[ii + 16] = (ushort)(iv + 6);
						cubeInds[ii + 17] = (ushort)(iv + 5);

						// left
						cubeInds[ii + 18] = (ushort)(iv + 0);
						cubeInds[ii + 19] = (ushort)(iv + 4);
						cubeInds[ii + 20] = (ushort)(iv + 7);
						cubeInds[ii + 21] = (ushort)(iv + 0);
						cubeInds[ii + 22] = (ushort)(iv + 7);
						cubeInds[ii + 23] = (ushort)(iv + 3);

						// back
						cubeInds[ii + 24] = (ushort)(iv + 4);
						cubeInds[ii + 25] = (ushort)(iv + 5);
						cubeInds[ii + 26] = (ushort)(iv + 6);
						cubeInds[ii + 27] = (ushort)(iv + 4);
						cubeInds[ii + 28] = (ushort)(iv + 6);
						cubeInds[ii + 29] = (ushort)(iv + 7);

						// bottom
						cubeInds[ii + 30] = (ushort)(iv + 0);
						cubeInds[ii + 31] = (ushort)(iv + 1);
						cubeInds[ii + 32] = (ushort)(iv + 5);
						cubeInds[ii + 33] = (ushort)(iv + 0);
						cubeInds[ii + 34] = (ushort)(iv + 5);
						cubeInds[ii + 35] = (ushort)(iv + 4);

						cubeIndex++;
					}
				}

				if (cubeIndex > 0)
				{
					MeshBuffer b = MeshBuffer.Create(VertexType.Standard, IndexType._16Bit);
					b.Append(cubeVerts, cubeInds);
					l.Mesh.AddMeshBuffer(b);
					b.Drop();
				}

				device.SceneManager.MeshManipulator.SetVertexColors(l.Mesh, cubeColor);
			}

			l.Transform.Rotation = new Vector3Df(gridGeneration * 0.93f, gridGeneration * 0.81f, gridGeneration * 0.69f);

			l.Generation = gridGeneration;
			l.CubeCount = gridCubeCount;
			l.MeshIsReady = true;
		}

		public void Draw(bool debugDrawGenerator = false)
		{
			VideoDriver driver = device.VideoDriver;

			// draw

			driver.SetMaterial(cubeMaterial);
			foreach (GridLayer l in layers)
			{
				if (!l.MeshIsReady)
					continue;

				driver.SetTransform(TransformationState.World, l.Transform);
				foreach (MeshBuffer mb in l.Mesh.MeshBuffers)
					driver.DrawMeshBuffer(mb);
			}

			// draw debug info

			if (debugDrawGenerator)
			{
				foreach (GridLayer l in layers)
				{
					if (!l.MeshIsReady)
						continue;

					if (l.Generation == gridGeneration - 1)
					{
						driver.SetMaterial(Material.IdentityRedWireframe);
						driver.SetTransform(TransformationState.World, l.Transform);

						Color c = Color.OpaqueRed;
						float x1 = -(CubeSize * GridDim) / 2;
						float z1 = -(CubeSize * GridDim) / 2;
						float x2 = x1 + (GridDim - 1) * CubeSize;
						float z2 = z1 + (GridDim - 1) * CubeSize;

						driver.Draw3DLine(new Line3Df(x1, 0, z1, x2, 0, z1), c);
						driver.Draw3DLine(new Line3Df(x1, 0, z1, x1, 0, z2), c);
						driver.Draw3DLine(new Line3Df(x2, 0, z1, x2, 0, z2), c);
						driver.Draw3DLine(new Line3Df(x1, 0, z2, x2, 0, z2), c);

						foreach (MeshBuffer mb in l.Mesh.MeshBuffers)
							driver.DrawMeshBuffer(mb);

						break;
					}
				}
			}
		}

		public void Drop()
		{
			if (meshGeneratorThread != null)
				meshGeneratorThread.Join();

			device.Drop();
		}

		public int GetTotalCubeCount()
		{
			int c = 0;

			foreach (GridLayer l in layers)
			{
				if (!l.MeshIsReady)
					continue;

				c += l.CubeCount;
			}

			return c;
		}

		[DebuggerDisplay("GridLayer: Generation={Generation}; MeshIsReady={MeshIsReady}")]
		class GridLayer
		{
			public bool MeshIsReady = false;
			public int Generation = -1;
			public int CubeCount = -1;
			public Mesh Mesh = null;
			public Matrix Transform = new Matrix();
		}
	}
}
