using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _04.Movement
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

				driver.BeginScene(true, true, new Color(113, 113, 113));
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
