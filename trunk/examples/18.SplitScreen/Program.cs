using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _18.SplitScreen
{
	class Program
	{
		// resolution
		static int ResX = 800;
		static int ResY = 600;
		static bool fullScreen = false;

		// use split screen ?
		static bool splitScreen = true;

		// cameras
		static CameraSceneNode[] camera = new CameraSceneNode[4] { null, null, null, null };

		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(ResX, ResY), 32, fullScreen);
			if (device == null)
				return;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			// load model
			AnimatedMesh model = smgr.GetMesh("../media/sydney.md2");
			if (model == null)
				return;

			AnimatedMeshSceneNode model_node = smgr.AddAnimatedMeshSceneNode(model);

			// load texture
			if (model_node != null)
			{
				Texture texture = driver.GetTexture("../media/sydney.bmp");
				model_node.SetMaterialTexture(0, texture);
				model_node.SetMD2Animation(AnimationTypeMD2.Run);
				model_node.SetMaterialFlag(MaterialFlag.Lighting, false);
			}

			// load map
			device.FileSystem.AddFileArchive("../media/map-20kdm2.pk3");
			AnimatedMesh map = smgr.GetMesh("20kdm2.bsp");
			if (map != null)
			{
				SceneNode map_node = smgr.AddOctreeSceneNode(map.GetMesh(0));
				map_node.Position = new Vector3Df(-850, -220, -850);
			}

			// create 3 fixed and one user-controlled cameras
			camera[0] = smgr.AddCameraSceneNode(null, new Vector3Df(50, 0, 0), new Vector3Df(0)); // font
			camera[1] = smgr.AddCameraSceneNode(null, new Vector3Df(0, 50, 0), new Vector3Df(0)); // top
			camera[2] = smgr.AddCameraSceneNode(null, new Vector3Df(0, 0, 50), new Vector3Df(0)); // left
			camera[3] = smgr.AddCameraSceneNodeFPS(); // user-controlled
			camera[3].Position = new Vector3Df(-50, 0, -50);

			device.CursorControl.Visible = false;

			int lastFPS = -1;

			while (device.Run())
			{
				// set the viewpoint to the whole screen and begin scene
				driver.ViewPort = new Recti(0, 0, ResX, ResY);
				driver.BeginScene(true, true, new Color(100, 100, 100));

				if (splitScreen)
				{
					smgr.ActiveCamera = camera[0];
					driver.ViewPort = new Recti(0, 0, ResX / 2, ResY / 2); // top left
					smgr.DrawAll();

					smgr.ActiveCamera = camera[1];
					driver.ViewPort = new Recti(ResX / 2, 0, ResX, ResY / 2); // top right
					smgr.DrawAll();

					smgr.ActiveCamera = camera[2];
					driver.ViewPort = new Recti(0, ResY / 2, ResX / 2, ResY); // bottom left
					smgr.DrawAll();

					driver.ViewPort = new Recti(ResX / 2, ResY / 2, ResX, ResY); // bottom right
				}

				smgr.ActiveCamera = camera[3];
				smgr.DrawAll();

				driver.EndScene();

				int fps = driver.FPS;
				if (lastFPS != fps)
				{
					device.SetWindowCaption(String.Format(
						"Split Screen example - Irrlicht Engine [{0}] fps: {1}",
						driver.Name, fps));

					lastFPS = fps;
				}
			}

			device.Drop();
		}

		static bool device_OnEvent(Event e)
		{
			// key S enables/disables split screen
			if (e.Type == EventType.Key &&
				e.Key.Key == KeyCode.KeyS &&
				e.Key.PressedDown)
			{
				splitScreen = !splitScreen;
				return true;
			}

			return false;
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
}
