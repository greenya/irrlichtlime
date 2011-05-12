using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L08.WPFWindow
{
	public partial class WinFormsUserControl : UserControl
	{
		/// <summary>
		/// Some simple class to store command data.
		/// We will use it to send commands to rendering thread (like command to call VideoDriver.ResizeNotify())
		/// </summary>
		class Command
		{
			public enum Kind
			{
				None,
				Resized
			}

			public Kind Type = Kind.None;
			public object Value = null;

			public void SetCommand(Kind type, object value) { Type = type; Value = value; }
			public void Clear() { Type = Kind.None; Value = null; }
		}

		Command backgroundCommand;
		BackgroundWorker backgroundWorker;

		public WinFormsUserControl()
		{
			InitializeComponent();

			backgroundCommand = new Command();

			backgroundWorker = new BackgroundWorker();
			backgroundWorker.WorkerSupportsCancellation = true;
			backgroundWorker.DoWork += new DoWorkEventHandler(backgroundWorker_DoWork);
			backgroundWorker.RunWorkerAsync(Handle);
			components.Add(backgroundWorker);

			IsNotifyResizes = true;
		}

		/// <summary>
		/// Indicates that rendering thread is working.
		/// </summary>
		public bool IsRendering { get { return backgroundWorker.IsBusy; } }

		/// <summary>
		/// Indicates that Irrlicht will be notifyed (or not) about resize of client area of this control.
		/// </summary>
		public bool IsNotifyResizes { get; set; }

		/// <summary>
		/// Shuts down rendering thread.
		/// This method must be called before this controls is going to be released.
		/// </summary>
		public void Shutdown()
		{
			if (backgroundWorker.IsBusy)
			{
				backgroundWorker.CancelAsync();

				while (backgroundWorker.IsBusy)
					Application.DoEvents();
			}
		}

		protected override void OnResize(EventArgs e)
		{
			base.OnResize(e);

			if (!IsNotifyResizes)
				return;

			lock (backgroundCommand)
			{
				Dimension2Di newSize = new Dimension2Di(this.Width, this.Height);
				if (newSize.Area > 0)
					backgroundCommand.SetCommand(Command.Kind.Resized, newSize);
			}
		}

		void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
		{
			BackgroundWorker worker = sender as BackgroundWorker;
			IrrlichtCreationParameters p = new IrrlichtCreationParameters();
			p.DriverType = DriverType.Direct3D9;
			p.WindowID = (IntPtr)e.Argument;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(p);
			if (device == null)
				// if device cannot be created by any reason - we just leave this thread,
				// after all IsRedering will report false, so it is all OK.
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;
			GUIEnvironment gui = device.GUIEnvironment;

			// setup a simple 3d scene

			CameraSceneNode cam = smgr.AddCameraSceneNode();
			cam.Target = new Vector3Df(0);

			SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 15, 0), 30.0f);
			cam.AddAnimator(anim);
			anim.Drop();

			SceneNode cube = smgr.AddCubeSceneNode(20);
			cube.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
			cube.SetMaterialTexture(1, driver.GetTexture("../../media/water.jpg"));
			cube.SetMaterialFlag(MaterialFlag.Lighting, false);
			cube.SetMaterialType(MaterialType.Reflection2Layer);

			smgr.AddSkyBoxSceneNode(
				"../../media/irrlicht2_up.jpg",
				"../../media/irrlicht2_dn.jpg",
				"../../media/irrlicht2_lf.jpg",
				"../../media/irrlicht2_rt.jpg",
				"../../media/irrlicht2_ft.jpg",
				"../../media/irrlicht2_bk.jpg");

			gui.AddImage(
				driver.GetTexture("../../media/lime_logo_alpha.png"),
				new Vector2Di(30, 0));

			// draw all

			while (device.Run())
			{
				driver.BeginScene(false);
				
				smgr.DrawAll();
				gui.DrawAll();

				// draw stats

				int x = 20;
				int y = driver.ScreenSize.Height - 50;

				driver.Draw2DRectangle(
					new Recti(x, y, x + driver.ScreenSize.Width - 2 * x, y + 30),
					new IrrlichtLime.Video.Color(0, 0, 0, 128));

				device.GUIEnvironment.BuiltInFont.Draw(
					"Driver: " + driver.Name,
					new Vector2Di(x + 5, y + 5),
					new IrrlichtLime.Video.Color(255, 255, 255));

				device.GUIEnvironment.BuiltInFont.Draw(
					"FPS: " + driver.FPS.ToString(),
					new Vector2Di(x + 5, y + 15),
					new IrrlichtLime.Video.Color(255, 255, 255));

				driver.EndScene();

				// check for cancellation

				if (worker.CancellationPending)
					device.Close();

				// check for new command

				lock (backgroundCommand)
				{
					switch (backgroundCommand.Type)
					{
						case Command.Kind.Resized:
							driver.ResizeNotify(backgroundCommand.Value as Dimension2Di);
							backgroundCommand.Clear();
							break;
					}
				}
			}

			// drop the device

			device.Drop();
		}
	}
}
