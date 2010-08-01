using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L02.WinFormsWindow
{
	public partial class Form1 : Form
	{
		// this class will hold all settings that we need to pass to background worker,
		// which will create Irrlicht device, do all rendering and drop it when needed;
		// we are extending IrrlichtCreationParameters with our custom settings
		class DeviceSettings : IrrlichtCreationParameters
		{
			public Color BackColor; // "null" for skybox
			
			public DeviceSettings(IntPtr hh, DriverType dt, byte aa, Color bc, bool vs)
			{
				WindowID = hh;
				DriverType = dt;
				AntiAliasing = aa;
				BackColor = bc;
				VSync = vs;
			}
		}

		private bool userWantExit = false; // if "true", we shut down rendering thread and then exit app

		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			// select "No AntiAliasing"
			comboBoxAntiAliasing.SelectedIndex = 0;

			// select "Skybox"
			comboBoxBackground.SelectedIndex = 0;

			// fill combobox with all available video drivers, except Null
			foreach (DriverType v in Enum.GetValues(typeof(DriverType)))
				if (v != DriverType.Null)
					comboBoxVideoDriver.Items.Add(v);
		}

		private void initializeIrrlichtDevice(object sender, EventArgs e)
		{
			if (comboBoxVideoDriver.SelectedItem == null)
				return;

			// if rendering in progress, we are sending cancel request and waiting for its finishing
			if (backgroundRendering.IsBusy)
			{
				backgroundRendering.CancelAsync();
				while (backgroundRendering.IsBusy)
					Application.DoEvents(); // this is not very correct way, but its very short, so we use it

				// redraw the panel, otherwise last rendered frame will stay as garbage
				panelRenderingWindow.Invalidate();
			}

			// collect settings and start background worker with these settings

			DeviceSettings s = new DeviceSettings(
				checkBoxUseSeparateWindow.Checked ? IntPtr.Zero : panelRenderingWindow.Handle,
				(DriverType)comboBoxVideoDriver.SelectedItem,
				(byte)(comboBoxAntiAliasing.SelectedIndex == 0 ? 0 : Math.Pow(2, comboBoxAntiAliasing.SelectedIndex)),
				comboBoxBackground.SelectedIndex == 0 ? null : new Color(comboBoxBackground.SelectedIndex == 1 ? 0xFF000000 : 0xFFFFFFFF),
				checkBoxUseVSync.Checked
			);

			backgroundRendering.RunWorkerAsync(s);

			labelRenderingStatus.Text = "Starting rendering...";
		}

		private void backgroundRendering_DoWork(object sender, DoWorkEventArgs e)
		{
			BackgroundWorker worker = sender as BackgroundWorker;
			DeviceSettings settings = e.Argument as DeviceSettings;

			// create irrlicht device using provided settings

			IrrlichtDevice dev = IrrlichtDevice.CreateDevice(settings);

			if (dev == null)
				throw new Exception("Failed to create Irrlicht device.");

			VideoDriver drv = dev.VideoDriver;
			SceneManager smgr = dev.SceneManager;

			// setup a simple 3d scene

			CameraSceneNode cam = smgr.AddCameraSceneNode();
			cam.Target = new Vector3Df(0);

			SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 15, 0), 30.0f);
			cam.AddAnimator(anim);
			anim.Drop();

			SceneNode cube = smgr.AddCubeSceneNode(20);
			cube.SetMaterialTexture(0, drv.GetTexture("../media/wall.bmp"));
			cube.SetMaterialTexture(1, drv.GetTexture("../media/water.jpg"));
			cube.SetMaterialFlag(MaterialFlag.Lighting, false);
			cube.SetMaterialType(MaterialType.Reflection2Layer);

			if (settings.BackColor == null)
			{
				smgr.AddSkyBoxSceneNode(
					"../media/irrlicht2_up.jpg",
					"../media/irrlicht2_dn.jpg",
					"../media/irrlicht2_lf.jpg",
					"../media/irrlicht2_rt.jpg",
					"../media/irrlicht2_ft.jpg",
					"../media/irrlicht2_bk.jpg");
			}

			dev.GUIEnvironment.AddImage(
				drv.GetTexture("../media/lime_logo_alpha.png"),
				new Vector2Di(30, 0));

			// draw all

			int lastFPS = -1;
			while (dev.Run())
			{
				if (settings.BackColor == null)
					// indeed, we do not need to spend time on cleaning color buffer if we use skybox
					drv.BeginScene(false);
				else
					drv.BeginScene(true, true, settings.BackColor);

				smgr.DrawAll();
				dev.GUIEnvironment.DrawAll();
				drv.EndScene();

				int fps = drv.FPS;
				if (lastFPS != fps)
				{
					// report progress using common BackgroundWorker' method
					// note: we cannot do just labelRenderingStatus.Text = "...",
					// because we are running another thread
					worker.ReportProgress(fps, drv.Name);
					lastFPS = fps;
				}

				// if we requested to stop, we close the device
				if (worker.CancellationPending)
					dev.Close();
			}

			// drop device
			dev.Drop();
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
			// if background worker still running, we send request to stop
			if (backgroundRendering.IsBusy)
			{
				backgroundRendering.CancelAsync();
				e.Cancel = true;
				userWantExit = true;
			}
		}

		private void backgroundRendering_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			// process reported progress

			int f = e.ProgressPercentage;
			string d = e.UserState as string;

			labelRenderingStatus.Text = string.Format(
				"Rendering {1} fps using {0} driver",
				d, f);
		}

		private void backgroundRendering_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{
			// if exception occured in rendering thread -- we display the message
			if (e.Error != null)
				MessageBox.Show(e.Error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

			// if user want exit - we close main form
			// note: it is the only way to close form correctly -- only when device dropped,
			// so background worker not running
			if (userWantExit)
				Close();

			labelRenderingStatus.Text = "No rendering";
		}
	}
}
