using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L09.SimpleLOD
{
	class Program
	{
		static IrrlichtDevice device;
		static bool isWireframeMode = false;
		static bool isLabelMode = false;
		static bool isStatsMode = false;

		static void Main(string[] args)
		{
			int lodItemCount = AskUserForLODItemCount();

			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(800, 600));
			if (device == null)
				return;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.SetWindowCaption("Simple LOD - Irrlicht Lime");
			device.CursorControl.Visible = false;

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			// generate all LODs of mesh

			List<Mesh> lodMesh = new List<Mesh>();
			Material meshMaterial = null;
			List<int> lodTriangleCount = new List<int>();

			int[] p = new int[] { 100, 50, 32, 20, 12, 6, 3 };
			for (int i = 0; i < p.Length; i++)
			{
				Mesh m = scene.GeometryCreator.CreateSphereMesh(50, p[i], p[i]);

				MeshBuffer mb = m.GetMeshBuffer(0);
				mb.Material.Type = MaterialType.Solid;
				mb.Material.SetTexture(0, driver.GetTexture("../../media/earth.jpg"));

				m.SetMaterialFlag(MaterialFlag.Lighting, false);
				lodMesh.Add(m);

				if (meshMaterial == null)
					meshMaterial = m.GetMeshBuffer(0).Material;

				lodTriangleCount.Add(mb.IndexCount / 3);
			}

			// generate world,
			// we generate a lot of objects with random positions in huge virtual cube

			int virtualCubeSide = 20000;
			LODItem[] lodItems = new LODItem[lodItemCount];
			Random r = new Random(12345000);
			for (int i = 0; i < lodItemCount; i++)
			{
				Matrix tmat = new Matrix(
					new Vector3Df( // translation
						r.Next(virtualCubeSide) - virtualCubeSide / 2,
						r.Next(virtualCubeSide) - virtualCubeSide / 2,
						r.Next(virtualCubeSide) - virtualCubeSide / 2));

				Vector3Df rvect = new Vector3Df(
					(float)r.NextDouble() / 200.0f,
					(float)r.NextDouble() / 200.0f,
					(float)r.NextDouble() / 200.0f);

				lodItems[i] = LODItem.Create(device, lodMesh, tmat, rvect);
			}

			// split world on virtual sectors (cubes) for faster visibility check

			int lodSectorSide = 6; // total number of sectors will be lodSectorSide^3, so for 6 it is 216
			int lodSectorSize = virtualCubeSide / lodSectorSide;
			LODSector[,,] lodSectors = new LODSector[lodSectorSide, lodSectorSide, lodSectorSide];

			for (int i = 0; i < lodSectorSide; i++)
			{
				for (int j = 0; j < lodSectorSide; j++)
				{
					for (int k = 0; k < lodSectorSide; k++)
					{
						AABBox dimension = new AABBox(
							new Vector3Df(i * lodSectorSize, j * lodSectorSize, k * lodSectorSize),
							new Vector3Df((i + 1) * lodSectorSize, (j + 1) * lodSectorSize, (k + 1) * lodSectorSize));

						dimension.MinEdge -= virtualCubeSide / 2;
						dimension.MaxEdge -= virtualCubeSide / 2;

						LODSector s = LODSector.Create(dimension);
						lodSectors[i, j, k] = s;
					}
				}
			}

			for (int i = 0; i < lodItems.Length; i++)
			{
				Vector3Df pos = lodItems[i].Position;
				pos += virtualCubeSide / 2;
				pos /= lodSectorSize;

				int ix = (int)pos.X;
				int iy = (int)pos.Y;
				int iz = (int)pos.Z;

				if (ix < 0) ix = 0;
				if (ix > lodSectorSide - 1)
					ix = lodSectorSide - 1;

				if (iy < 0) ix = 0;
				if (iy > lodSectorSide - 1)
					iy = lodSectorSide - 1;

				if (iz < 0) iz = 0;
				if (iz > lodSectorSide - 1)
					iz = lodSectorSide - 1;

				lodSectors[ix, iy, iz].AddLODItem(lodItems[i]);
			}

			// camera

			CameraSceneNode camera = scene.AddCameraSceneNodeFPS();
			camera.FarValue = 30000;

			// font, which we are going to use to show any text we need

			IrrlichtLime.GUI.GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");

			// render loop

			while (device.Run())
			{
				driver.BeginScene();
				scene.DrawAll();

				if (isLabelMode)
				{
					LODItem.LabelPositions = new List<Vector2Di>();
					LODItem.LabelTexts = new List<string>();
				}
				else
				{
					LODItem.LabelPositions = null;
					LODItem.LabelTexts = null;
				}

				meshMaterial.Wireframe = isWireframeMode;
				device.VideoDriver.SetMaterial(meshMaterial);

				uint timer = device.Timer.Time;
				Vector3Df cameraPosition = camera.AbsolutePosition;
				AABBox cameraViewBox = camera.ViewFrustum.BoundingBox;

				for (int i = 0; i < lodSectorSide; i++)
				{
					for (int j = 0; j < lodSectorSide; j++)
					{
						for (int k = 0; k < lodSectorSide; k++)
						{
							lodSectors[i, j, k].Draw(timer, cameraPosition, cameraViewBox);
						}
					}
				}

				if (isLabelMode)
				{
					for (int i = 0; i < LODItem.LabelPositions.Count; i++)
					{
						driver.Draw2DLine(
							LODItem.LabelPositions[i] - new Vector2Di(10, 0),
							LODItem.LabelPositions[i] + new Vector2Di(50, 0),
							Color.OpaqueGreen);

						driver.Draw2DLine(
							LODItem.LabelPositions[i] - new Vector2Di(0, 10),
							LODItem.LabelPositions[i] + new Vector2Di(0, 50),
							Color.OpaqueGreen);

						font.Draw(LODItem.LabelTexts[i], LODItem.LabelPositions[i], Color.OpaqueGreen);
					}
				}

				if (isStatsMode)
				{
					// show LOD stats

					int[] lodCount = new int[7] { 0, 0, 0, 0, 0, 0, 0 };
					for (int i = 0; i < lodItems.Length; i++)
						lodCount[lodItems[i].CurrentLOD]++;

					string f = "";
					for (int i = 0; i < lodCount.Length; i++)
					{
						int n = lodCount[i];
						f += "LOD" + i.ToString() + ": " + n.ToString() + " [" + ((n * 100) / lodItemCount).ToString() + "%] objects\n";
					}

					string l = "------------------------";

					font.Draw(
						string.Format("Stats\n{0}\n{1}{2}\nTotal: {3} [100%] objects", l, f, l, lodItemCount),
						new Vector2Di(10, 140),
						Color.OpaqueMagenta);
				}

				// show general stats

				font.Draw(string.Format(
					"Camera position: {0}\nTotal LOD 0 triangles: {1}\nTriangles currently drawn: {2}\nDriver: {3}\nFPS: {4}",
					camera.AbsolutePosition,
					lodTriangleCount[0] * lodItemCount,
					driver.PrimitiveCountDrawn,
					driver.Name,
					driver.FPS),
					10, 10, Color.OpaqueYellow);

				// show active keys

				font.Draw(
				    "[S] Toggle stats\n[W] Toggle wireframe\n[L] Toggle labels (only for LODs from 0 to 4)\n[Esc] Exit application",
				    10, driver.ScreenSize.Height - 80, Color.OpaqueCyan);

				driver.EndScene();
			}

			// drop

			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Key &&
				evnt.Key.PressedDown)
			{
				switch (evnt.Key.Key)
				{
					case KeyCode.KeyS:
						isStatsMode = !isStatsMode;
						return true;

					case KeyCode.KeyW:
						isWireframeMode = !isWireframeMode;
						return true;

					case KeyCode.KeyL:
						isLabelMode = !isLabelMode;
						return true;

					case KeyCode.Esc:
						device.Close();
						return true;
				}
			}

			return false;
		}

		static int AskUserForLODItemCount()
		{
			Console.Write("Enter number of planets to generate (recommended value is 5000): ");
			string s = Console.ReadLine();

			int i = Convert.ToInt32(s);
			if (i < 1) i = 1;

			return i;
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

	class LODItem
	{
		public static List<Vector2Di> LabelPositions = null;
		public static List<string> LabelTexts = null;

		IrrlichtDevice device;
		VideoDriver driver;
		Dimension2Di screenSize;

		List<Mesh> meshLODs;
		Matrix transformation;
		Vector3Df rotationVector;

		uint nextUpdateAt = 0;
		int currentLOD;

		public int CurrentLOD { get { return currentLOD; } }
		public Vector3Df Position { get { return transformation.Translation; } }

		static public LODItem Create(IrrlichtDevice device, List<Mesh> meshLODs, Matrix transformation, Vector3Df rotationVector)
		{
			LODItem n = new LODItem();
			n.device = device;
			n.meshLODs = meshLODs;
			n.transformation = transformation;
			n.rotationVector = rotationVector;
			n.currentLOD = meshLODs.Count - 1;

			// we cache some really frequently accessed values (which will never get changed anyway)
			n.driver = device.VideoDriver;
			n.screenSize = device.VideoDriver.ScreenSize;

			return n;
		}

		readonly float[] lodDistanceSQ = new float[] { // this values directly controls how many tringles we are drawing
			150 * 150, // LOD 0: 0 ... 150
			300 * 300, // LOD 1: 150 ... 300
			600 * 600, // LOD 2: 300 ... 600
			1200 * 1200, // LOD 3: 600 ... 1200
			2500 * 2500, // LOD 4: 1200 ... 2500
			6000 * 6000, // LOD 5: 2500 ... 6000
			-1 * -1 // LOD 6: 6000+; value "-1" doesn't play any role,
			// because anything that is further than 6000 will stay at the last available LOD, which is 6
		};

		readonly uint[] updateIntervals = new uint[] {
			10, // we can affort this speed of updating (which is almost "every frame")
			20, // because we know that objects with LOD 0 and 1 - are very close to the camera, we want them to look
			// hipoly and rotate smoothly; also we understand that it is only couple of objects with this LOD is
			// going to be present at any time
			40,
			80,
			120,
			200,
			1500 };

		public void Draw(uint time, Vector3Df cameraPosition)
		{
			if (time > nextUpdateAt)
			{
				// animation

				transformation.Rotation = rotationVector * time;

				// recalculate current LOD

				currentLOD = meshLODs.Count - 1;
				float distanceSQ = (transformation.Translation - cameraPosition).LengthSQ;
				for (int i = 0; i < lodDistanceSQ.Length - 1; i++)
				{
					if (distanceSQ < lodDistanceSQ[i])
					{
						currentLOD = i;
						break;
					}
				}

				// next line assigns new time for LOD to be recalculated in future,
				// we do not use same value for all LODs here, because we don't want all the LODItems
				// to be recalculated in the same time (same frame). So we assign a value
				// which higher when current LOD is higher - which also means that for now we are
				// a distant object and it is less possible that we will need to change LOD at all;
				// but close objects (with small LOD value, like 0, 1 or 2) we need to pick quite short time.
				// This is OK if it will be really short, because this objects are too close and indeed may
				// change their LOD value very soon, however, we also understand, that in general all the objects
				// takes very large area, so in general we will have something like less than 2% with LOD level 0, 1 or 2,
				// all other will get higher LOD, and about more than 50% will have maximum LOD value -- they take more time to recalc
				// their LOD than to draw them, so we need to calc their LOD less frequent.
				// p.s.: we also uses that fact, that we do not give ability to user to reach oposite side of our world in 1 frame,
				// the speed which user uses for movement is slow in general.

				nextUpdateAt = time + updateIntervals[currentLOD];
			}

			// drawing

			// we do no set material here, because we draw all LODItems with the same material, we set material in main rendering loop

			driver.SetTransform(TransformationState.World, transformation); // this is also very time consuming operation; we can optimize it
			// to make something like 100 calls (instead of 5000 - the number of LODItems) - we need to group LODItems all this we increase FPS up on
			// 10%, BUT it that case we will not be able to move independent LODItems, becase they will not need (and will not have) own transformation
			// matrix (only LODGroup will has it). So grouping is really greate for some completly static objects like trees, shrubs, stones, etc.

			// we draw single 16-bit meshbuffer
			driver.DrawMeshBuffer(meshLODs[currentLOD].GetMeshBuffer(0));

			if (LabelPositions != null && currentLOD <= 4)
			{
				Vector2Di p = device.SceneManager.SceneCollisionManager.GetScreenCoordinatesFrom3DPosition(transformation.Translation);

				// now we filter here results which will not be visible; we know that:
				// - GetScreenCoordinatesFrom3DPosition() returns {-10000,-10000} for behind camera 3d positions
				// - we do not need to draw out small text if its out of the screen
				// p.s.: without this filtering we will have about 200-300 labels to draw (instead of about 10-20 which are trully visible)
				if (p.X > -200 && p.X < screenSize.Width + 200 &&
					p.Y > -100 && p.Y < screenSize.Height + 100)
				{
					int t = meshLODs[currentLOD].GetMeshBuffer(0).IndexCount / 3;
					int d = (int)(transformation.Translation - cameraPosition).Length;

					LabelPositions.Add(p);
					LabelTexts.Add(
						"LOD: " + currentLOD.ToString() +
						"\nTrinagles: " + t.ToString() +
						"\nDistance: " + d.ToString());
				}
			}
		}
	}

	class LODSector
	{
		AABBox dimension;
		Vector3Df d1, d2, d3, d4, d5, d6, d7, d8;

		List<LODItem> lodItems;

		public AABBox Dimension { get { return dimension; } }

		public static LODSector Create(AABBox dimension)
		{
			LODSector s = new LODSector();
			s.dimension = dimension;
			s.d1 = dimension.MinEdge;
			s.d2 = new Vector3Df(dimension.MinEdge.X, dimension.MinEdge.Y, dimension.MaxEdge.Z);
			s.d3 = new Vector3Df(dimension.MinEdge.X, dimension.MaxEdge.Y, dimension.MinEdge.Z);
			s.d4 = new Vector3Df(dimension.MinEdge.X, dimension.MaxEdge.Y, dimension.MaxEdge.Z);
			s.d5 = dimension.MaxEdge;
			s.d6 = new Vector3Df(dimension.MaxEdge.X, dimension.MinEdge.Y, dimension.MinEdge.Z);
			s.d7 = new Vector3Df(dimension.MaxEdge.X, dimension.MinEdge.Y, dimension.MaxEdge.Z);
			s.d8 = new Vector3Df(dimension.MaxEdge.X, dimension.MaxEdge.Y, dimension.MinEdge.Z);

			s.lodItems = new List<LODItem>();

			return s;
		}

		public void AddLODItem(LODItem lodItem)
		{
			lodItems.Add(lodItem);
		}

		public void Draw(uint time, Vector3Df cameraPosition, AABBox cameraViewBox)
		{
			if (cameraViewBox.IsInside(d1) ||
				cameraViewBox.IsInside(d2) ||
				cameraViewBox.IsInside(d3) ||
				cameraViewBox.IsInside(d4) ||
				cameraViewBox.IsInside(d5) ||
				cameraViewBox.IsInside(d6) ||
				cameraViewBox.IsInside(d7) ||
				cameraViewBox.IsInside(d8))
			{
				for (int i = 0; i < lodItems.Count; i++)
				{
					lodItems[i].Draw(time, cameraPosition);
				}
			}
		}
	}
}
