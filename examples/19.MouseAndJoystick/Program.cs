using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _19.MouseAndJoystick
{
	class Program
	{
		static void Main(string[] args)
		{
			// Initialize device.
			
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			// Add event handling.

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			// Save important pointers.

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;
			Logger logger = device.Logger;

			// Initialize joysticks and print info about them.

			List<JoystickInfo> joystickList = device.ActivateJoysticks();
			if (joystickList != null)
			{
				logger.Log("Joystick support is enabled and " + joystickList.Count.ToString() + " joystick(s) are present.");

				foreach (JoystickInfo j in joystickList)
				{
					logger.Log("Joystick " + j.Joystick.ToString() + ":");
					logger.Log("\tName: \"" + j.Name + "\"");
					logger.Log("\tAxisCount: " + j.AxisCount.ToString());
					logger.Log("\tButtonCount: " + j.ButtonCount.ToString());
					logger.Log("\tPovHat: " + j.PovHat.ToString());
				}
			}
			else
			{
				logger.Log("Joystick support is not enabled.");
			}

			device.SetWindowCaption("Mouse and joystick - Irrlicht Lime - " + joystickList.Count.ToString() + " joystick(s)");

			// Create an arrow mesh and move it around either with the joystick axis/hat,
			// or make it follow the mouse pointer (when no joystick movement).

			SceneNode node = smgr.AddMeshSceneNode(
				smgr.AddArrowMesh(
					"Arrow",
					new Color(255, 0, 0),
					new Color(0, 255, 0),
					16, 16,
					2.0f, 1.3f,
					0.1f, 0.6f
				)
			);

			node.SetMaterialFlag(MaterialFlag.Lighting, false);

			CameraSceneNode camera = smgr.AddCameraSceneNode();
			camera.Position = new Vector3Df(0, 0, -10);

			// As in example #4, we'll use framerate independent movement.
			uint then = device.Timer.Time;
			const float MovementSpeed = 5.0f;

			// Run main cycle.

			while (device.Run())
			{
				// Work out a frame delta time.
				uint now = device.Timer.Time;
				float frameDeltaTime = (float)(now - then) / 1000.0f; // in seconds
				then = now;

				bool movedWithJoystick = false;
				Vector3Df nodePosition = node.Position;

				if (joystickList.Count > 0)
				{
					float moveHorizontal = 0.0f; // range is -1.0 for full left to +1.0 for full right
					float moveVertical = 0.0f; // range is -1.0 for full down to +1.0 for full up

					// We receive the full analog range of the axes, and so have to implement our own dead zone.
					// This is an empirical value, since some joysticks have more jitter or creep around the center
					// point than others. We'll use 5% of the range as the dead zone, but generally you would want
					// to give the user the option to change this.
					float DeadZone = 0.05f;

					moveHorizontal = joystickState.Axis[0] / 32767.0f; // "0" for X axis
					if (Math.Abs(moveHorizontal) < DeadZone)
						moveHorizontal = 0.0f;

					moveVertical = joystickState.Axis[1] / -32767.0f; // "1" for Y axis
					if (Math.Abs(moveVertical) < DeadZone)
						moveVertical = 0.0f;

					// POV will contain 65535 if POV hat info no0t supported, so we can check its range.
					ushort povDegrees = (ushort)(joystickState.POV / 100);
					if (povDegrees < 360)
					{
						if (povDegrees > 0 && povDegrees < 180)
							moveHorizontal = +1.0f;
						else if (povDegrees > 180)
							moveHorizontal = -1.0f;

						if (povDegrees > 90 && povDegrees < 270)
							moveVertical = -1.0f;
						else if (povDegrees > 270 || povDegrees < 90)
							moveVertical = +1.0f;
					}

					// If we have any movement, apply it.
					if (Math.Abs(moveHorizontal) > 0.0001f || Math.Abs(moveVertical) > 0.0001f)
					{
						float m = frameDeltaTime * MovementSpeed;
						nodePosition = new Vector3Df(moveHorizontal * m, moveVertical * m, nodePosition.Z);
						movedWithJoystick = true;
					}
				}

				// If the arrow node isn't being moved with the joystick, then have it follow the mouse cursor.
				if (!movedWithJoystick)
				{
					// Create a ray through the mouse cursor.
					Line3Df ray = smgr.SceneCollisionManager.GetRayFromScreenCoordinates(mouseState.Position, camera);

					// And intersect the ray with a plane around the node facing towards the camera.
					Plane3Df plane = new Plane3Df(nodePosition, new Vector3Df(0, 0, -1));
					Vector3Df mousePosition;
					if (plane.GetIntersectionWithLine(ray.Start, ray.Vector, out mousePosition))
					{
						// We now have a mouse position in 3d space; move towards it.
						Vector3Df toMousePosition = mousePosition - nodePosition;
						float availableMovement = frameDeltaTime * MovementSpeed;

						if (toMousePosition.Length <= availableMovement)
							nodePosition = mousePosition; // jump to the final position
						else
							nodePosition += toMousePosition.Normalize() * availableMovement; // move towards it
					}
				}

				node.Position = nodePosition;

				// Turn lighting on and off depending on whether the left mouse button is down.
				node.SetMaterialFlag(MaterialFlag.Lighting, mouseState.IsLeftButtonDown);

				// Draw all.
				driver.BeginScene(true, true, new Color(113, 113, 133));
				smgr.DrawAll();
				driver.EndScene();
			}

			// Drop the device.

			device.Drop();
		}

		// We'll create a class to record info on the mouse state.
		class MouseStateInfo
		{
			public Vector2Di Position = new Vector2Di();
			public bool IsLeftButtonDown = false;
		}

		static MouseStateInfo mouseState = new MouseStateInfo();
		static Event.JoystickEvent joystickState;

		static bool device_OnEvent(Event evnt)
		{
			// Remember the mouse state.
			if (evnt.Type == EventType.Mouse)
			{
				switch (evnt.Mouse.Type)
				{
					case MouseEventType.LeftDown:
						mouseState.IsLeftButtonDown = true;
						break;

					case MouseEventType.LeftUp:
						mouseState.IsLeftButtonDown = false;
						break;

					case MouseEventType.Move:
						mouseState.Position = new Vector2Di(evnt.Mouse.X, evnt.Mouse.Y);
						break;
					
					default:
						// We won't use any other mouse events.
						break;
				}
			}

			// The state of each connected joystick is sent to us once every run() of the Irrlicht device.
			// Store the state of the first joystick, ignoring other joysticks.
			if (evnt.Type == EventType.Joystick &&
				evnt.Joystick.Joystick == 0)
			{
				joystickState = evnt.Joystick;
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
