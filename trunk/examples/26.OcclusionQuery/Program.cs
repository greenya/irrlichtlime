using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _26.OcclusionQuery
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
			SceneManager scene = device.SceneManager;

			scene.GUIEnvironment.AddStaticText("Press Space to hide occluder.", new Recti(10, 10, 200, 50));

			// Create the node to be occluded. We create a sphere node with high poly count.

			MeshSceneNode node = scene.AddSphereSceneNode(10, 64);

			if (node != null)
			{
				node.Position = new Vector3Df(0, 0, 60);
				node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
				node.SetMaterialFlag(MaterialFlag.Lighting, false);
			}

			// Now we create another node, the occluder. It's a simple plane.

			SceneNode plane = scene.AddMeshSceneNode(
				scene.AddHillPlaneMesh("plane", new Dimension2Df(10), new Dimension2Di(2)), // mesh
				null, // parent
				-1, // id
				new Vector3Df(0, 0, 20), // position
				new Vector3Df(270, 0, 0)); // rotation

			if (plane != null)
			{
				plane.SetMaterialTexture(0, driver.GetTexture("../../media/t351sml.jpg"));
				plane.SetMaterialFlag(MaterialFlag.Lighting, false);
				plane.SetMaterialFlag(MaterialFlag.BackFaceCulling, true);
			}
			
			// Here we create the occlusion query. Because we don't have a plain mesh scene node
			// (SceneNodeType.Mesh or SceneNodeType.AnimatedMesh), we pass the base geometry as well. Instead,
			// we could also pass a simpler mesh or the bounding box. But we will use a time
			// based method, where the occlusion query renders to the frame buffer and in case
			// of success (occlusion), the mesh is not drawn for several frames.

			driver.AddOcclusionQuery(node, node.Mesh);

			// We have done everything, just a camera and draw it. We also write the
			// current frames per second and the name of the driver to the caption of the
			// window to examine the render speedup.
			// We also store the time for measuring the time since the last occlusion query ran
			// and store whether the node should be visible in the next frames.

			scene.AddCameraSceneNode();
			uint timeNow = device.Timer.Time;
			bool nodeVisible = true;

			while (device.Run())
			{
				plane.Visible = !IsKeyDown(KeyCode.Space);

				driver.BeginScene(true, true, new Color(113, 113, 133));

				// First, we draw the scene, possibly without the occluded element. This is necessary
				// because we need the occluder to be drawn first. You can also use several scene
				// managers to collect a number of possible occluders in a separately rendered scene.

				node.Visible = nodeVisible;
				scene.DrawAll();
				scene.GUIEnvironment.DrawAll();

				// Once in a while, here every 100 ms, we check the visibility. We run the queries,
				// update the pixel value, and query the result. Since we already rendered the node
				// we render the query invisible. The update is made blocking, as we need the result
				// immediately. If you don't need the result immediately, e.g. because oyu have other
				// things to render, you can call the update non-blocking. This gives the GPU more
				// time to pass back the results without flushing the render pipeline.
				// If the update was called non-blocking, the result from getOcclusionQueryResult is
				// either the previous value, or 0xffffffff if no value has been generated at all, yet.
				// The result is taken immediately as visibility flag for the node.

				if (device.Timer.Time - timeNow > 100)
				{
					driver.RunAllOcclusionQueries(false);
					driver.UpdateAllOcclusionQueries();
					nodeVisible = driver.GetOcclusionQueryResult(node) > 0;
					timeNow = device.Timer.Time;
				}

				driver.EndScene();

				device.SetWindowCaption(String.Format(
					"Occlusion Query Example - Irrlicht Engine [{0}] fps: {1} (primitives: {2})",
					driver.Name, driver.FPS, driver.PrimitiveCountDrawn));
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
