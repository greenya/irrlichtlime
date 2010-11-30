using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms; // for SystemInformation only
using System.IO;

using IrrlichtLime;
using IrrlichtLime.Video;
using IrrlichtLime.Core;
using IrrlichtLime.IO;
using IrrlichtLime.Scene;

namespace L05.ScreenshotToTexture
{
	class Program
	{
		static void Main(string[] args)
		{
			IrrlichtDevice device = IrrlichtDevice.CreateDevice(DriverType.Direct3D8, new Dimension2Di(512, 512));
			device.SetWindowCaption("Screenshot to texture - Irrlicht Lime");

			// set up very simple scene {{

			CameraSceneNode cam = device.SceneManager.AddCameraSceneNode();
			cam.Target = new Vector3Df(0);

			SceneNodeAnimator anim = device.SceneManager.CreateFlyCircleAnimator(new Vector3Df(0, 16, 0), 30, 0.0004f);
			cam.AddAnimator(anim);
			anim.Drop();

			SceneNode cube = device.SceneManager.AddCubeSceneNode(20);
			cube.SetMaterialFlag(MaterialFlag.Lighting, false);

			// }}

			while (device.Run())
			{
				cube.SetMaterialTexture(0, null);
				device.VideoDriver.RemoveAllTextures();

				Texture t = getDesktopTexture(device);
				cube.SetMaterialTexture(0, t);

				device.VideoDriver.BeginScene(false);

				device.VideoDriver.Draw2DImage(t, device.VideoDriver.ViewPort, new Recti(new Vector2Di(0), t.Size));
				device.VideoDriver.Draw2DRectangle(device.VideoDriver.ViewPort, new IrrlichtLime.Video.Color(0, 0, 0, 160));

				device.SceneManager.DrawAll();

				device.GUIEnvironment.BuiltInFont.Draw(
					device.Timer.ToString() +
					"\nMemory: " + (System.Diagnostics.Process.GetCurrentProcess().WorkingSet64 / (1 << 20)).ToString() + " Mb" +
					"\nFPS: " + device.VideoDriver.FPS.ToString(),
					new Vector2Di(16),
					new IrrlichtLime.Video.Color(255, 255, 255));

				device.VideoDriver.EndScene();
			}

			device.Drop();
		}

		private static Texture getDesktopTexture(IrrlichtDevice device)
		{
			int screenX = 0;
			int screenY = 0;
			int screenWidth = device.VideoDriver.ScreenSize.Width;
			int screenHeight = device.VideoDriver.ScreenSize.Height;

			Point p = new Point();
			GetCursorPos(ref p);
			screenX = p.X - screenWidth / 2;
			screenY = p.Y - screenHeight / 2;

			// validate grabbing rect (note: works fine without validation too) {{

			if (screenX < 0)
				screenX = 0;

			if (screenX + screenWidth > SystemInformation.VirtualScreen.Width)
				screenX = SystemInformation.VirtualScreen.Width - screenWidth;

			if (screenY < 0)
				screenY = 0;

			if (screenY + screenHeight > SystemInformation.VirtualScreen.Height)
				screenY = SystemInformation.VirtualScreen.Height - screenHeight;

			// }}

			Bitmap b = new Bitmap(
					screenWidth,
					screenHeight,
					PixelFormat.Format32bppArgb);

			Graphics g = Graphics.FromImage(b);

			g.CopyFromScreen(
				screenX,
				screenY,
				0, 0,
				new Size(screenWidth, screenHeight),
				CopyPixelOperation.SourceCopy);

			MemoryStream s = new MemoryStream();
			b.Save(s, ImageFormat.Bmp);

			byte[] c = s.ToArray();
			s.Close();

			LogLevel o = device.Logger.LogLevel;
			device.Logger.LogLevel = LogLevel.Error; // we hide all those "Loaded texture" messages in console {{

			ReadFile f = device.FileSystem.CreateMemoryReadFile("screenTexture", c);
			Texture t = device.VideoDriver.GetTexture(f);
			f.Drop();

			device.Logger.LogLevel = o; // }}

			return t;
		}

		[System.Runtime.InteropServices.DllImport("user32.dll")]
		static extern bool GetCursorPos(ref Point lpPoint);
	}
}
