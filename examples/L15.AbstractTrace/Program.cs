using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L15.AbstractTrace
{
	class Program
	{
		static IrrlichtDevice device;
		static AbstractTrace trace;

		static bool drawGenerator = false;
		static bool isPaused = false;

		static void Main()
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1280, 720));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			device.SetWindowCaption("Abstract Trace - Irrlicht Engine");
			device.OnEvent += Device_OnEvent;

			GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");
			Color textColor = Color.SolidWhite;

			CameraSceneNode camera = scene.AddCameraSceneNode();
			camera.FarValue = 20000;
			SceneNodeAnimator a = scene.CreateFlyCircleAnimator(new Vector3Df(), (AbstractTrace.CubeSize * AbstractTrace.GridDim) / 1.25f, 0.000025f, new Vector3Df(0.1f, 1, 0));
			camera.AddAnimator(a);
			a.Drop();

			trace = new AbstractTrace(device);
			trace.Init();

			while (device.Run())
			{
				driver.BeginScene();
				scene.DrawAll();

				if (!isPaused)
					trace.Step();

				trace.Draw(drawGenerator);

				font.Draw("[G]enerator: " + (drawGenerator ? "ON" : "OFF"), new Vector2Di(20, 20), textColor);
				font.Draw("[P]ause: " + (isPaused ? "ON" : "OFF"), new Vector2Di(20, 35), textColor);
				font.Draw("Cubes: " + trace.GetTotalCubeCount(), new Vector2Di(20, 50), textColor);
				font.Draw("FPS: " + driver.FPS, new Vector2Di(20, 65), textColor);

				driver.EndScene();
			}

			trace.Drop();
			device.Drop();
		}

		private static bool Device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Key && evnt.Key.PressedDown)
			{
				if (evnt.Key.Key == KeyCode.KeyG)
				{
					drawGenerator = !drawGenerator;
					return true;
				}

				if (evnt.Key.Key == KeyCode.KeyP)
				{
					isPaused = !isPaused;
					return true;
				}
			}

			return false;
		}
	}
}
