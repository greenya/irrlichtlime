using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L13.FractalBrowser
{
	class Program
	{
		static IrrlichtDevice device;
		static FractalGenerator fGen;
		static Vector2Di mouseMoveStart = null;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D8, new Dimension2Di(1024, 768));
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			VideoDriver driver = device.VideoDriver;

			GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");

			fGen = new FractalGenerator(device);
			fGen.Generate(new Rectd(
				-driver.ScreenSize.Width / 250.0,
				-driver.ScreenSize.Height / 250.0,
				driver.ScreenSize.Width / 250.0,
				driver.ScreenSize.Height / 250.0));

			while (device.Run())
			{
				driver.BeginScene(false);

				Vector2Di o = null;
				if (mouseMoveStart != null)
					o = device.CursorControl.Position - mouseMoveStart;

				float w = fGen.DrawAll(o);

				driver.Draw2DRectangle(new Recti(10, 10, 160, 56 + (w < 1 ? 16 : 0)), new Color(0x7f000000));

				Vector2Di v = new Vector2Di(20, 16);
				font.Draw("Max iterations: " + fGen.GetMaxIterations(), v, Color.OpaqueWhite);
				v.Y += 16;
				font.Draw("Zoom: " + (long)fGen.GetZoomFactor().X + "x", v, Color.OpaqueWhite);
				if (w < 1)
				{
					v.Y += 16;
					font.Draw("Computing: " + (int)(w * 100) + "%...", v, Color.OpaqueYellow);
				}

				driver.EndScene();
				device.Yield();
			}

			fGen.Drop();
			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Mouse)
			{
				Dimension2Di s = device.VideoDriver.ScreenSize;

				if (evnt.Mouse.Type == MouseEventType.Wheel)
				{
					Rectd r = new Rectd();

					if (evnt.Mouse.Wheel > 0)
					{
						// zoom in

						int x1 = evnt.Mouse.X - s.Width / 2 + (int)evnt.Mouse.Wheel * s.Width / 10;
						int y1 = evnt.Mouse.Y - s.Height / 2 + (int)evnt.Mouse.Wheel * s.Height / 10;

						r.UpperLeftCorner = fGen.GetWindowCoord(x1, y1);
						r.LowerRightCorner = fGen.GetWindowCoord(2 * evnt.Mouse.X - x1, 2 * evnt.Mouse.Y - y1);

						device.CursorControl.Position = new Vector2Di(s.Width / 2, s.Height / 2);
					}
					else
					{
						// zoom out

						int x1 = s.Width / 10;
						int y1 = s.Height / 10;

						r.UpperLeftCorner = fGen.GetWindowCoord(-x1, -y1);
						r.LowerRightCorner = fGen.GetWindowCoord(s.Width + x1, s.Height + y1);
					}

					fGen.Generate(r);
					return true;
				}

				if (evnt.Mouse.Type == MouseEventType.LeftDown)
				{
					mouseMoveStart = new Vector2Di(evnt.Mouse.X, evnt.Mouse.Y);
					return true;
				}

				if (evnt.Mouse.Type == MouseEventType.LeftUp)
				{
					Vector2Dd p1 = fGen.GetWindowCoord(evnt.Mouse.X, evnt.Mouse.Y);
					Vector2Dd p2 = fGen.GetWindowCoord(mouseMoveStart.X, mouseMoveStart.Y);
					Rectd r = fGen.GetWindow() + p2 - p1;

					fGen.Generate(r);

					mouseMoveStart = null;
					return true;
				}
			}

			if (evnt.Type == EventType.Key)
			{
				if (evnt.Key.Key == KeyCode.PrintScreen)
				{
					string n = "Screenshot-" + DateTime.Now.Ticks + ".png";
					Image i = device.VideoDriver.CreateScreenShot();
					device.VideoDriver.WriteImage(i, n);
					i.Drop();

					device.Logger.Log("Screenshot saved as " + n);
					return true;
				}

				switch (evnt.Key.Char)
				{
					case '+':
						fGen.Generate(fGen.GetMaxIterations() + 1);
						return true;

					case '-':
						fGen.Generate(fGen.GetMaxIterations() - 1);
						return true;

					case '*':
						fGen.Generate(fGen.GetMaxIterations() + 10);
						return true;

					case '/':
						fGen.Generate(fGen.GetMaxIterations() - 10);
						return true;
				}
			}

			return false;
		}
	}
}
