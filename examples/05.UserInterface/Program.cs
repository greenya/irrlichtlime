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

		enum guiID
		{
			ButtonQuit = 101,
			ButtonWindowNew,
			ButtonFileOpen,
			ScrollbarTransparency
		}

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

			//IGUISkin* skin = env->getSkin();
			//IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
			//if (font)
			//    skin->setFont(font);

			//skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

			//env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
			//    L"Quit", L"Exits Program");
			//env->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
			//    L"New Window", L"Launches a new Window");
			//env->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
			//    L"File Open", L"Opens a file");

			env.AddStaticText("Transparent Control:", new Recti(150, 20, 350, 40), true);
			//IGUIScrollBar* scrollbar = env->addScrollBar(true,
			//            rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
			//scrollbar->setMax(255);

			//scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

			env.AddStaticText("Logging ListBox:", new Recti(50,110,250,130), true);
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
			return false;
		}

		static bool AskUserForDriver(out DriverType driverType)
		{
			driverType = DriverType.Null;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n" +
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
