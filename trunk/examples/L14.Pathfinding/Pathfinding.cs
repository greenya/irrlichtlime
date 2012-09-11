using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime.Video;
using IrrlichtLime.Core;
using System.Diagnostics;

namespace L14.Pathfinding
{
	class Pathfinding
	{
		public enum CellType
		{
			Passable,
			Impassable,
			Start,
			Finish,
			Path
		}

		int[,] cells = null;
		List<Vector2Di> batchDestPos = null;
		List<Recti> batchSrcRect = null;
		Stopwatch stopwatch = new Stopwatch();

		public int Width { get { return cells.GetLength(0); } }
		public int Height { get { return cells.GetLength(1); } }
		public int CellSize { get; private set; }
		public int StartX { get; private set; }
		public int StartY { get; private set; }
		public int FinishX { get; private set; }
		public int FinishY { get; private set; }
		public int PathLength { get; private set; }
		public long PathCalcTimeMs { get { return stopwatch.ElapsedMilliseconds; } }

		public Pathfinding(int width, int height, int cellSize, int offsetX, int offsetY)
		{
			cells = new int[width, height];

			CellSize = cellSize;
			batchDestPos = new List<Vector2Di>();
			batchSrcRect = new List<Recti>();
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					cells[i, j] = -1;
					batchDestPos.Add(new Vector2Di(i * cellSize + offsetX, j * cellSize + offsetY));
					batchSrcRect.Add(new Recti(0, 0, cellSize, cellSize));
				}
			}
		}

		public void Draw(VideoDriver driver, Texture cellTexture)
		{
			int th = cellTexture.Size.Height;

			Recti[] srcRect = new Recti[5] {
				new Recti(th * 0, 0, th * 1, th), // [0] passable == -1
				new Recti(th * 1, 0, th * 2, th), // [1] impassable == -2
				new Recti(th * 2, 0, th * 3, th), // [2] start == -3
				new Recti(th * 3, 0, th * 4, th), // [3] finish == -4
				new Recti(th * 4, 0, th * 5, th) // [4] path == -5
			};

			for (int i = 0; i < cells.GetLength(0); i++)
			{
				for (int j = 0; j < cells.GetLength(1); j++)
				{
					int k = -1 - cells[i, j];
					if (k >= 0 && k < srcRect.Length)
						batchSrcRect[i * cells.GetLength(1) + j] = srcRect[k];
				}
			}

			driver.Draw2DImageBatch(cellTexture, batchDestPos, batchSrcRect);
		}

		public void SetCell(int x, int y, CellType c)
		{
			if (x < 0 || x >= cells.GetLength(0) || y < 0 || y >= cells.GetLength(1))
				return;

			switch (c)
			{
				case CellType.Passable:
				case CellType.Impassable:
					if ((StartX == x && StartY == y) || (FinishX == x && FinishY == y))
						return;
					break;

				case CellType.Start:
					if (cells[x, y] == -2 || cells[x, y] == -4) // don't change if its impassable or "finish"
						return;

					cells[StartX, StartY] = -1;
					StartX = x;
					StartY = y;
					break;

				case CellType.Finish:
					if (cells[x, y] == -2 || cells[x, y] == -3) // don't change if its impassable or "start"
						return;

					cells[FinishX, FinishY] = -1;
					FinishX = x;
					FinishY = y;
					break;
			}

			cells[x, y] = -(int)c - 1;
		}

		public void FindPath()
		{
			stopwatch.Reset();
			stopwatch.Start();

			int w = cells.GetLength(0);
			int h = cells.GetLength(1);

			// clean up prev path

			for (int i = 0; i < w; i++)
			{
				for (int j = 0; j < h; j++)
				{
					if (cells[i, j] == -5)
						cells[i, j] = -1;
				}
			}

			// build path data

			int[,] c = cells.Clone() as int[,];
			c[FinishX, FinishY] = 0;

			int v;
			bool b;
			bool f = false;
			do
			{
				b = false;

				for (int i = 0; i < w; i++)
				{
					for (int j = 0; j < h; j++)
					{
						if (c[i, j] < 0)
							continue;

						if (i > 0) // left
						{
							v = c[i - 1, j];

							if (v == -1 || v == -3)
							{
								c[i - 1, j] = c[i, j] + 1;
								b = true;

								if (v == -3)
									f = true;
							}
						}

						if (i < w - 1) // right
						{
							v = c[i + 1, j];

							if (v == -1 || v == -3)
							{
								c[i + 1, j] = c[i, j] + 1;
								b = true;

								if (v == -3)
									f = true;
							}
						}

						if (j > 0) // up
						{
							v = c[i, j - 1];

							if (v == -1 || v == -3)
							{
								c[i, j - 1] = c[i, j] + 1;
								b = true;

								if (v == -3)
									f = true;
							}
						}

						if (j < h - 1) // down
						{
							v = c[i, j + 1];

							if (v == -1 || v == -3)
							{
								c[i, j + 1] = c[i, j] + 1;
								b = true;

								if (v == -3)
									f = true;
							}
						}
					}
				}
			} while (b && !f);

			if (c[StartX, StartY] == -3)
			{
				// path not found
				PathLength = -1;
				stopwatch.Stop();
				return;
			}

			PathLength = c[StartX, StartY];

			// find the path

			int x = StartX;
			int y = StartY;
			bool t;
			for (; ; )
			{
				v = c[x, y];

				// the idea of next loop is to execute "left+right" and "up+down" code alternatively;
				// this gives more natural diagonal path

				t = false;
				for (int j = 0; j < 2; j++)
				{
					if (((x + y + j) & 1) == 1)
					{
						if (x > 0 && c[x - 1, y] == v - 1) // left
						{
							x--;
							t = true;
							break;
						}

						if (x < w - 1 && c[x + 1, y] == v - 1) // right
						{
							x++;
							t = true;
							break;
						}
					}
					else
					{
						if (y > 0 && c[x, y - 1] == v - 1) // up
						{
							y--;
							t = true;
							break;
						}

						if (y < h - 1 && c[x, y + 1] == v - 1) // down
						{
							y++;
							t = true;
							break;
						}
					}
				}

				if (t)
					cells[x, y] = -5;
				else
					break;
			}

			cells[FinishX, FinishY] = -4; // restore "finish", since it got overwritten with "path"

			stopwatch.Stop();
		}
	}
}
