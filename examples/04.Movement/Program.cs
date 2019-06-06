using System;
using System.Collections.Generic;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _04.Movement
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

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			SceneNode node = smgr.AddSphereSceneNode();
			if (node != null)
			{
				node.Position = new Vector3Df(0, 0, 30);
				node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
				node.SetMaterialFlag(MaterialFlag.Lighting, false);
			}

			SceneNode n = smgr.AddCubeSceneNode();
			if (n != null)
			{
				n.SetMaterialTexture(0, driver.GetTexture("../../media/t351sml.jpg"));
				n.SetMaterialFlag(MaterialFlag.Lighting, false);

				SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 0, 30), 20.0f);
				if (anim != null)
				{
					n.AddAnimator(anim);
					anim.Drop();
				}
			}

			AnimatedMeshSceneNode anms = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/ninja.b3d"));
			if (anms != null)
			{
				SceneNodeAnimator anim = smgr.CreateFlyStraightAnimator(
					new Vector3Df(100, 0, 60), new Vector3Df(-100, 0, 60), 3.5f, true);
				if (anim != null)
				{
					anms.AddAnimator(anim);
					anim.Drop();
				}

				anms.SetMaterialFlag(MaterialFlag.Lighting, false);

				anms.SetFrameLoop(0, 13);
				anms.AnimationSpeed = 15;

				anms.Scale = new Vector3Df(2);
				anms.Rotation = new Vector3Df(0, -90, 0);
			}

			smgr.AddCameraSceneNodeFPS();
			device.CursorControl.Visible = false;

			device.GUIEnvironment.AddImage(
				driver.GetTexture("../../media/irrlichtlogoalpha2.tga"),
				new Vector2Di(10, 20));

			int lastFPS = -1;

			uint then = device.Timer.Time;
			
			const float MOVEMENT_SPEED = 5.0f;

			while (device.Run())
			{
				uint now = device.Timer.Time;
				float frameDeltaTime = (float)(now - then) / 1000.0f;
				then = now;

				Vector3Df nodePosition = node.Position;

				if (IsKeyDown(KeyCode.KeyW))
					nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
				else if (IsKeyDown(KeyCode.KeyS))
					nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

				if (IsKeyDown(KeyCode.KeyA))
					nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
				else if (IsKeyDown(KeyCode.KeyD))
					nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

				node.Position = nodePosition;

				driver.BeginScene(ClearBufferFlag.All, new Color(113, 113, 113));
				smgr.DrawAll();
				device.GUIEnvironment.DrawAll();
				driver.EndScene();

				int fps = driver.FPS;
				if (lastFPS != fps)
				{
					device.SetWindowCaption(String.Format(
						"Movement example - Irrlicht Engine [{0}] fps: {1}",
						driver.Name, fps));

					lastFPS = fps;
				}
			}

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
