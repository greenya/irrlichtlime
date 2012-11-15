using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L15.AbstractTrace
{
	class Program
	{
		static IrrlichtDevice device;
		static AbstractTrace trace;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1280, 720));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			CameraSceneNode camera = scene.AddCameraSceneNode();
			camera.FarValue = 20000;
			SceneNodeAnimator a = scene.CreateFlyCircleAnimator(new Vector3Df(), (AbstractTrace.CubeSize * AbstractTrace.GridDim) / 1.25f, 0.000025f, new Vector3Df(0.1f, 1, 0));
			camera.AddAnimator(a);
			a.Drop();

			trace = new AbstractTrace(device);
			trace.Init();

			int lastFps = -1;
			while (device.Run())
			{
				driver.BeginScene();
				scene.DrawAll();
				trace.Step();
				trace.Draw();
				driver.EndScene();

				int fps = driver.FPS;
				if (fps != lastFps)
				{
					device.SetWindowCaption("Abstract Trace - Irrlicht Engine [" + fps + " fps; " + trace.GetTotalCubeCount() + " cubes]");
					lastFps = fps;
				}
			}

			trace.Drop();
			device.Drop();
		}
	}
}
