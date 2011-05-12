using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _13.RenderToTexture
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;
			GUIEnvironment env = device.GUIEnvironment;

			// load and display animated fairy mesh
			AnimatedMeshSceneNode fairy = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/faerie.md2"));
			if (fairy != null)
			{
				fairy.SetMaterialTexture(0, driver.GetTexture("../../media/faerie2.bmp")); // set diffuse texture
				fairy.SetMaterialFlag(MaterialFlag.Lighting, true); // enable dynamic lighting
				fairy.GetMaterial(0).Shininess = 20.0f; // set size of specular highlights
				fairy.Position = new Vector3Df(-10, 0, -100);
				fairy.SetMD2Animation(AnimationTypeMD2.Stand);
			}

			// add white light
			smgr.AddLightSceneNode(null, new Vector3Df(-15, 5, -105), new Colorf(1, 1, 1));

			// set ambient light
			smgr.AmbientLight = new Colorf(0.25f, 0.25f, 0.25f);

			// add fps camera
			CameraSceneNode fpsCamera = smgr.AddCameraSceneNodeFPS();
			fpsCamera.Position = new Vector3Df(-50, 50, -150);

			// disable mouse cursor
			device.CursorControl.Visible = false;

			// create test cube
			SceneNode test = smgr.AddCubeSceneNode(60);

			// let the cube rotate and set some light settings
			SceneNodeAnimator anim = smgr.CreateRotationAnimator(new Vector3Df(0.3f, 0.3f, 0));

			test.Position = new Vector3Df(-100, 0, -100);
			test.SetMaterialFlag(MaterialFlag.Lighting, false); // disable dynamic lighting
			test.AddAnimator(anim);
			anim.Drop();

			// create render target
			Texture rt = null;
			CameraSceneNode fixedCam = null;

			if (driver.QueryFeature(VideoDriverFeature.RenderToTarget))
			{
				rt = driver.AddRenderTargetTexture(new Dimension2Di(256), "RTT1");
				test.SetMaterialTexture(0, rt); // set material of cube to render target

				// add fixed camera
				fixedCam = smgr.AddCameraSceneNode(null, new Vector3Df(10, 10, -80), new Vector3Df(-10, 10, -100));
			}
			else
			{
				// create problem text
				GUIFont font = env.GetFont("../../media/fonthaettenschweiler.bmp");
				if (font != null)
					env.Skin.SetFont(font);

				GUIStaticText text = env.AddStaticText(
					"Your hardware or this renderer is not able to use the " +
					"render to texture feature. RTT Disabled.",
					new Recti(150, 20, 470, 60));

				text.OverrideColor = new Color(255, 255, 255, 100);
			}

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(true, true, new Color(0));

					if (rt != null)
					{
						// draw scene into render target

						// set render target texture
						driver.SetRenderTarget(rt, true, true, new Color(0, 0, 255));

						// make cube invisible and set fixed camera as active camera
						test.Visible = false;
						smgr.ActiveCamera = fixedCam;

						// draw whole scene into render buffer
						smgr.DrawAll();

						// set back old render target
						// The buffer might have been distorted, so clear it
						driver.SetRenderTarget(null, true, true, new Color(0));

						// make the cube visible and set the user controlled camera as active one
						test.Visible = true;
						smgr.ActiveCamera = fpsCamera;
					}

					// draw scene normally
					smgr.DrawAll();
					env.DrawAll();

					driver.EndScene();

					// display frames per second in window title
					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.SetWindowCaption(String.Format(
							"Render to Texture and Specular Highlights example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
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
