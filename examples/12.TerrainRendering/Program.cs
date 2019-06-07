﻿using System;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _12.TerrainRendering
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
			GUIEnvironment env = device.GUIEnvironment;

			driver.SetTextureCreationFlag(TextureCreationFlag.Always32Bit, true);

			// add irrlicht logo
			env.AddImage(driver.GetTexture("../../media/irrlichtlogoalpha2.tga"), new Vector2Di(10));

			// set gui font
			env.Skin.SetFont(env.GetFont("../../media/fontlucida.png"));

			// add some help text
			env.AddStaticText(
				"Press 'W' to change wireframe mode\nPress 'D' to toggle detail map\nPress 'S' to toggle skybox/skydome",
				new Recti(10, 421, 250, 475), true, true, null, -1, true);

			// add camera
			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS(null, 100.0f, 1.2f);
			camera.Position = new Vector3Df(2700 * 2, 255 * 2, 2600 * 2);
			camera.Target = new Vector3Df(2397 * 2, 343 * 2, 2700 * 2);
			camera.FarValue = 42000.0f;

			// disable mouse cursor
			device.CursorControl.Visible = false;

			// add terrain scene node
			TerrainSceneNode terrain = smgr.AddTerrainSceneNode(
				"../../media/terrain-heightmap.bmp",	// heightmap
				null,								// parent node
				-1,									// node id
				new Vector3Df(),					// position
				new Vector3Df(),					// rotation
				new Vector3Df(40, 4.4f, 40),		// scale
				new Color(255, 255, 255),			// vertex color
				5,									// max LOD
				TerrainPatchSize._17,				// patch size
				4);									// smooth factor

			terrain.SetMaterialFlag(MaterialFlag.Lighting, false);
			terrain.SetMaterialTexture(0, driver.GetTexture("../../media/terrain-texture.jpg"));
			terrain.SetMaterialTexture(1, driver.GetTexture("../../media/detailmap3.jpg"));
			terrain.SetMaterialType(MaterialType.DetailMap);

			terrain.ScaleTexture(1, 20);

			// create triangle selector for the terrain
			TriangleSelector selector = smgr.CreateTerrainTriangleSelector(terrain, 0);
			terrain.TriangleSelector = selector;

			// create collision response animator and attach it to the camera
			SceneNodeAnimator anim = smgr.CreateCollisionResponseAnimator(
				selector, camera,
				new Vector3Df(60, 100, 60),
				new Vector3Df(0, 0, 0),
				new Vector3Df(0, 50, 0));

			selector.Drop();
			camera.AddAnimator(anim);
			anim.Drop();

			// create skybox and skydome
			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, false);

			SceneNode skybox = smgr.AddSkyBoxSceneNode(
				"../../media/irrlicht2_up.jpg",
				"../../media/irrlicht2_dn.jpg",
				"../../media/irrlicht2_lf.jpg",
				"../../media/irrlicht2_rt.jpg",
				"../../media/irrlicht2_ft.jpg",
				"../../media/irrlicht2_bk.jpg");

			SceneNode skydome = smgr.AddSkyDomeSceneNode(driver.GetTexture("../../media/skydome.jpg"), 16, 8, 0.95f, 2);

			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, true);

			// create event receiver
			new MyEventReceiver(device, terrain, skybox, skydome);

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(ClearBufferFlag.All, new Color(0));

					smgr.DrawAll();
					env.DrawAll();

					driver.EndScene();

					// display frames per second in window title
					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						// also print terrain height of current camera position
						// we can use camera position because terrain is located at coordinate origin

						device.SetWindowCaption(String.Format(
							"Terrain rendering example - Irrlicht Engine [{0}] fps: {1} Height: {2}",
							driver.Name, fps, terrain.GetHeight(camera.AbsolutePosition.X, camera.AbsolutePosition.Z)));

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

	class MyEventReceiver
	{
		public MyEventReceiver(IrrlichtDevice device, SceneNode terrain, SceneNode skybox, SceneNode skydome)
		{
			this.terrain = terrain;
			this.skybox = skybox;
			this.skydome = skydome;
			showBox = true;
			showDebug = false;

			skybox.Visible = true;
			skydome.Visible = false;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
		}

		bool device_OnEvent(Event e)
		{
			// check if user presses the key 'W', 'P', 'D', 'S' or 'X'
			if (e.Type == EventType.Key && e.Key.PressedDown)
			{
				switch (e.Key.Key)
				{
					case KeyCode.KeyW: // switch wire frame mode
						terrain.SetMaterialFlag(MaterialFlag.Wireframe, !terrain.GetMaterial(0).Wireframe);
						terrain.SetMaterialFlag(MaterialFlag.PointCloud, false);
						return true;

					case KeyCode.KeyP: // switch point cloud mode
						terrain.SetMaterialFlag(MaterialFlag.PointCloud, !terrain.GetMaterial(0).PointCloud);
						terrain.SetMaterialFlag(MaterialFlag.Wireframe, false);
						return true;

					case KeyCode.KeyD: // toggle detail map
						terrain.SetMaterialType(terrain.GetMaterial(0).Type == MaterialType.Solid ?
							MaterialType.DetailMap : MaterialType.Solid);
						return true;

					case KeyCode.KeyS: // toggle skies
						showBox = !showBox;
						skybox.Visible = showBox;
						skydome.Visible = !showBox;
						return true;

					case KeyCode.KeyX: // toggle debug information
						showDebug = !showDebug;
						terrain.DebugDataVisible = showDebug ? DebugSceneType.BBoxAll : DebugSceneType.Off;
						return true;
				}
			}

			return false;
		}

		SceneNode terrain;
		SceneNode skybox;
		SceneNode skydome;
		bool showBox;
		bool showDebug;
	}
}
