using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L06.AnalogueClock
{
	class Program
	{
		static void Main(string[] args)
		{
			IrrlichtDevice device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9);
			device.SetWindowCaption("Analogue Clock - Irrlicht Lime");
			device.CursorControl.Visible = false;

			ClockNode.AddClockNode(device.SceneManager.RootNode);

			CameraSceneNode camera = device.SceneManager.AddCameraSceneNodeFPS(null, 100, 0.1f);
			camera.Position = new Vector3Df(40, -20, -100); // start up position
			camera.Target = new Vector3Df(); // prev position change has also moved target, so we update it

			while (device.Run())
			{
				device.VideoDriver.BeginScene();

				device.SceneManager.DrawAll();

				string s = string.Format(
					"{0}\n{1}\n{2}\n{3} tris\n{4} fps",
					device.Timer.RealTimeAndDate,
					device.VideoDriver.VendorInfo,
					device.VideoDriver.Name,
					device.VideoDriver.PrimitiveCountDrawn,
					device.VideoDriver.FPS);

				device.GUIEnvironment.BuiltInFont.Draw(s, 11, 11, new Color(0, 0, 0));
				device.GUIEnvironment.BuiltInFont.Draw(s, 10, 10, new Color(255, 255, 255));

				device.VideoDriver.EndScene();
			}

			device.Drop();
		}
	}
}
