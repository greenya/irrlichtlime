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

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(640, 480), 16, false, shadows);
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			AnimatedMesh mesh = smgr.GetMesh("../media/room.3ds");

			//smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

			SceneNode node = null;

			node = smgr.AddAnimatedMeshSceneNode(mesh);
			node.SetMaterialTexture(0, driver.GetTexture("../media/wall.jpg"));
			node.GetMaterial(0).SpecularColor.Set(0, 0, 0, 0);

			//mesh = smgr->addHillPlaneMesh( "myHill",
			//    core::dimension2d<f32>(20,20),
			//    core::dimension2d<u32>(40,40), 0, 0,
			//    core::dimension2d<f32>(0,0),
			//    core::dimension2d<f32>(10,10));

			//node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 3.0f, 300.0f, 30.0f);
			//node->setPosition(core::vector3df(0,7,0));

			//node->setMaterialTexture(0, driver->getTexture("../../media/stones.jpg"));
			//node->setMaterialTexture(1, driver->getTexture("../../media/water.jpg"));

			//node->setMaterialType(video::EMT_REFLECTION_2_LAYER);

			// create light

			node = smgr.AddLightSceneNode(null, new Vector3Df(0), new Colorf(1.0f, 0.6f, 0.7f, 1.0f), 800);
			SceneNodeAnimator anim = smgr.CreateFlyCircleAnimator(new Vector3Df(0, 150, 0), 250);
			node.AddAnimator(anim);
			anim.Drop();

			// attach billboard to light

			node = smgr.AddBillboardSceneNode(node, new Dimension2Df(50, 50));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialType(MaterialType.TransparentAddColor);
			node.SetMaterialTexture(0, driver.GetTexture("../media/particlewhite.bmp"));

			// create a particle system

			//scene::IParticleSystemSceneNode* ps =
			//    smgr->addParticleSystemSceneNode(false);

			//scene::IParticleEmitter* em = ps->createBoxEmitter(
			//        core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
			//        core::vector3df(0.0f,0.06f,0.0f),   // initial direction
			//        80,100,                             // emit rate
			//        video::SColor(0,255,255,255),       // darkest color
			//        video::SColor(0,255,255,255),       // brightest color
			//        800,2000,0,                         // min and max age, angle
			//        core::dimension2df(10.f,10.f),         // min size
			//        core::dimension2df(20.f,20.f));        // max size

			//ps->setEmitter(em); // this grabs the emitter
			//em->drop(); // so we can drop it here without deleting it

			//scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

			//ps->addAffector(paf); // same goes for the affector
			//paf->drop();

			//ps->setPosition(core::vector3df(-70,60,40));
			//ps->setScale(core::vector3df(2,2,2));
			//ps->setMaterialFlag(video::EMF_LIGHTING, false);
			//ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			//ps->setMaterialTexture(0, driver->getTexture("../../media/fire.bmp"));
			//ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

			//scene::IVolumeLightSceneNode * n = smgr->addVolumeLightSceneNode(0, -1,
			//                    32,                              // Subdivisions on U axis
			//                    32,                              // Subdivisions on V axis
			//                    video::SColor(0, 255, 255, 255), // foot color
			//                    video::SColor(0, 0, 0, 0));      // tail color

			//if (n)
			//{
			//        n->setScale(core::vector3df(56.0f, 56.0f, 56.0f));
			//        n->setPosition(core::vector3df(-120,50,40));

			//        // load textures for animation
			//        core::array<video::ITexture*> textures;
			//        for (s32 g=7; g > 0; --g)
			//        {
			//                core::stringc tmp;
			//                tmp = "../../media/portal";
			//                tmp += g;
			//                tmp += ".bmp";
			//                video::ITexture* t = driver->getTexture( tmp.c_str() );
			//                textures.push_back(t);
			//        }

			//        // create texture animator
			//        scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures, 150);

			//        // add the animator
			//        n->addAnimator(glow);

			//        // drop the animator because it was created with a create() function
			//        glow->drop();
			//}

			// add animated character

			mesh = smgr.GetMesh("../media/dwarf.x");
			AnimatedMeshSceneNode anode = smgr.AddAnimatedMeshSceneNode(mesh);

			anode.Position = new Vector3Df(-50, 20, -60);
			anode.AnimationSpeed = 15;

			// add shadow
			//anode->addShadowVolumeSceneNode();
			smgr.ShadowColor = new Coloru(0, 0, 0, 150);

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
			if (device.WindowActive)
			{
				driver.BeginScene(true, true, new Coloru(0));
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
