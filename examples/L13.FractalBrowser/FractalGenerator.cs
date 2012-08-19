using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;

namespace L13.FractalBrowser
{
	class FractalGenerator
	{
		const int TileSize = 64;

		IrrlichtDevice device = null;
		VideoDriver driver = null;
		Recti screen = new Recti(0, 0, 640, 480);
		Rectd window = new Rectd(-1, -1, 1, 1);
		List<Tile> tiles = new List<Tile>();
		Thread[] threads = new Thread[1 + 8]; // [0] - tile manager; [1+] - single tile generator
		int maxIterations = 10;

		public FractalGenerator(IrrlichtDevice device)
		{
			this.device = device;
			driver = device.VideoDriver;
			screen = driver.ViewPort;

			regenerateTiles();
		}

		public void Drop()
		{
			abortThreads();
			clearTiles();
		}

		public void Generate(Rectd window, int maxIterations)
		{
			if (window.Width < 0.000004 || window.Width > 20 ||
				window.Height < 0.000004 || window.Height > 20)
				return;

			if (maxIterations < 0)
				maxIterations = 0;

			abortThreads();

			this.window = window;
			this.maxIterations = maxIterations;

			foreach (Tile t in tiles)
			{
				t.MaxIterations = maxIterations;
				t.TextureIsReady = false;
				t.WindowRect = new Rectd(
					GetWindowCoord(t.ScreenPos.X, t.ScreenPos.Y),
					GetWindowCoord(t.ScreenPos.X + TileSize, t.ScreenPos.Y + TileSize));
			}

			threads[0] = new Thread(new ThreadStart(threadTileManager_main));
			threads[0].Start();
		}

		public void Generate(Rectd window)
		{
			Generate(window, maxIterations);
		}

		public void Generate(int maxIterations)
		{
			Generate(window, maxIterations);
		}

		public Vector2Dd GetZoomFactor()
		{
			return new Vector2Dd(
				screen.Width / window.Width,
				screen.Height / window.Height);
		}

		public int GetMaxIterations()
		{
			return maxIterations;
		}

		public Rectd GetWindow()
		{
			return window;
		}

		public Vector2Dd GetWindowCoord(int screenX, int screenY)
		{
			double dx = screen.Width / window.Width;
			double x = window.UpperLeftCorner.X + screenX / dx;

			double dy = screen.Height / window.Height;
			double y = window.UpperLeftCorner.Y + screenY / dy;

			return new Vector2Dd(x, y);
		}

		public float DrawAll(Vector2Di screenOffset = null)
		{
			Vector2Di zero = new Vector2Di(0);
			int n = 0;

			foreach (Tile tile in tiles)
			{
				if (tile.TextureIsReady)
				{
					driver.Draw2DImage(tile.Texture, tile.ScreenPos + (screenOffset ?? zero));
					n++;
				}
			}

			return (float)n / tiles.Count;
		}

		void abortThreads()
		{
			for (int i = 0; i < threads.Length; i++)
			{
				if (threads[i] != null)
				{
					threads[i].Abort();
					threads[i] = null;
				}
			}
		}

		void regenerateTiles()
		{
			clearTiles();

			bool o = driver.GetTextureCreationFlag(TextureCreationFlag.CreateMipMaps);
			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, false);

			int y = 0;
			int x = 0;
			Dimension2Di d = new Dimension2Di(TileSize);

			while (y < screen.Height)
			{
				tiles.Add(new Tile(x, y, d, driver));

				x += TileSize;
				if (x >= screen.Width)
				{
					x = 0;
					y += TileSize;
				}
			}

			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, o);

			// sort tiles: closest to center of the screen goes first

			int swh = screen.Width / 2;
			int shh = screen.Height / 2;
			bool b;

			do
			{
				b = false;
				for (int i = 0; i < tiles.Count - 1; i++)
				{
					int tx1 = tiles[i].ScreenPos.X + TileSize / 2;
					int ty1 = tiles[i].ScreenPos.Y + TileSize / 2;
					int td1 = Math.Abs(swh - tx1) + Math.Abs(shh - ty1);

					int tx2 = tiles[i + 1].ScreenPos.X + TileSize / 2;
					int ty2 = tiles[i + 1].ScreenPos.Y + TileSize / 2;
					int td2 = Math.Abs(swh - tx2) + Math.Abs(shh - ty2);

					if (td1 > td2)
					{
						Tile t = tiles[i];
						tiles[i] = tiles[i + 1];
						tiles[i + 1] = t;
						b = true;
					}
				}
			} while (b);
		}

		void clearTiles()
		{
			foreach (Tile t in tiles)
				driver.RemoveTexture(t.Texture);

			tiles.Clear();
		}

		void threadTileManager_main()
		{
			int j;

			foreach (Tile tile in tiles)
			{
				while (true)
				{
					j = -1;
					for (int i = 1; i < threads.Length; i++)
					{
						if (threads[i] == null ||
							threads[i].ThreadState == ThreadState.Stopped)
						{
							j = i;
							break;
						}
					}

					if (j != -1)
						break;

					Thread.Sleep(1);
				}

				threads[j] = new Thread(new ParameterizedThreadStart(threadTileGenerator_main));
				threads[j].Start(tile);
			}
		}

		void threadTileGenerator_main(object tileObject)
		{
			Tile tile = tileObject as Tile;

			if (!tile.TexturePainter.Lock(TextureLockMode.WriteOnly))
				return;

			try
			{
				// generate Mandelbrot set

				int w = tile.TexturePainter.MipMapLevelWidth;
				double rx = tile.WindowRect.UpperLeftCorner.X;
				double rxu = tile.WindowRect.Width / w;

				int h = tile.TexturePainter.MipMapLevelHeight;
				double ry = tile.WindowRect.UpperLeftCorner.Y;
				double ryu = tile.WindowRect.Height / h;

				Color c = new Color();
				int i;

				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						double ax0 = rx + x * rxu;
						double ay0 = ry + y * ryu;
						double ax1 = ax0;
						double ay1 = ay0;
						double ac = ax0 * ax0 + ay0 * ay0;

						for (i = 0; i < tile.MaxIterations && ac < 16; i++)
						{
							double ax2 = ax1 * ax1 - ay1 * ay1 + ax0;
							ay1 = 2 * ax1 * ay1 + ay0;
							ax1 = ax2;
							ac = ax1 * ax1 + ay1 * ay1;
						}

						if (i < tile.MaxIterations)
							c.Set((uint)(i * 0x0102f4));
						else
							c.Set(0);

						tile.TexturePainter.SetPixel(x, y, c);
					}
				}
			}
			finally
			{
				tile.TexturePainter.Unlock();
				tile.TextureIsReady = true;
			}
		}

		class Tile
		{
			public Vector2Di ScreenPos;
			public Rectd WindowRect;
			public Texture Texture;
			public TexturePainter TexturePainter;
			public bool TextureIsReady;
			public int MaxIterations;

			public Tile(int screenX, int screenY, Dimension2Di screenDimension, VideoDriver driver)
			{
				ScreenPos = new Vector2Di(screenX, screenY);
				Texture = driver.AddTexture(screenDimension, string.Format("TileTexture({0},{1})", screenX, screenY));
				TexturePainter = Texture.GetTexturePainter();
			}
		}
	}
}