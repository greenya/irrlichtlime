using System;

using IrrlichtLime;
using IrrlichtLime.Video;

namespace L01.TexturePainting
{
	class Program
	{
		static void Main()
		{
			DriverSettingsForm driverSettings = new DriverSettingsForm(
				"Texture paint example",
				"This example shows how to use TexturePainter and render-to-texture (RTT) technique.\n\n" +
				"Use mouse to draw on the 2D image (texture) and see changes on the mesh and on RTT target.");

			if (!driverSettings.ShowDialog())
				return;

			device = IrrlichtDevice.CreateDevice(
				driverSettings.DriverType,
				driverSettings.VideoMode.Resolution,
				driverSettings.VideoMode.Depth,
				driverSettings.Fullscreen);

			if (device == null)
			{
				Console.WriteLine("\nDevice creation failed!\n<Press any key to exit>");
				Console.ReadKey();
				return;
			}

			device.VideoDriver.SetTextureCreationFlag(TextureCreationFlag.AllowMemoryCopy, true);	//workaround: bug in irrlicht

			Application app = new Application(device);

			int lastFPS = -1;
			while (device.Run())
			{
				device.VideoDriver.BeginScene();

				app.Render();

				device.VideoDriver.EndScene();

				int fps = device.VideoDriver.FPS;
				if (fps != lastFPS)
				{
					device.SetWindowCaption(string.Format(
						"Texture painting example - Irrlicht Lime [{0}] {1} fps",
						device.VideoDriver.Name, fps));

					lastFPS = fps;
				}
			}

			device.Drop();
		}

		static IrrlichtDevice device;
	}
}
