using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _11.PerPixelLighting
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;
			GUIEnvironment env = device.GUIEnvironment;

			driver.SetTextureCreationFlag(TextureCreationFlag.Always32Bit, true);

			// add irrlicht logo
			env.AddImage(driver.GetTexture("../../media/irrlichtlogoalpha2.tga"), new Vector2Di(10));

			// add camera
			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS();
			camera.Position = new Vector3Df(-200, 200, -200);

			// disable mouse cursor
			device.CursorControl.Visible = false;

			driver.Fog = new Fog(new Color(138, 125, 81, 0), FogType.Linear, 250, 1000, 0.003f, true, false);

			AnimatedMesh roomMesh = smgr.GetMesh("../../media/room.3ds");
			SceneNode room = null;
			SceneNode earth = null;

			if (roomMesh != null)
			{
				// the room mesh doesn't have proper texture mapping on the floor,
				// so we can recreate them on runtime
				smgr.MeshManipulator.MakePlanarTextureMapping(roomMesh.GetMesh(0), 0.003f);

				Texture normalMap = driver.GetTexture("../../media/rockwall_height.bmp");
				if (normalMap != null)
					driver.MakeNormalMapTexture(normalMap, 9.0f);

				Mesh tangentMesh = smgr.MeshManipulator.CreateMeshWithTangents(roomMesh.GetMesh(0));
				room = smgr.AddMeshSceneNode(tangentMesh);
				room.SetMaterialTexture(0, driver.GetTexture("../../media/rockwall.jpg"));
				room.SetMaterialTexture(1, normalMap);
				room.GetMaterial(0).SpecularColor = new Color(0);
				room.GetMaterial(0).Shininess = 0.0f;
				room.SetMaterialFlag(MaterialFlag.Fog, true);
				room.SetMaterialType(MaterialType.ParallaxMapSolid);
				room.GetMaterial(0).MaterialTypeParam = 1.0f / 64.0f; // adjust height for parallax effect

				tangentMesh.Drop(); // drop mesh because we created it with a "create" call
			}

			// add earth sphere
			AnimatedMesh earthMesh = smgr.GetMesh("../../media/earth.x");
			if (earthMesh != null)
			{
				// perform various task with the mesh manipulator
				MeshManipulator manipulator = smgr.MeshManipulator;

				// create mesh copy with tangent informations from original earth.x mesh
				Mesh tangentSphereMesh = manipulator.CreateMeshWithTangents(earthMesh.GetMesh(0));

				// set the alpha value of all vertices to 200
				manipulator.SetVertexColorAlpha(tangentSphereMesh, 200);

				// scale the mesh by factor 50
				Matrix m = new Matrix();
				m.Scale = new Vector3Df(50);
				manipulator.Transform(tangentSphereMesh, m);

				earth = smgr.AddMeshSceneNode(tangentSphereMesh);
				earth.Position = new Vector3Df(-70, 130, 45);

				// load heightmap, create normal map from it and set it
				Texture earthNormalMap = driver.GetTexture("../../media/earthbump.jpg");
				if (earthNormalMap != null)
				{
					driver.MakeNormalMapTexture(earthNormalMap, 20);
					earth.SetMaterialTexture(1, earthNormalMap);
					earth.SetMaterialType(MaterialType.NormalMapTransparentVertexAlpha);
				}

				// adjust material settings
				earth.SetMaterialFlag(MaterialFlag.Fog, true);

				// add rotation animator
				SceneNodeAnimator anim = smgr.CreateRotationAnimator(new Vector3Df(0, 0.1f, 0));
				earth.AddAnimator(anim);
				anim.Drop();

				// drop mesh because we created it with a "create" call.
				tangentSphereMesh.Drop();
			}

			// add light 1 (more green)
			LightSceneNode light1 = smgr.AddLightSceneNode(null, new Vector3Df(), new Colorf(0.5f, 1.0f, 0.5f, 0.0f), 800);
			if (light1 != null)
			{
				light1.DebugDataVisible = DebugSceneType.BBox;

				// add fly circle animator to light
				SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(50, 300, 0), 190.0f, -0.003f);
				light1.AddAnimator(anim);
				anim.Drop();

				// attach billboard to the light
				SceneNode bill = smgr.AddBillboardSceneNode(light1, new Dimension2Df(60, 60));
				bill.SetMaterialFlag(MaterialFlag.Lighting, false);
				bill.SetMaterialFlag(MaterialFlag.ZWrite, false);
				bill.SetMaterialType(MaterialType.TransparentAddColor);
				bill.SetMaterialTexture(0, driver.GetTexture("../../media/particlegreen.jpg"));
			}

			// add light 2 (red)
			SceneNode light2 = smgr.AddLightSceneNode(null, new Vector3Df(), new Colorf(1.0f, 0.2f, 0.2f, 0.0f), 800.0f);
			if (light2 != null)
			{
				// add fly circle animator to light
				SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 150, 0), 200.0f, 0.001f, new Vector3Df(0.2f, 0.9f, 0.0f));
				light2.AddAnimator(anim);
				anim.Drop();

				// attach billboard to light
				SceneNode bill = smgr.AddBillboardSceneNode(light2, new Dimension2Df(120, 120));
				bill.SetMaterialFlag(MaterialFlag.Lighting, false);
				bill.SetMaterialFlag(MaterialFlag.ZWrite, false);
				bill.SetMaterialType(MaterialType.TransparentAddColor);
				bill.SetMaterialTexture(0, driver.GetTexture("../../media/particlered.bmp"));

				// add particle system
				ParticleSystemSceneNode ps = smgr.AddParticleSystemSceneNode(false, light2);

				// create and set emitter
				ParticleEmitter em = ps.CreateBoxEmitter(
					new AABBox(-3, 0, -3, 3, 1, 3),
					new Vector3Df(0.0f, 0.03f, 0.0f),
					80, 100,
					new Color(255, 255, 255, 10), new Color(255, 255, 255, 10),
					400, 1100);

				em.MinStartSize = new Dimension2Df(30.0f, 40.0f);
				em.MaxStartSize = new Dimension2Df(30.0f, 40.0f);

				ps.Emitter = em;
				em.Drop();

				// create and set affector
				ParticleAffector paf = ps.CreateFadeOutParticleAffector();
				ps.AddAffector(paf);
				paf.Drop();

				// adjust some material settings
				ps.SetMaterialFlag(MaterialFlag.Lighting, false);
				ps.SetMaterialFlag(MaterialFlag.ZWrite, false);
				ps.SetMaterialTexture(0, driver.GetTexture("../../media/fireball.bmp"));
				ps.SetMaterialType(MaterialType.TransparentAddColor);
			}

			MyEventReceiver receiver = new MyEventReceiver(device, room, earth);

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(true, true, new Color(0));

					smgr.DrawAll();
					env.DrawAll();

					driver.EndScene();

					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.SetWindowCaption(String.Format(
							"Per pixel lighting example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
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

	class MyEventReceiver
	{
		public MyEventReceiver(IrrlichtDevice device, SceneNode room, SceneNode earth)
		{
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			// store pointer to room so we can change its drawing mode
			this.driver = device.VideoDriver;
			this.room = room;
			this.earth = earth;

			GUIEnvironment env = device.GUIEnvironment;

			// set a nicer font
			GUIFont font = env.GetFont("../../media/fonthaettenschweiler.bmp");
			if (font != null)
				env.Skin.SetFont(font);

			// add window and listbox
			GUIWindow window = env.AddWindow(new Recti(460, 375, 630, 470), false, "Use 'E' + 'R' to change");

			this.listBox = env.AddListBox(new Recti(2, 22, 165, 88), window);
			this.listBox.AddItem("Diffuse");
			this.listBox.AddItem("Bump mapping");
			this.listBox.AddItem("Parallax mapping");
			this.listBox.SelectedIndex = 1;

			// create problem text
			this.problemText = env.AddStaticText(
				"Your hardware or this renderer is not able to use the needed shaders for this material. Using fall back materials.",
				new Recti(150, 20, 470, 80));

			this.problemText.OverrideColor = new Color(255, 255, 255, 100);

			// set start material (prefer parallax mapping if available)
			MaterialRenderer renderer = this.driver.GetMaterialRenderer(MaterialType.ParallaxMapSolid);
			if (renderer != null && renderer.Capability == 0)
				this.listBox.SelectedIndex = 2;

			// set the material which is selected in the listbox
			setMaterial();
		}

		bool device_OnEvent(Event e)
		{
			// check if user presses the key 'E' or 'R'
			if (e.Type == EventType.Key && !e.Key.PressedDown &&
				this.room != null && this.listBox != null)
			{
				// change selected item in listbox

				int sel = this.listBox.SelectedIndex;
				if (e.Key.Key == KeyCode.KeyR)
					++sel;
				else if (e.Key.Key == KeyCode.KeyE)
					--sel;
				else
					return false;

				if (sel > 2) sel = 0;
				if (sel < 0) sel = 2;
				this.listBox.SelectedIndex = sel;

				// set the material which is selected in the listbox
				setMaterial();
			}

			return false;
		}

		private void setMaterial()
		{
			MaterialType roomMat = MaterialType.Solid;
			MaterialType earthMat = MaterialType.Solid;

			// change material setting
			switch (this.listBox.SelectedIndex)
			{
				case 0:
					roomMat = MaterialType.Solid;
					earthMat = MaterialType.TransparentVertexAlpha;
					break;

				case 1:
					roomMat = MaterialType.NormalMapSolid;
					earthMat = MaterialType.NormalMapTransparentVertexAlpha;
					break;

				case 2:
					roomMat = MaterialType.ParallaxMapSolid;
					earthMat = MaterialType.ParallaxMapTransparentVertexAlpha;
					break;
			}

			this.room.SetMaterialType(roomMat);
			this.earth.SetMaterialType(earthMat);

			// display some problem text when problem
			MaterialRenderer roomRenderer = this.driver.GetMaterialRenderer(roomMat);
			MaterialRenderer earthRenderer = this.driver.GetMaterialRenderer(earthMat);
			this.problemText.Visible =
				roomRenderer == null ||
				roomRenderer.Capability != 0 ||
				earthRenderer == null ||
				earthRenderer.Capability != 0;
		}

		private GUIStaticText problemText;
		private GUIListBox listBox;
		private SceneNode room;
		private SceneNode earth;
		private VideoDriver driver;
	}
}
