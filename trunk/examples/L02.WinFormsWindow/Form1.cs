using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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
		class DeviceSettings
		{
			public IntPtr HostHandle;
			public DriverType DriverType;

			public DeviceSettings(IntPtr hh, DriverType dt)
			{
				HostHandle = hh;
				DriverType = dt;
			}
		}

		private bool userWantExit = false;

		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			// fill combobox with all available video drivers, except Null
			foreach (DriverType v in Enum.GetValues(typeof(DriverType)))
				if (v != DriverType.Null)
					comboBox1.Items.Add(v);
		}

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			// if rending in progress, we sneding cancel request and waiting for its finish
			if (backgroundWorker1.IsBusy)
			{
				backgroundWorker1.CancelAsync();
				while (backgroundWorker1.IsBusy)
					Application.DoEvents();
			}

			backgroundWorker1.RunWorkerAsync(
				new DeviceSettings(
					panel1.Handle, (DriverType)comboBox1.SelectedItem));
		}

		private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
		{
			BackgroundWorker worker = sender as BackgroundWorker;
			DeviceSettings settings = e.Argument as DeviceSettings;

			// create irrlicht device in the button window

			IrrlichtCreationParameters p = new IrrlichtCreationParameters();
			p.DriverType = settings.DriverType;
			p.WindowID = settings.HostHandle;
			IrrlichtDevice dev = IrrlichtDevice.CreateDevice(p);

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

			smgr.AddSkyBoxSceneNode(
				"../media/irrlicht2_up.jpg",
				"../media/irrlicht2_dn.jpg",
				"../media/irrlicht2_lf.jpg",
				"../media/irrlicht2_rt.jpg",
				"../media/irrlicht2_ft.jpg",
				"../media/irrlicht2_bk.jpg");

			// draw all

			int lastFPS = -1;
			while (dev.Run())
			{
				drv.BeginScene();
				smgr.DrawAll();
				drv.EndScene();

				int fps = drv.FPS;
				if (lastFPS != fps)
				{
					// we reporting progress using BackgroundWorker' ReportProgress method
					// note: we cannot do just label1.Text = "...", because its another thread
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
			// if background worker still running, we sending request to finish rendering
			// and cancel closing request of the main form
			if (backgroundWorker1.IsBusy)
			{
				backgroundWorker1.CancelAsync();
				e.Cancel = true;
				userWantExit = true;
			}
		}

		private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			int f = e.ProgressPercentage;
			string d = e.UserState as string;

			label1.Text = string.Format(
				"Using {0} driver and rendering {1} fps",
				d, f);
		}

		private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{
			if (e.Error != null)
				MessageBox.Show(e.Error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

			// as background worker finished, and user want exit - we close main form
			// (it is the only way to close form correctly -- only when device dropped,
			// so background worker not running)
			if (userWantExit)
				Close();
		}
	}
}
