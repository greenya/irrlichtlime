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

			MeshBuffersBatch batch = new MeshBuffersBatch(device, N);

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
					device.VideoDriver.PrimitiveCountDrawn + " prims | " +
					MemUsageText + " of physical memory used");
			}

			batch.Drop();
			device.Drop();
		}

		static int AskUserForN()
		{
			Console.WriteLine("Enter size of bounding cube side");
			Console.WriteLine("(10 to render 10*10*10=1k cubes; 20 for 8k; 40 => 64k; 50 => 125k)");
			Console.Write("(typing less than 1 or more than 80 (512k) is not recommended): ");
			string s = Console.ReadLine();

			return Convert.ToInt32(s);
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

		List<MeshBuffer> meshbuffers; // list of pointers on ready-to-be-drawn meshbuffers
		List<Mesh> meshesToDrop; // list of meshes that we have created (to use their meshbuffers) and must drop after all

		public MeshBuffersBatch(IrrlichtDevice device, int N)
		{
			this.device = device;

			material = new Material();
			material.Lighting = false;

			matrix = new Matrix();

			Vertex3D[] vertices32bit;
			uint[] indices32bit;
			generate(device, N, out vertices32bit, out indices32bit);

			int chunk = 0; // current 16-bit chunk of indices
			int chunkSize = 65520; // must be less than 0xffff and able to divide on 36 without remaining (36 is a number of indices in each single cube)
			// 65520/36 == 1820 cubes per chunk (maximum possible)

			meshbuffers = new List<MeshBuffer>();
			meshesToDrop = new List<Mesh>();

			device.Logger.Log("Batching cubes into chunks (meshbuffers)...");

			while (true)
			{
				int startVertexIndex = int.MaxValue;
				int endVertexIndex = int.MinValue;

				List<int> indicesChunk = new List<int>();
				for (int i = chunk * chunkSize; i < indices32bit.Length && i < (chunk + 1) * chunkSize; i++)
				{
					if (indices32bit[i] < startVertexIndex)
						startVertexIndex = (int)indices32bit[i];

					if (indices32bit[i] > endVertexIndex)
						endVertexIndex = (int)indices32bit[i];

					indicesChunk.Add((int)indices32bit[i]);
				}

				for (int i = 0; i < indicesChunk.Count; i++)
					indicesChunk[i] -= startVertexIndex;

				List<Vertex3D> verticesChunk = new List<Vertex3D>();
				for (int i = (int)startVertexIndex; i <= (int)endVertexIndex; i++)
					verticesChunk.Add(vertices32bit[i]);

				// as we cannot create MeshBuffer (for now this is impossible in Lime), we going to ask Irrlicht to create some primitive,
				// than we will use its mesh buffer for modification and rendering after all.
				// Note: Irrlicht' GeometryCreator creates 16-bit meshbuffers only, so we have one more problem to care about.

				Mesh mesh = device.SceneManager.GeometryCreator.CreateCubeMesh(new Vector3Df(1));
				MeshBuffer mb = mesh.GetMeshBuffer(0);

				meshbuffers.Add(mb);
				meshesToDrop.Add(mesh);

				// all stuff below is only because we have to deal with existing 36 indices and 12 vertices in just created mesh :(
				// p.s.: otherwise we would write something like "mb.Append(verticesChunk.ToArray(), indicesChunk.ToArray());"
				// {{{

				ushort[] indicesToUpdate = new ushort[36];
				for (int i = 0; i < 36; i++) indicesToUpdate[i] = (ushort)indicesChunk[i];

				ushort[] indicesToAppend = new ushort[indicesChunk.Count - 36];
				for (int i = 0; i < indicesChunk.Count - 36; i++) indicesToAppend[i] = (ushort)(indicesChunk[i + 36] - 12);

				Vertex3D[] verticesToUpdate = new Vertex3D[12];
				for (int i = 0; i < 12; i++) verticesToUpdate[i] = verticesChunk[i];

				Vertex3D[] verticesToAppend = new Vertex3D[verticesChunk.Count - 12];
				for (int i = 0; i < verticesChunk.Count - 12; i++) verticesToAppend[i] = verticesChunk[i + 12];

				mb.UpdateIndices(indicesToUpdate, 0);
				mb.UpdateVertices(verticesToUpdate, 0);
				mb.Append(verticesToAppend, indicesToAppend);

				// }}}

				mb.SetHardwareMappingHint(HardwareMappingHint.Static, HardwareBufferType.VertexAndIndex);

				device.Logger.Log(
					(chunk * 100 / ((indices32bit.Length / chunkSize) + 1)) + "%: " +
					"Chunk #" + (chunk + 1) + " has been created. ~" +
					Program.MemUsageText,
					LogLevel.Debug);

				if ((chunk & 0xf) == 0xf)
					GC.Collect();

				if (indices32bit.Length <= (chunk + 1) * chunkSize)
					break;

				chunk++;
			}
		}

		public void Draw()
		{
			device.VideoDriver.SetTransform(TransformationState.World, matrix);
			device.VideoDriver.SetMaterial(material);

			foreach (MeshBuffer mb in meshbuffers)
				device.VideoDriver.DrawMeshBuffer(mb);
		}

		public void Drop()
		{
			foreach (Mesh m in meshesToDrop)
				m.Drop();
		}

		/// <param name="N">Number of cubes in single dimension (e.g. total cubes for 20 is 20^3=8000)</param>
		private void generate(IrrlichtDevice device, int N, out Vertex3D[] vertices, out uint[] indices)
		{
			int cubeSide = 32;

			// ask Irrlicht to generate cube mesh for us (we use it like a template)

			Mesh cubeMesh = device.SceneManager.GeometryCreator.CreateCubeMesh(new Vector3Df(cubeSide));
			ushort[] cubeIndices = cubeMesh.GetMeshBuffer(0).Indices as ushort[];
			Vertex3D[] cubeVertices = cubeMesh.GetMeshBuffer(0).Vertices as Vertex3D[];
			cubeMesh.Drop();

			// generate cubes

			device.Logger.Log("Generating " + N * N * N + " cubes...", LogLevel.Debug);

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
					Program.MemUsageText,
					LogLevel.Debug);

				if ((i & 0xf) == 0xf)
					GC.Collect();
			}
		}
	}
}
