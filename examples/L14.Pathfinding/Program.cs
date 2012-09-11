using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Video;
using IrrlichtLime.Core;
using IrrlichtLime.GUI;

namespace L14.Pathfinding
{
	class Program
	{
		static IrrlichtDevice device;
		static Pathfinding pathfinding;
		static bool workMode = true;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1280, 768));
			if (device == null)
				return;

			device.SetWindowCaption("Pathfinding - Irrlicht Engine");
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			VideoDriver driver = device.VideoDriver;
			GUIFont font = device.GUIEnvironment.GetFont("../../media/fontlucida.png");
			Color fontNormalColor = Color.OpaqueWhite;
			Color fontActionColor = Color.OpaqueYellow;

			Texture pathfindingTexture = driver.GetTexture("../../media/pathfinding.png");
			int cellSize = pathfindingTexture.Size.Height;
			pathfinding = new Pathfinding(64, 48, cellSize, 0, 0);
			pathfinding.SetCell(4, 4, Pathfinding.CellType.Start);
			pathfinding.SetCell(pathfinding.Width - 5, pathfinding.Height - 5, Pathfinding.CellType.Finish);

			while (device.Run())
			{
				driver.BeginScene(true, false);

				pathfinding.FindPath();
				pathfinding.Draw(driver, pathfindingTexture);

				// draw info panel

				Vector2Di v = new Vector2Di(pathfinding.Width * pathfinding.CellSize + 20, 20);
				font.Draw("FPS: " + driver.FPS, v, fontNormalColor);

				v.Y += 32;
				font.Draw("Map size: " + pathfinding.Width + " x " + pathfinding.Height, v, fontNormalColor);
				v.Y += 16;
				font.Draw("Shortest path: " + (pathfinding.PathLength == -1 ? "N/A" : pathfinding.PathLength.ToString()), v, fontNormalColor);
				v.Y += 16;
				font.Draw("Calculation time: " + pathfinding.PathCalcTimeMs + " ms", v, fontNormalColor);

				v.Y += 32;
				font.Draw(workMode ? "[LMB] Set cell impassable" : "[LMB] Set Start cell", v, fontActionColor);
				v.Y += 16;
				font.Draw(workMode ? "[RMB] Set cell passable" : "[RMB] Set Finish cell", v, fontActionColor);
				v.Y += 16;
				font.Draw("[Space] Change mode", v, fontActionColor);

				v.Y += 32;
				font.Draw("[F1] Clean up the map", v, fontActionColor);
				v.Y += 16;
				font.Draw("[F2] Add random blocks", v, fontActionColor);

				driver.EndScene();
			}

			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Mouse)
			{
				if (evnt.Mouse.IsLeftPressed())
				{
					pathfinding.SetCell(
						evnt.Mouse.X / pathfinding.CellSize,
						evnt.Mouse.Y / pathfinding.CellSize,
						workMode ? Pathfinding.CellType.Impassable : Pathfinding.CellType.Start);

					return true;
				}

				if (evnt.Mouse.IsRightPressed())
				{
					pathfinding.SetCell(
						evnt.Mouse.X / pathfinding.CellSize,
						evnt.Mouse.Y / pathfinding.CellSize,
						workMode ? Pathfinding.CellType.Passable : Pathfinding.CellType.Finish);

					return true;
				}
			}

			if (evnt.Type == EventType.Key && evnt.Key.PressedDown)
			{
				if (evnt.Key.Key == KeyCode.Space)
				{
					workMode = !workMode;
					return true;
				}

				if (evnt.Key.Key == KeyCode.F1)
				{
					for (int i = 0; i < pathfinding.Width; i++)
						for (int j = 0; j < pathfinding.Height; j++)
							pathfinding.SetCell(i, j, Pathfinding.CellType.Passable);

					return true;
				}

				if (evnt.Key.Key == KeyCode.F2)
				{
					Random r = new Random();
					for (int n = 0; n < 30; n++) // generate random blocks
					{
						int w = r.Next(8) + 2;
						int h = r.Next(8) + 2;
						int x = r.Next(pathfinding.Width - w);
						int y = r.Next(pathfinding.Height - h);
						Pathfinding.CellType c = n < 10 ? Pathfinding.CellType.Impassable : Pathfinding.CellType.Passable;

						for (int i = 0; i <= w; i++)
							for (int j = 0; j <= h; j++)
								pathfinding.SetCell(x + i, y + j, c);
					}

					return true;
				}
			}

			return false;
		}
	}
}
