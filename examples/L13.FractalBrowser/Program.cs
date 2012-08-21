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
		static bool showHelp = false;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D8, new Dimension2Di(1024, 768));
			if (device == null)
				return;

			device.SetWindowCaption("Fractal Generator - Irrlicht Engine");
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			VideoDriver driver = device.VideoDriver;
			GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");
			Color fontBackgroundColor = new Color(0x7f000000);
			Color fontNormalColor = Color.OpaqueWhite;
			Color fontActionColor = Color.OpaqueYellow;

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

				// draw stats

				driver.Draw2DRectangle(new Recti(10, 10, 160, 56 + (w < 1 ? 16 : 0)), fontBackgroundColor);

				Vector2Di v = new Vector2Di(20, 16);
				font.Draw("Max iterations: " + fGen.GetMaxIterations(), v, fontNormalColor);
				v.Y += 16;
				font.Draw("Zoom: " + (long)fGen.GetZoomFactor().X + "x", v, fontNormalColor);
				if (w < 1)
				{
					v.Y += 16;
					font.Draw("Computing: " + (int)(w * 100) + "%...", v, fontActionColor);
				}

				// draw help

				int h = driver.ScreenSize.Height;
				driver.Draw2DRectangle(new Recti(10, showHelp ? h - 130 : h - 40, showHelp ? 220 : 160, h - 10), fontBackgroundColor);

				v.Y = h - 34;
				font.Draw("[F1] " + (showHelp ? "Hide" : "Show") + " help", v, fontNormalColor);

				if (showHelp)
				{
					v.Y = h - 124;
					font.Draw("[Mouse Left Button] Navigate", v, fontNormalColor);
					v.Y += 16;
					font.Draw("[Mouse Wheel] Zoom in/out", v, fontNormalColor);
					v.Y += 16;
					font.Draw("[+][-][*][/] Max iterations", v, fontNormalColor);
					v.Y += 16;
					font.Draw("[PrintScreen] Save screenshot", v, fontNormalColor);
					v.Y += 16;
					font.Draw("[Esc] Exit application", v, fontNormalColor);
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
				if (evnt.Key.PressedDown)
				{
					if (evnt.Key.Key == KeyCode.Esc)
					{
						device.Close();
						return true;
					}

					if (evnt.Key.Key == KeyCode.F1)
					{
						showHelp = !showHelp;
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

				if (evnt.Key.Key == KeyCode.PrintScreen) // PrintScreen never comes with "evnt.Key.PressedDown == true" so we process it without checking that
				{
					string n = "Screenshot-" + DateTime.Now.Ticks + ".png";
					Image i = device.VideoDriver.CreateScreenShot();
					device.VideoDriver.WriteImage(i, n);
					i.Drop();

					device.Logger.Log("Screenshot saved as " + n);
					return true;
				}
			}

			return false;
		}
	}
}
