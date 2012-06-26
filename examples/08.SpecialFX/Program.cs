using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _08.SpecialFX
{
	class Program
	{
		static void Main(string[] args)
		{
			bool shadows = AskUserForRealtimeShadows();

			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480), 16, false, shadows);
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			AnimatedMesh mesh = smgr.GetMesh("../../media/room.3ds");

			smgr.MeshManipulator.MakePlanarTextureMapping(mesh.GetMesh(0), 0.004f);

			SceneNode node = null;

			node = smgr.AddAnimatedMeshSceneNode(mesh);
			node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.jpg"));
			node.GetMaterial(0).SpecularColor.Set(0, 0, 0, 0);

			mesh = smgr.AddHillPlaneMesh("myHill",
				new Dimension2Df(20, 20),
				new Dimension2Di(40, 40), null, 0,
				new Dimension2Df(0),
				new Dimension2Df(10, 10));

			node = smgr.AddWaterSurfaceSceneNode(mesh.GetMesh(0), 3.0f, 300.0f, 30.0f);
			node.Position = new Vector3Df(0, 7, 0);

			node.SetMaterialTexture(0, driver.GetTexture("../../media/stones.jpg"));
			node.SetMaterialTexture(1, driver.GetTexture("../../media/water.jpg"));

			node.SetMaterialType(MaterialType.Reflection2Layer);

			// create light

			node = smgr.AddLightSceneNode(null, new Vector3Df(0), new Colorf(1.0f, 0.6f, 0.7f, 1.0f), 800);
			SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 150, 0), 250);
			node.AddAnimator(anim);
			anim.Drop();

			// attach billboard to light

			node = smgr.AddBillboardSceneNode(node, new Dimension2Df(50, 50));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialType(MaterialType.TransparentAddColor);
			node.SetMaterialTexture(0, driver.GetTexture("../../media/particlewhite.bmp"));

			// create a particle system

			ParticleSystemSceneNode ps = smgr.AddParticleSystemSceneNode(false);

			ParticleEmitter em = ps.CreateBoxEmitter(
				new AABBox(-7, 0, -7, 7, 1, 7),	// emitter size
				new Vector3Df(0.0f, 0.06f, 0.0f),	// initial direction
				80, 100,							// emit rate
				new Color(255, 255, 255, 0),		// darkest color
				new Color(255, 255, 255, 0),		// brightest color
				800, 2000, 0,						// min and max age, angle
				new Dimension2Df(10.0f),			// min size
				new Dimension2Df(20.0f));			// max size

			ps.Emitter = em; // this grabs the emitter
			em.Drop(); // so we can drop it here without deleting it

			ParticleAffector paf = ps.CreateFadeOutParticleAffector();

			ps.AddAffector(paf); // same goes for the affector
			paf.Drop();

			ps.Position = new Vector3Df(-70, 60, 40);
			ps.Scale = new Vector3Df(2);
			ps.SetMaterialFlag(MaterialFlag.Lighting, false);
			ps.SetMaterialFlag(MaterialFlag.ZWrite, false);
			ps.SetMaterialTexture(0, driver.GetTexture("../../media/fire.bmp"));
			ps.SetMaterialType(MaterialType.TransparentAddColor);

			VolumeLightSceneNode n = smgr.AddVolumeLightSceneNode(null, -1,
				32,								// Subdivisions on U axis
				32,								// Subdivisions on V axis
				new Color(255, 255, 255, 0),	// foot color
				new Color(0, 0, 0, 0));		// tail color

			if (n != null)
			{
				n.Scale = new Vector3Df(56);
				n.Position = new Vector3Df(-120, 50, 40);

				// load textures for animation
				List<Texture> textures = new List<Texture>();
				for (int i = 7; i > 0; i--)
				{
					string s = string.Format("../../media/portal{0}.bmp", i);
					textures.Add(driver.GetTexture(s));
				}

				// create texture animator
				SceneNodeAnimator glow = smgr.CreateTextureAnimator(textures, 0.150f);

				// add the animator
				n.AddAnimator(glow);

				// drop the animator because it was created with a create() function
				glow.Drop();
			}

			// add animated character

			mesh = smgr.GetMesh("../../media/dwarf.x");
			AnimatedMeshSceneNode anode = smgr.AddAnimatedMeshSceneNode(mesh);

			anode.Position = new Vector3Df(-50, 20, -60);
			anode.AnimationSpeed = 15;

			// add shadow
			anode.AddShadowVolumeSceneNode();
			smgr.ShadowColor = new Color(0, 0, 0, 150);

			// make the model a little bit bigger and normalize its normals
			// because of the scaling, for correct lighting
			anode.Scale = new Vector3Df(2);
			anode.SetMaterialFlag(MaterialFlag.NormalizeNormals, true);

			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS();
			camera.Position = new Vector3Df(-50, 50, -150);

			// disable mouse cursor
			device.CursorControl.Visible = false;

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(true, true, new Color(0));
					smgr.DrawAll();
					driver.EndScene();

					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.SetWindowCaption(String.Format(
							"SpecialFX example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
		}

		static bool AskUserForRealtimeShadows()
		{
			Console.WriteLine("Please press 'y' if you want to use realtime shadows.");
			return Console.ReadKey().Key == ConsoleKey.Y;
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
