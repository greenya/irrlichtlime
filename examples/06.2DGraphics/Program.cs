using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.GUI;

namespace _06._2DGraphics
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(512, 384));
			if (device == null)
				return;

			device.SetWindowCaption("Irrlicht Engine - 2D Graphics Demo");

			VideoDriver driver = device.VideoDriver;

			Texture images = driver.GetTexture("../media/2ddemo.png");
			driver.MakeColorKeyTexture(images, new Vector2Di(0, 0));

			GUIFont font = device.GUIEnvironment.BuiltInFont;
			GUIFont font2 = device.GUIEnvironment.GetFont("../media/fonthaettenschweiler.bmp");

			Recti imp1 = new Recti(349, 15, 385, 78);
			Recti imp2 = new Recti(387, 15, 423, 78);

			driver.Material2D.Layer[0].BilinearFilter = true;
			driver.Material2D.AntiAliasing = AntiAliasingMode.FullBasic;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					uint time = device.Timer.Time;

					driver.BeginScene(true, true, new Coloru(120, 102, 136));

					// draw fire & dragons background world
					driver.Draw2DImage(images, new Vector2Di(50, 50),
						new Recti(0, 0, 342, 224), null,
						new Coloru(255, 255, 255), true);

					// draw flying imp
					driver.Draw2DImage(images, new Vector2Di(164, 125),
						(time / 500 % 2) == 1 ? imp1 : imp2, null,
						new Coloru(255, 255, 255), true);

					// draw second flying imp with colorcylce
					driver.Draw2DImage(images, new Vector2Di(270, 105),
						(time / 500 % 2) == 1 ? imp1 : imp2, null,
						new Coloru(time % 255, 255, 255), true);

					// draw some text
					if (font != null)
						font.Draw("This demo shows that Irrlicht is also capable of drawing 2D graphics.",
							new Recti(130, 10, 300, 50), new Coloru(255, 255, 255));

					// draw some other text
					if (font2 != null)
						font2.Draw("Also mixing with 3d graphics is possible.",
							new Recti(130, 20, 300, 60), new Coloru(time % 255, time % 255, 255));

					driver.EnableMaterial2D();
					driver.Draw2DImage(images, new Recti(10, 10, 108, 48), new Recti(354, 87, 442, 118));
					driver.EnableMaterial2D(false);

					Vector2Di m = device.CursorControl.Position;
					driver.Draw2DRectangle(new Recti(m.X - 20, m.Y - 20, m.X + 20, m.Y + 20), new Coloru(255, 255, 255, 100));

					driver.EndScene();
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
