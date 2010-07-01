using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _02.Quake3Map
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;

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
					return;
			}

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			device.FileSystem.AddFileArchive("../media/map-20kdm2.pk3");

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
					driver.BeginScene(true, true, new Color(200, 200, 200));
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
		}
	}
}
