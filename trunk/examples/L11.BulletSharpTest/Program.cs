using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

// NOTE: this example requires BulletSharp.dll for compiling and for running.

// Well, I don't want to ship 1.6 megs dll with Lime just for this example.
// In future if there are will be more examples using BulletSharp.dll - probably i will include it into Lime package.
// For now I will left it like this - if you want to see example running - you should download dll manually.
// See checkBulletSharpDllPresence() implementation for more details: what url and what version to use.

namespace L11.BulletSharpTest
{
	class Program
	{
		const float worldGravity = 200;
		const float cubeMass = 1;
		const float cubeSize = 40;
		const float sphereMass = cubeMass * 5;
		const float sphereRadius = cubeSize * 0.75f;

		static IrrlichtDevice device;
		static Physics physics;
		static Particles particles;
		static bool simPaused = false;
		static bool useTrails = false;

		static void Main(string[] args)
		{
			checkBulletSharpDllPresence();

			// setup Irrlicht

			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1024, 768));
			if (device == null)
				return;

			device.SetWindowCaption("BulletSharp Test - Irrlicht Engine");
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;
			GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");

			CameraSceneNode camera = scene.AddCameraSceneNodeFPS();
			camera.Position = new Vector3Df(100, 800, -1000);
			camera.Target = new Vector3Df(0, 100, 0);
			camera.FarValue = 30000;
			camera.AutomaticCulling = CullingType.FrustumBox;

			device.CursorControl.Visible = false;

			// setup physics

			physics = new Physics();
			physics.Setup(new Vector3Df(0, -worldGravity, 0));

			// setup particles

			particles = new Particles(device);

			// load quake level

			device.FileSystem.AddFileArchive("../../media/map-20kdm2.pk3");

			Mesh mesh = scene.GetMesh("20kdm2.bsp").GetMesh(0);
			SceneNode quakeLevel = scene.AddOctreeSceneNode(mesh, null, -1, 1024);
			quakeLevel.Position = new Vector3Df(-1300, -144, -1249);

			physics.AddShape(Physics.Shape.Mesh, quakeLevel);

			// generate dynamic objects

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						MeshSceneNode n = scene.AddCubeSceneNode(cubeSize);
						n.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
						n.SetMaterialFlag(MaterialFlag.Lighting, false);
						n.Position = new Vector3Df(70 + i * cubeSize, 520 + j * cubeSize, -650 + k * cubeSize);

						physics.AddShape(Physics.Shape.Box, n, cubeMass);
					}
				}
			}

			// main loop

			uint curTime = 0;
			uint lastTime = 0;
			int simFps = 0;
			int simFrames = 0;
			uint simFramesTime = 0;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					// simulate physics

					lastTime = curTime;
					curTime = device.Timer.Time;
					if (!simPaused)
					{
						float deltaTime = (curTime - lastTime) / 1000.0f;
						bool b = physics.StepSimulation(deltaTime);
						if (b) simFrames++;
					}

					if (curTime - simFramesTime > 1000)
					{
						simFramesTime = curTime;
						simFps = simFrames;
						simFrames = 0;
					}

					// winnow particles

					particles.Winnow(curTime, simPaused);

					// render scene

					driver.BeginScene(true, true, new Color(40, 80, 160));
					scene.DrawAll();

					Material material = new Material();
					material.Lighting = false;
					device.VideoDriver.SetMaterial(material);

					// display stats

					driver.Draw2DRectangle(new Recti(10, 10, 140, 180), new Color(0x7f000000));

					Vector2Di v = new Vector2Di(20, 20);
					font.Draw("Rendering", v, Color.OpaqueYellow);
					v.Y += 16;
					font.Draw(scene.Attributes.GetValue("calls") + " nodes", v, Color.OpaqueWhite);
					v.Y += 16;
					font.Draw(driver.FPS + " fps", v, Color.OpaqueWhite);
					v.Y += 32;
					font.Draw("Physics" + (simPaused ? " (paused)" : ""), v, Color.OpaqueYellow);
					v.Y += 16;
					font.Draw(physics.NumCollisionObject + " shapes", v, Color.OpaqueWhite);
					v.Y += 16;
					font.Draw(simFps + " fps", v, Color.OpaqueWhite);
					v.Y += 32;
					font.Draw("[T]rails " + (useTrails ? "ON" : "OFF"), v, Color.OpaqueGreen);

					driver.EndScene();
				}

				device.Yield();
			}

			// drop

			physics.Drop();
			device.Drop();
		}

		static bool mouseCanShoot = true;
		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Key &&
				evnt.Key.PressedDown)
			{
				switch (evnt.Key.Key)
				{
					case KeyCode.Space:
						simPaused = !simPaused;
						return true;

					case KeyCode.KeyT:
						useTrails = !useTrails;
						return true;
				}
			}

			if (evnt.Type == EventType.Mouse)
			{
				if (evnt.Mouse.IsLeftPressed())
				{
					if (!mouseCanShoot)
						return true;

					MeshSceneNode n = device.SceneManager.AddSphereSceneNode(sphereRadius);
					n.SetMaterialTexture(0, device.VideoDriver.GetTexture("../../media/wall.bmp"));
					n.SetMaterialFlag(MaterialFlag.Lighting, false);

					Vector3Df v = (device.SceneManager.ActiveCamera.Target - device.SceneManager.ActiveCamera.Position).Normalize();
					n.Position = device.SceneManager.ActiveCamera.Position + v * 100;

					if (useTrails)
						particles.Add(n, device.Timer.Time);

					physics.AddShape(Physics.Shape.Shpere, n, sphereMass, false, v * cubeMass * 10000);

					mouseCanShoot = false;
					return true;
				}
				else
				{
					mouseCanShoot = true;
				}
			}

			return false;
		}

		static void checkBulletSharpDllPresence()
		{
			const string bulletSharpDllFilename = "BulletSharp.dll";
			const string bulletSharpUrl = "https://code.google.com/p/bulletsharp/";
			const string bulletSharpDllUrl = "https://code.google.com/p/bulletsharp/downloads/detail?name=bulletsharp-2.80-sp1.zip";

			if (System.IO.File.Exists(bulletSharpDllFilename))
				return;

			Console.ForegroundColor = ConsoleColor.Yellow;
			Console.WriteLine(bulletSharpDllFilename + " not found.");
			Console.ForegroundColor = ConsoleColor.Gray;
			Console.WriteLine();
			Console.WriteLine("If you want to run this example you have to place it near this EXE file.");
			Console.WriteLine("This example was tested with bulletsharp-2.80-sp1 a \"Release NoGfx\" dll.");
			Console.WriteLine("You can get it from " + bulletSharpUrl);
			Console.WriteLine();
			Console.WriteLine("Press any key to exit or F1 if you want to navigate your web browser right now.");

			ConsoleKeyInfo k = Console.ReadKey();
			if (k.Key == ConsoleKey.F1)
				System.Diagnostics.Process.Start(bulletSharpDllUrl);

			Environment.Exit(0);
		}
	}
}
