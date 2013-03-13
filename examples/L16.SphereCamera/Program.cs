using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Video;
using IrrlichtLime.Core;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L16.SphereCamera
{
	class Program
	{
		static IrrlichtDevice device;
		static VideoDriver driver;
		static SceneManager scene;

		static MeshSceneNode sphere;
		static SphereCamera camera;
		static SpherePath path;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(800, 600));
			device.SetWindowCaption("Sphere Camera - Irrlicht Engine");
			driver = device.VideoDriver;
			scene = device.SceneManager;

			sphere = scene.AddSphereSceneNode(5, 100);
			sphere.SetMaterialTexture(0, driver.GetTexture("../../media/earth.jpg"));
			sphere.TriangleSelector = scene.CreateTriangleSelector(sphere.Mesh, sphere);
			sphere.TriangleSelector.Drop();

			scene.AmbientLight = new Colorf(0.2f, 0.2f, 0.2f);
			LightSceneNode light = scene.AddLightSceneNode();
			light.Position = new Vector3Df(-10, 10, -10);

			camera = new SphereCamera(device, new Vector3Df(0), 8, 20, 10, 0, 0);
			camera.Inclination = 200;

			path = new SpherePath(5.4f);

			GUIFont font = device.GUIEnvironment.BuiltInFont;
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.PostEvent(new Event('r', KeyCode.KeyR, true)); // pretend user pressed [R]

			while (device.Run())
			{
				driver.BeginScene();

				scene.DrawAll();

				path.Draw(driver);

				font.Draw("Press [Arrows], [LMB] and [Mouse Scroll] to change view", 10, 10, Color.OpaqueYellow);
				font.Draw("Press [RMB] on Earth to place new path point", 10, 20, Color.OpaqueYellow);
				font.Draw("Press [R] to reload path data from file", 10, 30, Color.OpaqueYellow);
				font.Draw("Press [C] to clean up", 10, 40, Color.OpaqueYellow);

				font.Draw(driver.FPS.ToString() + " fps", 10, driver.ScreenSize.Height - 40, Color.OpaqueYellow);
				font.Draw(path.PointCount.ToString() + " point(s)", 10, driver.ScreenSize.Height - 30, Color.OpaqueYellow);
				font.Draw(camera.ToString(), 10, driver.ScreenSize.Height - 20, Color.OpaqueYellow);

				driver.EndScene();
			}

			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Mouse &&
				evnt.Mouse.Type == MouseEventType.RightDown)
			{
				Vector3Df v;
				Triangle3Df t;
				SceneNode n;

				Line3Df l = scene.SceneCollisionManager.GetRayFromScreenCoordinates(new Vector2Di(evnt.Mouse.X, evnt.Mouse.Y));
				if (scene.SceneCollisionManager.GetCollisionPoint(l, sphere.TriangleSelector, out v, out t, out n))
				{
					path.AddPoint(v);
					return true;
				}
			}

			if (evnt.Type == EventType.Key)
			{
				switch (evnt.Key.Key)
				{
					case KeyCode.Left:
						camera.Inclination++;
						return true;

					case KeyCode.Right:
						camera.Inclination--;
						return true;

					case KeyCode.Up:
						camera.Azimuth--;
						return true;

					case KeyCode.Down:
						camera.Azimuth++;
						return true;

					case KeyCode.KeyC:
						path.Clear();
						return true;

					//case KeyCode.KeyS:
					//    path.Save("../../media/SphereCameraPath.xml");
					//    return true;

					case KeyCode.KeyR:
						path.Load("../../media/SphereCameraPath.xml");
						return true;
				}
			}

			return false;
		}
	}
}
