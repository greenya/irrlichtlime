using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _09.Meshviewer
{
	class Program
	{
		static IrrlichtDevice device = null;
		static string startUpModelFile;
		static string messageText;
		static string caption;
		static SceneNode model = null;
		static SceneNode skybox = null;
		static bool octree = false;
		static bool useLight = false;

		static CameraSceneNode[] camera = new CameraSceneNode[2];

		// Values used to identify individual GUI elements
		enum guiID
		{
			DialogRootWindow = 0x10000,

			XScale,
			YScale,
			ZScale,

			OpenModel,
			SetModelArchive,
			LoadAsOctree,

			SkyBoxVisible,
			ToggleDebugInfo,

			DebugOff,
			DebugBoundingBox,
			DebugNormals,
			DebugSkeleton,
			DebugWireOverlay,
			DebugHalfTransparent,
			DebugBuffersBoundingBoxes,
			DebugAll,

			ModelMaterialSolid,
			ModelMaterialTransparent,
			ModelMaterialReflection,

			CameraMaya,
			CameraFirstPerson,

			PositionText,

			About,
			Quit,

			TextureFilter,
			SkinTransparency,
			SkinAnimationFPS,

			ButtonSetScale,
			ButtonScaleMul10,
			ButtonScaleDiv10,
			ButtonOpenModel,
			ButtonShowAbout,
			ButtonShowToolbox,
			ButtonSelectArchive,

			Logo
		}

		// And some magic numbers
		const int MaxFramerate = 1000;
		const int DefaultFramerate = 30;

		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(800, 600), 16);
			if (device == null)
				return;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.SetWindowResizable(true);
			device.SetWindowCaption("Irrlicht Engine - Loading...");

			VideoDriver driver = device.VideoDriver;
			GUIEnvironment env = device.GUIEnvironment;
			SceneManager smgr = device.SceneManager;

			//smgr->getParameters()->setAttribute(scene::COLLADA_CREATE_SCENE_INSTANCES, true);

			//driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

			smgr.AddLightSceneNode(null, new Vector3Df(200), new Colorf(1.0f, 1.0f, 1.0f), 2000);
			//smgr->setAmbientLight(video::SColorf(0.3f,0.3f,0.3f));

			// add our media directory as "search path"
			//device.FileSystem.AddFolderFileArchive("../media/");

			// read configuration from xml file
			XmlDocument xml = new XmlDocument();
			xml.Load("../media/config.xml");
			startUpModelFile = xml.DocumentElement["startUpModel"].Attributes["file"].Value;
			caption = xml.DocumentElement["messageText"].Attributes["caption"].Value;
			messageText = xml.DocumentElement["messageText"].InnerText;

			if (args.Length > 0)
				startUpModelFile = args[0];

			// set a nicer font
			GUIFont font = env.GetFont("fonthaettenschweiler.bmp");
			if (font != null)
				env.Skin.SetFont(GUIDefaultFont.Default, font);

			// create menu
			//gui::IGUIContextMenu* menu = env->addMenu();
			//menu->addItem(L"File", -1, true, true);
			//menu->addItem(L"View", -1, true, true);
			//menu->addItem(L"Camera", -1, true, true);
			//menu->addItem(L"Help", -1, true, true);

			//gui::IGUIContextMenu* submenu;
			//submenu = menu->getSubMenu(0);
			//submenu->addItem(L"Open Model File & Texture...", GUI_ID_OPEN_MODEL);
			//submenu->addItem(L"Set Model Archive...", GUI_ID_SET_MODEL_ARCHIVE);
			//submenu->addItem(L"Load as Octree", GUI_ID_LOAD_AS_OCTREE);
			//submenu->addSeparator();
			//submenu->addItem(L"Quit", GUI_ID_QUIT);

			//submenu = menu->getSubMenu(1);
			//submenu->addItem(L"sky box visible", GUI_ID_SKY_BOX_VISIBLE, true, false, true);
			//submenu->addItem(L"toggle model debug information", GUI_ID_TOGGLE_DEBUG_INFO, true, true);
			//submenu->addItem(L"model material", -1, true, true );

			//submenu = submenu->getSubMenu(1);
			//submenu->addItem(L"Off", GUI_ID_DEBUG_OFF);
			//submenu->addItem(L"Bounding Box", GUI_ID_DEBUG_BOUNDING_BOX);
			//submenu->addItem(L"Normals", GUI_ID_DEBUG_NORMALS);
			//submenu->addItem(L"Skeleton", GUI_ID_DEBUG_SKELETON);
			//submenu->addItem(L"Wire overlay", GUI_ID_DEBUG_WIRE_OVERLAY);
			//submenu->addItem(L"Half-Transparent", GUI_ID_DEBUG_HALF_TRANSPARENT);
			//submenu->addItem(L"Buffers bounding boxes", GUI_ID_DEBUG_BUFFERS_BOUNDING_BOXES);
			//submenu->addItem(L"All", GUI_ID_DEBUG_ALL);

			//submenu = menu->getSubMenu(1)->getSubMenu(2);
			//submenu->addItem(L"Solid", GUI_ID_MODEL_MATERIAL_SOLID);
			//submenu->addItem(L"Transparent", GUI_ID_MODEL_MATERIAL_TRANSPARENT);
			//submenu->addItem(L"Reflection", GUI_ID_MODEL_MATERIAL_REFLECTION);

			//submenu = menu->getSubMenu(2);
			//submenu->addItem(L"Maya Style", GUI_ID_CAMERA_MAYA);
			//submenu->addItem(L"First Person", GUI_ID_CAMERA_FIRST_PERSON);

			//submenu = menu->getSubMenu(3);
			//submenu->addItem(L"About", GUI_ID_ABOUT);

			// create toolbar

			//gui::IGUIToolBar* bar = env->addToolBar();

			//video::ITexture* image = driver->getTexture("open.png");
			//bar->addButton(GUI_ID_BUTTON_OPEN_MODEL, 0, L"Open a model",image, 0, false, true);

			//image = driver->getTexture("tools.png");
			//bar->addButton(GUI_ID_BUTTON_SHOW_TOOLBOX, 0, L"Open Toolset",image, 0, false, true);

			//image = driver->getTexture("zip.png");
			//bar->addButton(GUI_ID_BUTTON_SELECT_ARCHIVE, 0, L"Set Model Archive",image, 0, false, true);

			//image = driver->getTexture("help.png");
			//bar->addButton(GUI_ID_BUTTON_SHOW_ABOUT, 0, L"Open Help", image, 0, false, true);

			// create a combobox with some senseless texts

			//gui::IGUIComboBox* box = env->addComboBox(core::rect<s32>(250,4,350,23), bar, GUI_ID_TEXTUREFILTER);
			//box->addItem(L"No filtering");
			//box->addItem(L"Bilinear");
			//box->addItem(L"Trilinear");
			//box->addItem(L"Anisotropic");
			//box->addItem(L"Isotropic");

			// disable alpha
			setSkinTransparency(255, env.Skin);

			// add a tabcontrol
			createToolBox();

			// create fps text
			//IGUIStaticText* fpstext = env->addStaticText(L"", core::rect<s32>(400,4,570,23), true, false, bar);
			//IGUIStaticText* postext = env->addStaticText(L"", core::rect<s32>(10,50,470,80),false, false, 0, GUI_ID_POSITION_TEXT);
			//postext->setVisible(false);

			// set window caption
			caption = string.Format("{0} - [{1}]", caption, driver.Name);
			device.SetWindowCaption(caption);

			// show about message box and load default model
			if (args.Length == 1)
				showAboutText();

			loadModel(startUpModelFile);

			// add skybox

			//SkyBox = smgr->addSkyBoxSceneNode(
			//    driver->getTexture("irrlicht2_up.jpg"),
			//    driver->getTexture("irrlicht2_dn.jpg"),
			//    driver->getTexture("irrlicht2_lf.jpg"),
			//    driver->getTexture("irrlicht2_rt.jpg"),
			//    driver->getTexture("irrlicht2_ft.jpg"),
			//    driver->getTexture("irrlicht2_bk.jpg"));

			// add a camera scene node

			//Camera[0] = smgr->addCameraSceneNodeMaya();
			//Camera[0]->setFarValue(20000.f);
			// Maya cameras reposition themselves relative to their target, so target the location where the mesh scene node is placed.
			//Camera[0]->setTarget(core::vector3df(0,30,0));

			camera[1] = smgr.AddCameraSceneNodeFPS();
			camera[1].FarValue = 20000;
			camera[1].Position = new Vector3Df(0, 0, -70);
			camera[1].Target = new Vector3Df(0, 30, 0);

			setActiveCamera(camera[0]);

			// load the irrlicht engine logo
			GUIImage img = env.AddImage(driver.GetTexture("irrlichtlogoalpha2.tga"), new Vector2Di(10, (int)driver.ScreenSize.Height - 128));
			img.ID = (int)guiID.Logo;

			// lock the logo's edges to the bottom left corner of the screen
			//img->setAlignment(EGUIA_UPPERLEFT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT);

			// draw everything

			while (device.Run() && driver != null)
			{
				if (device.WindowActive)
				{
					driver.BeginScene(true, true, new Coloru(50, 50, 50));
					smgr.DrawAll();
					env.DrawAll();
					driver.EndScene();

					string str = string.Format("FPS: {0} Tris: {1}", driver.FPS, driver.PrimitiveCountDrawn);
					//fpstext.Text = str;

					CameraSceneNode cam = device.SceneManager.ActiveCamera;
					str = string.Format("Pos: {0} Tgt: {1}", cam.Position, cam.Target);
					//postext.Text = str;
				}
				else
					device.Yield();
			}

			device.Drop();
		}

		static bool device_OnEvent(Event e)
		{
			//throw new NotImplementedException();
			return false;
		}

		static void setActiveCamera(CameraSceneNode newActive)
		{
			if (device == null)
				return;

			CameraSceneNode c = device.SceneManager.ActiveCamera;
			c.InputReceiverEnabled = false;

			newActive.InputReceiverEnabled = true;
			device.SceneManager.ActiveCamera = newActive;
		}

		static void setSkinTransparency(uint alpha, GUISkin skin)
		{
			foreach (GUIDefaultColor i in Enum.GetValues(typeof(GUIDefaultColor)))
			{
				Coloru c = skin.GetColor(i);
				c.Alpha = alpha;
				skin.SetColor(i, c);
			}
		}

		static void updateScaleInfo(SceneNode model)
		{
			//GUIElement t = device.GUIEnvironment.RootGUIElement.GetElementFromID(guiID.DialogRootWindow, true);
			//if (t == null)
			//    return;

			if (model == null)
			{
				//t.GetElementFromID(guiID.XScale, true).Text = "-";
				//t.GetElementFromID(guiID.YScale, true).Text = "-";
				//t.GetElementFromID(guiID.ZScale, true).Text = "-";
			}
			else
			{
				Vector3Df s = model.Scale;
				//t.GetElementFromID(guiID.XScale, true).Text = s.X.ToString();
				//t.GetElementFromID(guiID.YScale, true).Text = s.Y.ToString();
				//t.GetElementFromID(guiID.ZScale, true).Text = s.Z.ToString();
			}
		}

		static void showAboutText()
		{
			// create modal message box with the text loaded from the xml file
			//device.GUIEnvironment.AddMessageBox(caption, messageText);
		}

		static void loadModel(string f)
		{
			string e = Path.GetExtension(f);

			switch (e)
			{
				// if a texture is loaded apply it to the current model
				case ".jpg":
				case ".pcx":
				case ".png":
				case ".ppm":
				case ".pgm":
				case ".pbm":
				case ".psd":
				case ".tga":
				case ".bmp":
				case ".wal":
				case ".rgb":
				case ".rgba":
					Texture t = device.VideoDriver.GetTexture(f);
					if (t != null && model != null)
					{
						// always reload texture
						device.VideoDriver.RemoveTexture(t);
						t = device.VideoDriver.GetTexture(f);
						model.SetMaterialTexture(0, t);
					}
					return;

				// if a archive is loaded add it to the FileArchive
				case ".pk3":
				case ".zip":
				case ".pak":
				case ".npk":
					device.FileSystem.AddFileArchive(f);
					return;
			}

			// load a model into the engine

			if (model != null)
				model.Remove();

			model = null;

			if (e == ".irr")
			{
				device.SceneManager.LoadScene(f);
				model = device.SceneManager.GetSceneNodeFromType(SceneNodeType.AnimatedMesh);
				return;
			}

			AnimatedMesh m = device.SceneManager.GetMesh(f);
			if (m == null)
			{
				// model could not be loaded
				//if (startUpModelFile != f)
				//	device.GUIEnvironment.AddMessageBox(caption, "The model could not be loaded. Maybe it is not a supported file format.");

				return;
			}

			// set default material properties

			if (octree)
			{
				model = device.SceneManager.AddOctreeSceneNode(m.GetMesh(0));
			}
			else
			{
				AnimatedMeshSceneNode n = device.SceneManager.AddAnimatedMeshSceneNode(m);
				n.AnimationSpeed = 30;
				model = n;
			}

			model.SetMaterialFlag(MaterialFlag.Lighting, useLight);
			model.SetMaterialFlag(MaterialFlag.NormalizeNormals, useLight);
			model.DebugDataVisible = DebugSceneType.Off;

			// we need to uncheck the menu entries. would be cool to fake a menu event, but
			// that's not so simple. so we do it brute force
			//GUIContextMenu u = device.GUIEnvironment.RootGUIElement.GetElementFromID(guiID.ToggleDebugInfo, true) as GUIContextMenu;
			//if (u != null)
			//{
			//    for (int i = 0; i < 6; i++)
			//        u.SetItemChecked(i, false);
			//}

			updateScaleInfo(model);
		}

		static void createToolBox()
		{
			GUIEnvironment env = device.GUIEnvironment;
			//GUIElement root = env.RootGUIElement;

			// remove tool box if already there
			//GUIElement e = root.GetElementFromID(guiID.DialogRootWindow, true);
			//if (e != null)
			//    e.Remove();

			// create the toolbox window
			GUIWindow w = env.AddWindow(new Recti(600, 45, 800, 480), false, "Toolset", null, (int)guiID.DialogRootWindow);

			// create tab control and tabs
			//IGUITabControl* tab = env->addTabControl(core::rect<s32>(2,20,800-602,480-7), w, true, true);

			//IGUITab* t1 = tab->addTab(L"Config");

			// add some edit boxes and a button to tab one
			//env.AddStaticText("Scale:", new Recti(10, 20, 60, 45), false, false, t1);
			//env.AddStaticText("X:", new Recti(22, 48, 40, 66), false, false, t1);
			//env.AddEditBox("1.0", new Recti(40, 46, 130, 66), true, t1, guiID.XScale);
			//env.AddStaticText("Y:", new Recti(22, 82, 40, 100), false, false, t1);
			//env.AddEditBox("1.0", new Recti(40, 76, 130, 96), true, t1, guiID.YScale);
			//env.AddStaticText("Z:", new Recti(22, 108, 40, 126), false, false, t1);
			//env.AddEditBox("1.0", new Recti(40, 106, 130, 126), true, t1, guiID.ZScale);

			//env.AddButton(new Recti(10, 134, 85, 165), t1, guiID.ButtonSetScale, "Set");

			// quick scale buttons
			//env.AddButton(new Recti(65, 20, 95, 40), t1, guiID.ButtonScaleMul10, "* 10");
			//env.AddButton(new Recti(100, 20, 130, 40), t1, guiID.ButtonScaleDiv10, "* 0.1");

			updateScaleInfo(model);

			// add transparency control
			//env.AddStaticText("GUI Transparency Control:", new Recti(10, 200, 150, 225), true, false, t1);
			//GUIScrollBar b = env.AddScrollBar(true, new Recti(10, 225, 150, 240), t1, guiID.SkinTransparency);
			//b.MaxValue = 255;
			//b.Position = 255;

			// add framerate control
			//env.AddStaticText("Framerate:", new Recti(10, 240, 150, 265), true, false, t1);
			//b = env.AddScrollBar(true, new Recti(10, 265, 150, 280), t1, guiID.SkinAnimationFPS);
			//b.MaxValue = MaxFramerate;
			//b.MinValue = -MaxFramerate;
			//b.Position = DefaultFramerate;

			// bring irrlicht engine logo to front, because it now may be below the newly created toolbox
			//root->bringToFront(root->getElementFromId(guiID.Logo, true));
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
