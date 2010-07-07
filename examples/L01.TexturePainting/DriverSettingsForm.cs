using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.GUI;

namespace L01.TexturePainting
{
	class DriverSettingsForm
	{
		public DriverType DriverType { get { return driverType; } }
		public VideoMode VideoMode { get { return videoMode; } }
		public bool Fullscreen { get { return fullscreen; } }

		public DriverSettingsForm(string windowCaption, string aboutText)
		{
			this.windowCaption = windowCaption;
			this.aboutText = aboutText;
		}

		public bool ShowDialog()
		{
			device = IrrlichtDevice.CreateDevice(DriverType.BurningsVideo, new Dimension2Di(320, 320));
			device.FileSystem.AddFileArchive("../media/");
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.SetWindowCaption(windowCaption);

			initGUI();

			while (device.Run())
			{
				device.VideoDriver.BeginScene(true, true, new Color(40, 180, 80));
				device.GUIEnvironment.DrawAll();
				device.VideoDriver.EndScene();
			}

			device.Drop();

			return run;
		}

		private void initGUI()
		{
			GUIEnvironment gui = device.GUIEnvironment;
			gui.Skin.SetFont(gui.GetFont("fontlucida.png"));
			foreach (GUIDefaultColor c in Enum.GetValues(typeof(GUIDefaultColor)))
			{
				Color l = gui.Skin.GetColor(c);
				l.Alpha = 255;
				gui.Skin.SetColor(l, c);
			}

			GUITabControl tc = gui.AddTabControl(new Recti(20, 20, 300, 250));

			GUITab t1 = tc.AddTab("Setup");

			gui.AddStaticText("Driver", new Recti(20, 20, 260, 40), false, false, t1);
			guiDriverType = gui.AddComboBox(new Recti(20, 40, 260, 60), t1);
			foreach (DriverType t in Enum.GetValues(typeof(DriverType)))
			{
				if (t == DriverType.Null)
					continue;

				int i = guiDriverType.AddItem(t.ToString(), (int)t);

				if (t == driverType)
					guiDriverType.SelectedIndex = i;
			}

			gui.AddStaticText("Resolution", new Recti(20, 70, 260, 90), false, false, t1);
			guiResolution = gui.AddComboBox(new Recti(20, 90, 260, 110), t1);
			foreach (VideoMode m in device.VideoModeList.ModeList)
			{
				int i = guiResolution.AddItem(m.ToString());

				if (m.Resolution == videoMode.Resolution && m.Depth == videoMode.Depth)
					guiResolution.SelectedIndex = i;
			}

			guiFullscreen = gui.AddCheckBox(fullscreen, new Recti(20, 130, 260, 150), "Fullscreen", t1);

			GUITab t2 = tc.AddTab("About");

			gui.AddStaticText(aboutText, new Recti(20, 20, 260, 180), false, true, t2);

			guiButtonRun = gui.AddButton(new Recti(130, 270, 210, 300), null, -1, "Run");
			guiButtonExit = gui.AddButton(new Recti(220, 270, 300, 300), null, -1, "Exit");
		}

		bool device_OnEvent(Event e)
		{
			if (e.Type == EventType.GUI)
			{
				if (e.GUI.Type == GUIEventType.ButtonClicked)
				{
					if (e.GUI.Caller == guiButtonRun)
					{
						driverType = (DriverType)guiDriverType.GetItemData(guiDriverType.SelectedIndex);
						videoMode = device.VideoModeList.ModeList[guiResolution.SelectedIndex];
						fullscreen = guiFullscreen.Checked;

						run = true;
						device.Close();
						return true;
					}

					if (e.GUI.Caller == guiButtonExit)
					{
						run = false;
						device.Close();
						return true;
					}
				}
			}

			return false;
		}

		// default settings <
		DriverType driverType = DriverType.Direct3D8;
		VideoMode videoMode = new VideoMode(800, 600, 32);
		bool fullscreen = false;
		// >

		bool run = false;
		string windowCaption;
		string aboutText;

		IrrlichtDevice device;
		GUIComboBox guiDriverType;
		GUIComboBox guiResolution;
		GUICheckBox guiFullscreen;
		GUIElement guiButtonRun;
		GUIElement guiButtonExit;
	}
}
