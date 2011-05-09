using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L07.FastStaticRendering
{
	class Program
	{
		static void Main(string[] args)
		{
			int N = AskUserForN();
			bool B = AskUserForB();

			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(800, 600));
			if (device == null)
				return;

			device.CursorControl.Visible = false;

			CameraSceneNode camera = device.SceneManager.AddCameraSceneNodeFPS();
			camera.FarValue = 20000;
			camera.Position = new Vector3Df(-200);
			camera.Target = new Vector3Df(0);

			MeshBuffersBatch batch = new MeshBuffersBatch(device, N, B);

			while (device.Run())
			{
				device.VideoDriver.BeginScene();

				device.SceneManager.DrawAll();

				batch.Draw();

				device.VideoDriver.EndScene();

				device.SetWindowCaption(
					"Fast static rendering - Irrlicht Lime - " +
					device.VideoDriver.Name + " | " +
					device.VideoDriver.FPS + " fps | " +
					N * N * N + " cubes  | " +
					device.VideoDriver.PrimitiveCountDrawn + " primitives | " +
					MemUsageText + " of physical memory used");
			}

			batch.Drop();
			device.Drop();
		}

		static int AskUserForN()
		{
			Console.WriteLine("Enter size of bounding cube side");
			Console.WriteLine(" (10 to render 10*10*10=1k cubes; 20 for 8k; 40 => 64k; 50 => 125k)");
			Console.WriteLine(" (typing less than 1 or more than 80 (512k) is not recommended): ");
			string s = Console.ReadLine();

			return Convert.ToInt32(s);
		}

		static bool AskUserForB()
		{
			Console.WriteLine("What meshbuffers to use?");
			Console.WriteLine(" (1) split to 16-bit meshbuffers");
			Console.WriteLine(" (2) use single 32-bit meshbuffer ");
			ConsoleKeyInfo k = Console.ReadKey();

			return k.KeyChar == '1';
		}

		static bool AskUserForDriver(out DriverType driverType)
		{
			driverType = DriverType.Null;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n" +
						" (d) Burning's Software Renderer\n (e) Software Renderer\n" +
						" (f) NullDevice\n (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: driverType = DriverType.OpenGL; break;
				case ConsoleKey.B: driverType = DriverType.Direct3D9; break;
				case ConsoleKey.C: driverType = DriverType.Direct3D8; break;
				case ConsoleKey.D: driverType = DriverType.BurningsVideo; break;
				case ConsoleKey.E: driverType = DriverType.Software; break;
				case ConsoleKey.F: driverType = DriverType.Null; break;
				default:
					return false;
			}

			return true;
		}

		static public string MemUsageText
		{
			get { return System.Diagnostics.Process.GetCurrentProcess().WorkingSet64 / (1024 * 1024) + " Mb"; }
		}
	}

	class MeshBuffersBatch
	{
		IrrlichtDevice device;
		Material material;
		Matrix matrix;
		Mesh mesh;

		public MeshBuffersBatch(IrrlichtDevice device, int N, bool B)
		{
			this.device = device;
			material = new Material();
			material.Lighting = false;
			matrix = new Matrix();

			mesh = Mesh.Create();

			if (B)
				generateMultiple16bitMeshbuffers(N);
			else
				generateSingle32BitMeshbuffer(N);

			mesh.RecalculateBoundingBox();

			device.Logger.Log("Collecting garbage...");
			GC.Collect();
		}

		public void Drop()
		{
			mesh.Drop();
		}

		public void Draw()
		{
			device.VideoDriver.SetTransform(TransformationState.World, matrix);
			device.VideoDriver.SetMaterial(material);

			for (int i = 0; i < mesh.MeshBufferCount; i++)
				device.VideoDriver.DrawMeshBuffer(mesh.GetMeshBuffer(i));
		}

		void generateMultiple16bitMeshbuffers(int N)
		{
			Vertex3D[] vertices32bit;
			uint[] indices32bit;
			generateVerticesAndIndices(N, out vertices32bit, out indices32bit);

			List<Vertex3D> verticesChunk = new List<Vertex3D>();
			List<ushort> indicesChunk = new List<ushort>();
			
			int totalCubes = N * N * N;
			int indicesInCube = indices32bit.Length / totalCubes;
			int verticesInCube = vertices32bit.Length / totalCubes;
			int maximumVerticesPerChunk = ushort.MaxValue; // must not be more than 0xffff (because we use 16-bit indices)
			int verticesIndexOffset = 0;

			device.Logger.Log("Batching cubes into 16-bit meshbuffers...");

			for (int cubeIndex = 0; cubeIndex < totalCubes; cubeIndex++)
			{
				// add vertices
				for (int i = 0; i < verticesInCube; i++)
					verticesChunk.Add(vertices32bit[cubeIndex * verticesInCube + i]);

				// add indices
				for (int i = 0; i < indicesInCube; i++)
					indicesChunk.Add((ushort)(indices32bit[cubeIndex * indicesInCube + i] - verticesIndexOffset));

				if (verticesChunk.Count + verticesInCube > maximumVerticesPerChunk // if this chunk is full
					|| cubeIndex == totalCubes - 1) // or this is last cube
				{
					// we create meshbuffer and add it to the main mesh
					MeshBuffer mb = MeshBuffer.Create(VertexType.Standard, IndexType._16Bit);
					mb.SetHardwareMappingHint(HardwareMappingHint.Static, HardwareBufferType.VertexAndIndex);
					mb.Append(verticesChunk.ToArray(), indicesChunk.ToArray());
					mb.RecalculateBoundingBox();
					mesh.AddMeshBuffer(mb);
					mb.Drop();

					// clean up vertex and index chunks
					verticesIndexOffset += verticesChunk.Count;
					verticesChunk = new List<Vertex3D>();
					indicesChunk = new List<ushort>();

					device.Logger.Log(
						(((cubeIndex + 1) * 100) / totalCubes) + "%: " +
						mesh + ". ~" +
						Program.MemUsageText);

					GC.Collect();
				}
			}
		}

		void generateSingle32BitMeshbuffer(int N)
		{
			Vertex3D[] vertices32bit;
			uint[] indices32bit;
			generateVerticesAndIndices(N, out vertices32bit, out indices32bit);

			MeshBuffer mb = MeshBuffer.Create(VertexType.Standard, IndexType._32Bit);
			mesh.AddMeshBuffer(mb);
			mb.Drop();

			device.Logger.Log("Appending " +
				vertices32bit.Length + " vertices and " +
				indices32bit.Length + " indices to 32-bit meshbuffer...");

			mb.Append(vertices32bit, indices32bit);
			mb.SetHardwareMappingHint(HardwareMappingHint.Static, HardwareBufferType.VertexAndIndex);
		}

		/// <param name="N">Number of cubes in single dimension (e.g. total cubes for 20 is 20^3=8000)</param>
		void generateVerticesAndIndices(int N, out Vertex3D[] vertices, out uint[] indices)
		{
			int cubeSide = 32;

			// ask Irrlicht to generate cube mesh for us (we use it like a template)

			Mesh cubeMesh = device.SceneManager.GeometryCreator.CreateCubeMesh(new Vector3Df(cubeSide));
			ushort[] cubeIndices = cubeMesh.GetMeshBuffer(0).Indices as ushort[];
			Vertex3D[] cubeVertices = cubeMesh.GetMeshBuffer(0).Vertices as Vertex3D[];
			cubeMesh.Drop();

			// generate cubes

			device.Logger.Log("Generating " + N * N * N + " cubes...");

			vertices = new Vertex3D[N * N * N * cubeVertices.Length];
			indices = new uint[N * N * N * cubeIndices.Length];

			int verticesIndex = 0;
			int indicesIndex = 0;
			int colorBase = (255 - cubeVertices.Length) / N;
			float cubePosOffset = 2.0f * cubeSide;

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					for (int k = 0; k < N; k++)
					{
						// add indices
						uint firstfreeIndex = (uint)verticesIndex;
						for (int l = 0; l < cubeIndices.Length; l++)
							indices[indicesIndex++] = firstfreeIndex + cubeIndices[l];

						// add vertices
						for (int l = 0; l < cubeVertices.Length; l++)
						{
							Vertex3D v = new Vertex3D(cubeVertices[l]);
							v.Color = new Color(i * colorBase + l, j * colorBase + l, k * colorBase + l);
							v.Position += new Vector3Df(i, j, k) * cubePosOffset;
							vertices[verticesIndex++] = v;
						}
					}
				}

				device.Logger.Log(
					(((i + 1) * 100) / N) + "%: " +
					(i + 1) * N * N + " cubes has been generated. ~" +
					Program.MemUsageText);

				if ((i & 0xf) == 0xf)
					GC.Collect();
			}
		}
	}
}
