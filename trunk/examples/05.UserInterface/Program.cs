using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.GUI;

namespace _05.UserInterface
{
	class Program
	{
		static IrrlichtDevice device;

		const int GUI_ID_ButtonQuit = 101;
		const int GUI_ID_ButtonWindowNew = 102;
		const int GUI_ID_ButtonFileOpen = 103;
		const int GUI_ID_ScrollbarTransparency = 104;

		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(640, 480));
			if (device == null)
				return;

			device.WindowCaption = "Irrlicht Engine - User Interface Demo";
			device.WindowResizable = true;

			VideoDriver driver = device.VideoDriver;
			GUIEnvironment env = device.GUIEnvironment;

			GUISkin skin = env.Skin;
			GUIFont font = env.GetFont("../media/fonthaettenschweiler.bmp");
			if (font != null)
				skin.SetFont(GUIDefaultFont.Default, font);

			skin.SetFont(GUIDefaultFont.Tooltip, env.BuiltInFont);

			env.AddButton(new Recti(10, 240, 110, 240 + 32), null, GUI_ID_ButtonQuit, "Quit", "Exits Program");
			env.AddButton(new Recti(10, 280, 110, 280 + 32), null, GUI_ID_ButtonWindowNew, "New Window", "Launches a new Window");
			env.AddButton(new Recti(10, 320, 110, 320 + 32), null, GUI_ID_ButtonFileOpen, "File Open", "Opens a file");

			env.AddStaticText("Transparent Control:", new Recti(150, 20, 350, 40), true);
			GUIScrollBar scrollbar = env.AddScrollBar(true, new Recti(150, 45, 350, 60), null, GUI_ID_ScrollbarTransparency);
			scrollbar.MaxValue = 255;
			scrollbar.Position = (int)env.Skin.GetColor(GUIDefaultColor.WindowBackground).Alpha;

			GUIStaticText trq = env.AddStaticText("Logging ListBox:", new Recti(50,110,250,130), true);
			//IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
			//env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			env.AddImage(driver.GetTexture("../media/irrlichtlogoalpha2.tga"), new Vector2Di(10, 10));

			while (device.Run())
			if (device.WindowActive)
			{
				driver.BeginScene(true, true, new Coloru(0, 200, 200, 200));
				env.DrawAll();
				driver.EndScene();
			}

			device.Drop();
		}

		static bool device_OnEvent(Event e)
		{
			if (e.Type == EventType.GUI)
			{
				int id = e.GUI.Caller.ID;
				GUIEnvironment env = device.GUIEnvironment;

				switch (e.GUI.Type)
				{
					case GUIEventType.ScrollBarChanged:
						if (id == GUI_ID_ScrollbarTransparency)
						{
							int pos = ((GUIScrollBar)e.GUI.Caller).Position;
							foreach (GUIDefaultColor which in Enum.GetValues(typeof(GUIDefaultColor)))
							{
								Coloru color = env.Skin.GetColor(which);
								color.Alpha = (uint)pos;
								env.Skin.SetColor(which, color);
							}
						}
						break;

					case GUIEventType.ButtonClicked:
						switch (id)
						{
							case GUI_ID_ButtonQuit:
								device.Close();
								return true;

							case GUI_ID_ButtonWindowNew:
								//Context.listbox->addItem(L"Window created");
								//Context.counter += 30;
								//if (Context.counter > 200)
								//    Context.counter = 0;

								//IGUIWindow* window = env->addWindow(
								//    rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
								//    false, // modal?
								//    L"Test window");

								//env->addStaticText(L"Please close me",
								//    rect<s32>(35,35,140,50),
								//    true, // border?
								//    false, // wordwrap?
								//    window);
								return true;

							case GUI_ID_ButtonFileOpen:
								//Context.listbox->addItem(L"File open");
								//env->addFileOpenDialog(L"Please choose a file.");
								return true;

							default:
								return false;
						}
				}
			}

			return false;
		}

		static bool AskUserForDriver(out DriverType driverType)
		{
			driverType = DriverType.Null;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n" +
						" (d) Burning's Software Renderer\n (e) Software Renderer\n" +
						" (f) NullDevice\n (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: driverType = DriverType.OpenGL; break;
				case ConsoleKey.B: driverType = DriverType.Direct3D9; break;
				case ConsoleKey.C: driverType = DriverType.Direct3D8; break;
				case ConsoleKey.D: driverType = DriverType.BurningsVideo; break;
				case ConsoleKey.E: driverType = DriverType.Software; break;
				case ConsoleKey.F: driverType = DriverType.Null; break;
				default:
					return false;
			}

			return true;
		}
	}
}
