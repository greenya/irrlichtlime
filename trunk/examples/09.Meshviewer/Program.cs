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
using IrrlichtLime.IO;

namespace _09.Meshviewer
{
	static class Program
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

			device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(800, 600), 16);
			if (device == null)
				return;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.SetWindowResizable(true);
			device.SetWindowCaption("Irrlicht Engine - Loading...");

			VideoDriver driver = device.VideoDriver;
			GUIEnvironment env = device.GUIEnvironment;
			SceneManager smgr = device.SceneManager;

			//smgr->getParameters()->setAttribute(scene::COLLADA_CREATE_SCENE_INSTANCES, true);

			driver.SetTextureCreationFlag(TextureCreationFlag.Always32Bit, true);

			smgr.AddLightSceneNode(null, new Vector3Df(200), new Colorf(1.0f, 1.0f, 1.0f), 2000);
			smgr.AmbientLight = new Colorf(0.3f, 0.3f, 0.3f);

			// add our media directory as "search path"
			device.FileSystem.AddFileArchive("../media/");

			// read configuration from xml file
			// (we use .NET way to do this, since Lime doesn't support native Irrlicht' xml reader)
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
				env.Skin.SetFont(font);

			// create menu
			GUIContextMenu menu = env.AddMenu();
			menu.AddItem("File", -1, true, true);
			menu.AddItem("View", -1, true, true);
			menu.AddItem("Camera", -1, true, true);
			menu.AddItem("Help", -1, true, true);

			GUIContextMenu submenu;
			submenu = menu.GetSubMenu(0);
			submenu.AddItem("Open Model File & Texture...", (int)guiID.OpenModel);
			submenu.AddItem("Set Model Archive...", (int)guiID.SetModelArchive);
			submenu.AddItem("Load as Octree", (int)guiID.LoadAsOctree);
			submenu.AddSeparator();
			submenu.AddItem("Quit", (int)guiID.Quit);

			submenu = menu.GetSubMenu(1);
			submenu.AddItem("sky box visible", (int)guiID.SkyBoxVisible, true, false, true);
			submenu.AddItem("toggle model debug information", (int)guiID.ToggleDebugInfo, true, true);
			submenu.AddItem("model material", -1, true, true);

			submenu = submenu.GetSubMenu(1);
			submenu.AddItem("Off", (int)guiID.DebugOff);
			submenu.AddItem("Bounding Box", (int)guiID.DebugBoundingBox);
			submenu.AddItem("Normals", (int)guiID.DebugNormals);
			submenu.AddItem("Skeleton", (int)guiID.DebugSkeleton);
			submenu.AddItem("Wire overlay", (int)guiID.DebugWireOverlay);
			submenu.AddItem("Half-Transparent", (int)guiID.DebugHalfTransparent);
			submenu.AddItem("Buffers bounding boxes", (int)guiID.DebugBuffersBoundingBoxes);
			submenu.AddItem("All", (int)guiID.DebugAll);

			submenu = menu.GetSubMenu(1).GetSubMenu(2);
			submenu.AddItem("Solid", (int)guiID.ModelMaterialSolid);
			submenu.AddItem("Transparent", (int)guiID.ModelMaterialTransparent);
			submenu.AddItem("Reflection", (int)guiID.ModelMaterialReflection);

			submenu = menu.GetSubMenu(2);
			submenu.AddItem("Maya Style", (int)guiID.CameraMaya);
			submenu.AddItem("First Person", (int)guiID.CameraFirstPerson);

			submenu = menu.GetSubMenu(3);
			submenu.AddItem("About", (int)guiID.About);

			// create toolbar

			GUIToolBar bar = env.AddToolBar();

			Texture image = driver.GetTexture("open.png");
			bar.AddButton((int)guiID.ButtonOpenModel, null, "Open a model", image, null, false, true);

			image = driver.GetTexture("tools.png");
			bar.AddButton((int)guiID.ButtonShowToolbox, null, "Open Toolset", image, null, false, true);

			image = driver.GetTexture("zip.png");
			bar.AddButton((int)guiID.ButtonSelectArchive, null, "Set Model Archive", image, null, false, true);

			image = driver.GetTexture("help.png");
			bar.AddButton((int)guiID.ButtonShowAbout, null, "Open Help", image, null, false, true);

			// create a combobox with some senseless texts

			GUIComboBox box = env.AddComboBox(new Recti(250, 4, 350, 23), bar, (int)guiID.TextureFilter);
			box.AddItem("No filtering");
			box.AddItem("Bilinear");
			box.AddItem("Trilinear");
			box.AddItem("Anisotropic");
			box.AddItem("Isotropic");

			// disable alpha
			setSkinTransparency(255, env.Skin);

			// add a tabcontrol
			createToolBox();

			// create fps text
			GUIStaticText fpstext = env.AddStaticText("", new Recti(400, 4, 570, 23), true, false, bar);
			GUIStaticText postext = env.AddStaticText("", new Recti(10, 50, 470, 80), false, false, null, (int)guiID.PositionText);
			postext.Visible = false;

			// show about message box and load default model
			if (args.Length == 0)
				showAboutText();

			loadModel(startUpModelFile);

			// add skybox

			skybox = smgr.AddSkyBoxSceneNode(
				"irrlicht2_up.jpg", "irrlicht2_dn.jpg",
				"irrlicht2_lf.jpg", "irrlicht2_rt.jpg",
				"irrlicht2_ft.jpg", "irrlicht2_bk.jpg");

			// add a camera scene node

			camera[0] = smgr.AddCameraSceneNodeMaya();
			camera[0].FarValue = 20000;
			// Maya cameras reposition themselves relative to their target,
			// so target the location where the mesh scene node is placed.
			camera[0].Target = new Vector3Df(0, 30, 0);

			camera[1] = smgr.AddCameraSceneNodeFPS();
			camera[1].FarValue = 20000;
			camera[1].Position = new Vector3Df(0, 0, -70);
			camera[1].Target = new Vector3Df(0, 30, 0);

			setActiveCamera(camera[0]);

			// load the irrlicht engine logo
			GUIImage img = env.AddImage(
				driver.GetTexture("irrlichtlogoalpha2.tga"),
				new Vector2Di(10, (int)driver.ScreenSize.Height - 128));
			img.ID = (int)guiID.Logo;

			// lock the logo's edges to the bottom left corner of the screen
			img.SetAlignment(GUIAlignment.UpperLeft, GUIAlignment.UpperLeft, GUIAlignment.LowerRight, GUIAlignment.LowerRight);

			// set window caption
			caption = string.Format("{0} - [{1}]", caption, driver.Name);
			device.SetWindowCaption(caption);

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
					fpstext.Text = str;

					CameraSceneNode cam = device.SceneManager.ActiveCamera;
					str = string.Format("Pos: {0} Tgt: {1}", cam.Position, cam.Target);
					postext.Text = str;
				}
				else
					device.Yield();
			}

			device.Drop();
		}

		static bool device_OnEvent(Event e)
		{
			// Escape swaps Camera Input
			if (e.Type == EventType.Key && !e.Key.PressedDown && OnKeyUp(e.Key.Key))
				return true;

			if (e.Type == EventType.GUI)
			{
				guiID id = (guiID)e.GUI.Caller.ID;
				GUIEnvironment env = device.GUIEnvironment;

				switch (e.GUI.Type)
				{
					case GUIEventType.MenuItemSelected:
						// a menu item was clicked
						OnMenuItemSelected(e.GUI.Caller as GUIContextMenu);
						break;

					case GUIEventType.FileDialogFileSelected:
						// load the model file, selected in the file open dialog
						loadModel((e.GUI.Caller as GUIFileOpenDialog).FileName);
						break;

					case GUIEventType.ScrollBarChanged:
						if (id == guiID.SkinTransparency)
						{
							// control skin transparency
							int p = (e.GUI.Caller as GUIScrollBar).Position;
							setSkinTransparency((uint)p, env.Skin);
						}
						else if (id == guiID.SkinAnimationFPS)
						{
							// control animation speed
							int p = (e.GUI.Caller as GUIScrollBar).Position;
							if (model.Type == SceneNodeType.AnimatedMesh)
								(model as AnimatedMeshSceneNode).AnimationSpeed = p;
						}

						break;

					case GUIEventType.ComboBoxChanged:
						if (id == guiID.TextureFilter)
							// control anti-aliasing/filtering
							OnTextureFilterSelected(e.GUI.Caller as GUIComboBox);

						break;

					case GUIEventType.ButtonClicked:
						switch (id)
						{
							case guiID.ButtonSetScale:
								// set scale
								GUIElement r = env.RootElement;
								Vector3Df s = new Vector3Df(
									Convert.ToSingle(r.GetElementFromID((int)guiID.XScale, true).Text),
									Convert.ToSingle(r.GetElementFromID((int)guiID.YScale, true).Text),
									Convert.ToSingle(r.GetElementFromID((int)guiID.ZScale, true).Text));

								if (model != null)
									model.Scale = s;

								updateScaleInfo(model);
								break;

							case guiID.ButtonScaleMul10:
								if (model != null)
									model.Scale *= 10;

								updateScaleInfo(model);
								break;

							case guiID.ButtonScaleDiv10:
								if (model != null)
									model.Scale *= 0.1f;

								updateScaleInfo(model);
								break;

							case guiID.ButtonOpenModel:
								env.AddFileOpenDialog("Please select a model file to open");
								break;

							case guiID.ButtonSelectArchive:
								env.AddFileOpenDialog("Please select your game archive/directory");
								break;

							case guiID.ButtonShowAbout:
								showAboutText();
								break;

							case guiID.ButtonShowToolbox:
								createToolBox();
								break;
						}

						break; // case GUIEventType.ButtonClicked:
				}
			}

			return false;
		}

		static bool OnKeyUp(KeyCode keyCode)
		{
			if (device == null)
				return false;

			switch (keyCode)
			{
				case KeyCode.Esc:
					CameraSceneNode c = device.SceneManager.ActiveCamera;
					if (c != null)
						c.InputReceiverEnabled = !c.InputReceiverEnabled;

					return true;

				case KeyCode.F1:
					GUIElement e = device.GUIEnvironment.RootElement.GetElementFromID((int)guiID.PositionText);
					if (e != null)
						e.Visible = !e.Visible;

					break;

				case KeyCode.KeyM:
					device.MinimizeWindow();
					break;

				case KeyCode.KeyL:
					useLight = !useLight;
					if (model != null)
					{
						model.SetMaterialFlag(MaterialFlag.Lighting, useLight);
						model.SetMaterialFlag(MaterialFlag.NormalizeNormals, useLight);
					}

					break;
			}

			return false;
		}

		static void OnMenuItemSelected(GUIContextMenu menu)
		{
			guiID id = (guiID)menu.SelectedCommandID;
			GUIEnvironment env = device.GUIEnvironment;

			switch (id)
			{
				case guiID.OpenModel: // FilOnButtonSetScalinge -> Open Model
					env.AddFileOpenDialog("Please select a model file to open");
					break;

				case guiID.SetModelArchive: // File -> Set Model Archive
					env.AddFileOpenDialog("Please select your game archive/directory");
					break;

				case guiID.LoadAsOctree: // File -> LoadAsOctree
					octree = !octree;
					menu.SetItemChecked(menu.SelectedIndex, octree);
					break;

				case guiID.Quit: // File -> Quit
					device.Close();
					break;

				case guiID.SkyBoxVisible: // View -> Skybox
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));
					skybox.Visible = !skybox.Visible;
					break;

				case guiID.DebugOff: // View -> Debug Information -> Off
					for (int i = 1; i <= 6; i++)
						menu.SetItemChecked(menu.SelectedIndex + i, false);

					if (model != null)
						model.DebugDataVisible = DebugSceneType.Off;

					break;

				case guiID.DebugBoundingBox: // View -> Debug Information -> Bounding Box
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.BBox;

					break;

				case guiID.DebugNormals: // View -> Debug Information -> Normals
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.Normals;

					break;

				case guiID.DebugSkeleton: // View -> Debug Information -> Skeleton
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.Skeleton;

					break;

				case guiID.DebugWireOverlay: // View -> Debug Information -> Wire overlay
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.MeshWireOverlay;

					break;

				case guiID.DebugHalfTransparent: // View -> Debug Information -> Half-Transparent
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.HalfTransparency;

					break;

				case guiID.DebugBuffersBoundingBoxes: // View -> Debug Information -> Buffers bounding boxes
					menu.SetItemChecked(menu.SelectedIndex, !menu.GetItemChecked(menu.SelectedIndex));

					if (model != null)
						model.DebugDataVisible ^= DebugSceneType.BBoxBuffers;

					break;

				case guiID.DebugAll: // View -> Debug Information -> All
					for (int i = 1; i <= 6; i++)
						menu.SetItemChecked(menu.SelectedIndex - i, true);

					if (model != null)
						model.DebugDataVisible = DebugSceneType.Full;

					break;

				case guiID.About: // Help->About
					showAboutText();
					break;

				case guiID.ModelMaterialSolid: // View -> Material -> Solid
					if (model != null)
						model.SetMaterialType(MaterialType.Solid);

					break;

				case guiID.ModelMaterialTransparent: // View -> Material -> Transparent
					if (model != null)
						model.SetMaterialType(MaterialType.TransparentAddColor);

					break;

				case guiID.ModelMaterialReflection: // View -> Material -> Reflection
					if (model != null)
						model.SetMaterialType(MaterialType.SphereMap);

					break;

				case guiID.CameraMaya:
					setActiveCamera(camera[0]);
					break;

				case guiID.CameraFirstPerson:
					setActiveCamera(camera[1]);
					break;
			}
		}

		static void OnTextureFilterSelected(GUIComboBox combo)
		{
			if (model == null)
				return;

			int p = combo.SelectedIndex;
			switch (p)
			{
				case 0: // No filtering
					model.SetMaterialFlag(MaterialFlag.BilinearFilter, false);
					model.SetMaterialFlag(MaterialFlag.TrilinearFilter, false);
					model.SetMaterialFlag(MaterialFlag.AnisotropicFilter, false);
					break;

				case 1: // Bilinear
					model.SetMaterialFlag(MaterialFlag.BilinearFilter, true);
					model.SetMaterialFlag(MaterialFlag.TrilinearFilter, false);
					break;

				case 2: // Trilinear
					model.SetMaterialFlag(MaterialFlag.BilinearFilter, false);
					model.SetMaterialFlag(MaterialFlag.TrilinearFilter, true);
					break;

				case 3: // Anisotropic
					model.SetMaterialFlag(MaterialFlag.AnisotropicFilter, true);
					break;

				case 4: // Isotropic
					model.SetMaterialFlag(MaterialFlag.AnisotropicFilter, false);
					break;
			}
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
				skin.SetColor(c, i);
			}
		}

		static void updateScaleInfo(SceneNode model)
		{
			GUIElement t = device.GUIEnvironment.RootElement.GetElementFromID((int)guiID.DialogRootWindow, true);
			if (t == null)
				return;

			if (model == null)
			{
				t.GetElementFromID((int)guiID.XScale, true).Text = "-";
				t.GetElementFromID((int)guiID.YScale, true).Text = "-";
				t.GetElementFromID((int)guiID.ZScale, true).Text = "-";
			}
			else
			{
				Vector3Df s = model.Scale;
				t.GetElementFromID((int)guiID.XScale, true).Text = s.X.ToString();
				t.GetElementFromID((int)guiID.YScale, true).Text = s.Y.ToString();
				t.GetElementFromID((int)guiID.ZScale, true).Text = s.Z.ToString();
			}
		}

		static void showAboutText()
		{
			device.GUIEnvironment.AddMessageBox(caption, messageText);
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
				if (startUpModelFile != f)
					device.GUIEnvironment.AddMessageBox(caption, "The model could not be loaded. Maybe it is not a supported file format.");

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
			GUIContextMenu u = device.GUIEnvironment.RootElement.GetElementFromID((int)guiID.ToggleDebugInfo, true) as GUIContextMenu;
			if (u != null)
			{
				for (int i = 0; i < 6; i++)
					u.SetItemChecked(i, false);
			}

			updateScaleInfo(model);
		}

		static void createToolBox()
		{
			GUIEnvironment env = device.GUIEnvironment;
			GUIElement root = env.RootElement;

			// remove tool box if already there
			GUIElement e = root.GetElementFromID((int)guiID.DialogRootWindow, true);
			if (e != null)
				e.Remove();

			// create the toolbox window
			GUIWindow w = env.AddWindow(new Recti(600, 45, 800, 480), false, "Toolset", null, (int)guiID.DialogRootWindow);

			// create tab control and tabs
			GUITabControl tab = env.AddTabControl(new Recti(2, 20, 800 - 602, 480 - 7), w, true, true);

			GUITab t1 = tab.AddTab("Config");

			// add some edit boxes and a button to tab one
			env.AddStaticText("Scale:", new Recti(10, 20, 60, 45), false, false, t1);
			env.AddStaticText("X:", new Recti(22, 48, 40, 66), false, false, t1);
			env.AddEditBox("1.0", new Recti(40, 46, 130, 66), true, t1, (int)guiID.XScale);
			env.AddStaticText("Y:", new Recti(22, 78, 40, 96), false, false, t1);
			env.AddEditBox("1.0", new Recti(40, 76, 130, 96), true, t1, (int)guiID.YScale);
			env.AddStaticText("Z:", new Recti(22, 108, 40, 126), false, false, t1);
			env.AddEditBox("1.0", new Recti(40, 106, 130, 126), true, t1, (int)guiID.ZScale);

			env.AddButton(new Recti(10, 134, 85, 165), t1, (int)guiID.ButtonSetScale, "Set");

			// quick scale buttons
			env.AddButton(new Recti(65, 20, 95, 40), t1, (int)guiID.ButtonScaleMul10, "* 10");
			env.AddButton(new Recti(100, 20, 130, 40), t1, (int)guiID.ButtonScaleDiv10, "* 0.1");

			updateScaleInfo(model);

			// add transparency control
			env.AddStaticText("GUI Transparency Control:", new Recti(10, 200, 150, 225), true, false, t1);
			GUIScrollBar b = env.AddScrollBar(true, new Recti(10, 225, 150, 240), t1, (int)guiID.SkinTransparency);
			b.MaxValue = 255;
			b.Position = 255;

			// add framerate control
			env.AddStaticText("Framerate:", new Recti(10, 240, 150, 265), true, false, t1);
			b = env.AddScrollBar(true, new Recti(10, 265, 150, 280), t1, (int)guiID.SkinAnimationFPS);
			b.MaxValue = MaxFramerate;
			b.MinValue = -MaxFramerate;
			b.Position = DefaultFramerate;

			// bring irrlicht engine logo to front, because it now may be below the newly created toolbox
			root.BringToFront(root.GetElementFromID((int)guiID.Logo, true));
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
