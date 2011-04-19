using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _23.MeshHandling
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(800, 600));
			if (device == null)
				return;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.SetWindowCaption("Mesh handling - Irrlicht Lime");
			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			// Generate starting height map and mesh

			HeightMap map = new HeightMap(255, 255);
			map.Generate(HeightMap.HeightFunc.EggBox);

			HeightMesh mesh = new HeightMesh();
			mesh.Init(driver, map, 50.0f, HeightMesh.ColorFunc.GreyscaleBasedOnTheHeight);

			// Add the mesh to the scene graph

			MeshSceneNode meshnode = scene.AddMeshSceneNode(mesh.Mesh);
			meshnode.SetMaterialFlag(MaterialFlag.BackFaceCulling, false);

			// Add light (just for nice effects)

			LightSceneNode lightnode = scene.AddLightSceneNode(null, new Vector3Df(0, 100, 0), new Colorf(1, 1, 1), 500.0f);
			SceneNodeAnimator anim = scene.CreateFlyCircleAnimator(new Vector3Df(0, 150, 0), 250.0f);
			lightnode.AddAnimator(anim);
			anim.Drop();

			// Add camera

			CameraSceneNode camera = scene.AddCameraSceneNodeFPS();
			camera.Position = new Vector3Df(-20.0f, 100.0f, -20.0f);
			camera.Target = new Vector3Df(200.0f, -100.0f, 200.0f);
			camera.FarValue = 20000.0f;

			// Main loop

			while (device.Run())
			{
				if (!device.WindowActive)
				{
					device.Sleep(100);
					continue;
				}

				if (IsKeyDown(KeyCode.KeyW))
				{
					meshnode.SetMaterialFlag(MaterialFlag.Wireframe, !meshnode.GetMaterial(0).Wireframe);
				}
				else if (IsKeyDown(KeyCode.Key1))
				{
					map.Generate(HeightMap.HeightFunc.EggBox);
					mesh.Init(driver, map, 50.0f, HeightMesh.ColorFunc.GreyscaleBasedOnTheHeight);
				}
				else if (IsKeyDown(KeyCode.Key2))
				{
					map.Generate(HeightMap.HeightFunc.MoreSine);
					mesh.Init(driver, map, 50.0f, HeightMesh.ColorFunc.CoordinateInterpolation);
				}
				else if (IsKeyDown(KeyCode.Key3))
				{
					map.Generate(HeightMap.HeightFunc.JustExp);
					mesh.Init(driver, map, 50.0f, HeightMesh.ColorFunc.CoordinateInterpolation);
				}

				driver.BeginScene();
				scene.DrawAll();
				driver.EndScene();
			}

			// Clean up

			mesh.Drop();
			device.Drop();
		}

		static Dictionary<KeyCode, bool> KeyIsDown = new Dictionary<KeyCode, bool>();

		static bool device_OnEvent(Event e)
		{
			if (e.Type == EventType.Key)
			{
				if (KeyIsDown.ContainsKey(e.Key.Key))
					KeyIsDown[e.Key.Key] = e.Key.PressedDown;
				else
					KeyIsDown.Add(e.Key.Key, e.Key.PressedDown);
			}

			return false;
		}

		static bool IsKeyDown(KeyCode keyCode)
		{
			return KeyIsDown.ContainsKey(keyCode) ? KeyIsDown[keyCode] : false;
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
	}

	/// <summary>
	/// A simple class for representing heightmaps.
	/// </summary>
	class HeightMap
	{
		/// <summary>
		/// The type of the function which generate the heightmap.
		/// </summary>
		public enum HeightFunc
		{
			/// <summary>
			/// An interesting sample function :-)
			/// </summary>
			EggBox,

			/// <summary>
			/// A rather dumb sine function :-/
			/// </summary>
			MoreSine,

			/// <summary>
			/// A simple function
			/// </summary>
			JustExp
		}

		float scale;
		float[] data;

		public ushort Width { get; private set; }
		public ushort Height { get; private set; }

		/// <summary>
		/// Creates new instance with given width and height. 
		/// </summary>
		public HeightMap(ushort w, ushort h)
		{
			Width = w;
			Height = h;
			scale = (float)Math.Sqrt((double)(w * w + h * h));
			data = new float[w * h];
		}

		/// <summary>
		/// Gets height value for specified coordinates.
		/// </summary>
		public float GetHeight(int x, int y)
		{
			if (x < 0 || x > Width || y < 0 || y > Height)
				throw new ArgumentOutOfRangeException();

			return data[x + Width * y];
		}

		/// <summary>
		/// Fills the heightmap with values generated from given function.
		/// </summary>
		public void Generate(HeightFunc func)
		{
			int i = 0;
			for (int y = 0; y < Height; y++)
				for (int x = 0; x < Width; x++)
					data[i++] = calculate(func, x, y);
		}

		/// <summary>
		/// Gets the normal vector at (x, y) to be the cross product of the vectors between the adjacent
		/// points in the horizontal and vertical directions.
		/// </summary>
		public Vector3Df GetNormal(int x, int y, float s)
		{
			if (x < 0 || x > Width || y < 0 || y > Height)
				throw new ArgumentOutOfRangeException();

			float zc = GetHeight(x, y);
			float zl, zr, zu, zd;

			if (x == 0)
			{
				zr = GetHeight(x + 1, y);
				zl = zc + zc - zr;
			}
			else if (x == Width - 1)
			{
				zl = GetHeight(x - 1, y);
				zr = zc + zc - zl;
			}
			else
			{
				zr = GetHeight(x + 1, y);
				zl = GetHeight(x - 1, y);
			}

			if (y == 0)
			{
				zd = GetHeight(x, y + 1);
				zu = zc + zc - zd;
			}
			else if (y == Height - 1)
			{
				zu = GetHeight(x, y - 1);
				zd = zc + zc - zu;
			}
			else
			{
				zd = GetHeight(x, y + 1);
				zu = GetHeight(x, y - 1);
			}

			return new Vector3Df(scale * 2 * (zl - zr), 4, scale * 2 * (zd - zu)).Normalize();
		}

		/// <summary>
		/// Calculates single height value for specified function and coordinates.
		/// </summary>
		float calculate(HeightFunc func, int x, int y)
		{
			float xu = x - Width / 2.0f;
			float yu = y - Height / 2.0f;

			switch (func)
			{
				case HeightFunc.EggBox:
					{
						double r = 4.0f * Math.Sqrt((double)(xu * xu + yu * yu)) / scale;
						double z = Math.Exp(-r * 2) * (Math.Cos(0.2f * xu) + Math.Cos(0.2f * yu));
						float o = (float)(0.32f + 0.25f * z);
						return o;
					}

				case HeightFunc.MoreSine:
					{
						double xf = 0.3f * xu / scale;
						double yf = 12.0f * yu / scale;
						double z = Math.Sin(xf * xf + yf) * Math.Sin(xf + yf * yf);
						float o = (float)(0.25f + 0.25f * z);
						return o;
					}

				case HeightFunc.JustExp:
					{
						float xf = 6 * xu / scale;
						float yf = 6 * yu / scale;
						float z = xf * xf + yf * yf;
						float o = (float)(0.3f * z * Math.Cos(xf * yf));
						return o;
					}

				default:
					throw new ArgumentException("Unexpected height function value: " + func.ToString());
			}
		}
	}

	/// <summary>
	/// Generates a mesh from a heightmap.
	/// </summary>
	class HeightMesh
	{
		/// <summary>
		/// Set of functions which can be used for coloring the nodes while creating the mesh.
		/// </summary>
		public enum ColorFunc
		{
			GreyscaleBasedOnTheHeight,
			CoordinateInterpolation,
			PureWhite
		}

		int width;
		int height;
		float scale;

		public Mesh Mesh { get; private set; }

		public HeightMesh()
		{
			width = 0;
			height = 0;
			scale = 1.0f;
			Mesh = Mesh.Create();
		}

		public void Drop()
		{
			Mesh.Drop();
		}

		/// <summary>
		/// Initializes mesh with new value.
		/// Unless the heightmap is small, it won't all fit into a single MeshBuffer.
		/// This function chops it into pieces and generates a buffer from each one.
		/// </summary>
		public void Init(VideoDriver driver, HeightMap map, float s, ColorFunc cf)
		{
			width = map.Width;
			height = map.Height;
			scale = s;

			if (Mesh.MeshBufferCount > 0)
				Mesh.RemoveMeshBuffer(0, Mesh.MeshBufferCount);

			int sw = 0xffff / (height + 1); // maximum vertices per meshbuffer

			for (int y0 = 0; y0 < height; y0 += sw)
			{
				int y1 = y0 + sw;
				if (y1 >= height)
					y1 = height - 1; // the last one might be narrower
				addStrip(map, cf, y0, y1);
			}

			Mesh.RecalculateBoundingBox();
		}

		/// <summary>
		/// Generates a MeshBuffer which represents all the vertices and indices for values of y
		/// between y0 and y1, and add it to the mesh.
		/// </summary>
		void addStrip(HeightMap map, ColorFunc cf, int y0, int y1)
		{
			Vertex3D[] vertices = new Vertex3D[(y1 - y0 + 1) * width];
			ushort[] indices = new ushort[(y1 - y0) * (width - 1) * 6]; // "6" is a number of indices in 2 triangles (which forms a quad)

			// calculate vertices

			int i = 0;
			for (int y = y0; y <= y1; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					float z = map.GetHeight(x, y);
					float xf = (float)x / (float)width;
					float yf = (float)y / (float)height;

					vertices[i++] = new Vertex3D(
						new Vector3Df(x, scale * z, y), // position
						map.GetNormal(x, y, scale), // normal
						calculate(cf, xf, yf, z), // color
						new Vector2Df(xf, yf) // tcoords
					);
				}
			}

			// calculate indices

			i = 0;
			for (int y = y0; y < y1; ++y)
			{
				for (int x = 0; x < width - 1; ++x)
				{
					int n = (y - y0) * width + x;
					indices[i++] = (ushort)n;
					indices[i++] = (ushort)(n + height);
					indices[i++] = (ushort)(n + height + 1);
					indices[i++] = (ushort)(n + height + 1);
					indices[i++] = (ushort)(n + 1);
					indices[i++] = (ushort)n;
				}
			}

			// append calculated verices and indices to mesh buffer

			MeshBuffer buf = MeshBuffer.Create(VertexType.Standard, IndexType._16Bit); // create new buffer
			Mesh.AddMeshBuffer(buf);
			buf.Append(vertices, indices);
			buf.RecalculateBoundingBox();
			buf.Drop();
		}

		/// <summary>
		/// Calculates single color value for given coordinates.
		/// </summary>
		Color calculate(ColorFunc cf, float x, float y, float z)
		{
			switch (cf)
			{
				case ColorFunc.GreyscaleBasedOnTheHeight:
					int n = (int)(255.0f * z);
					return new Color(n, n, n);

				case ColorFunc.CoordinateInterpolation:
					return new Color(128 + (int)(127.0f * x), 128 + (int)(127.0f * y), 255);

				case ColorFunc.PureWhite:
					return Color.OpaqueWhite;

				default:
					throw new ArgumentException("Unexpected color function value: " + cf.ToString());
			}
		}
	}
}
