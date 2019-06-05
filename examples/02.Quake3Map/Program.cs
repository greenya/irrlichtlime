using System;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _02.Quake3Map
{
	class Program
	{
		static void Main()
		{
			DriverType? driverType = AskForDriver();
			if (!driverType.HasValue)
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType.Value, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			device.FileSystem.AddFileArchive("../../media/map-20kdm2.pk3");

			AnimatedMesh mesh = smgr.GetMesh("20kdm2.bsp");
			SceneNode node = null;

			if (mesh != null)
				node = smgr.AddOctreeSceneNode(mesh.GetMesh(0), null, -1, 1024);

			if (node != null)
				node.Position = new Vector3Df(-1300, -144, -1249);

			smgr.AddCameraSceneNodeFPS();

			device.CursorControl.Visible = false;

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(ClearBufferFlag.All, new Color(200, 200, 200));
					smgr.DrawAll();
					driver.EndScene();

					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.SetWindowCaption(String.Format(
							"Quake 3 Map Example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
		}

		static DriverType? AskForDriver()
		{
			Console.Write("Please select the driver you want for this example:\n" +
				" (a) OpenGL\n" +
				" (b) Direct3D 9.0c\n" +
				" (c) Burning's Software Renderer\n" +
				" (d) Software Renderer\n" +
				" (e) NullDevice\n" +
				" (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: return DriverType.OpenGL;
				case ConsoleKey.B: return DriverType.Direct3D9;
				case ConsoleKey.C: return DriverType.BurningsVideo;
				case ConsoleKey.D: return DriverType.Software;
				case ConsoleKey.E: return DriverType.Null;
				default: return null;
			}
		}
	}
}
