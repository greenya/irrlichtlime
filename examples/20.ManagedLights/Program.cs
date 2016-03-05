using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _20.ManagedLights
{
    class Program
    {
        // Enough to reach the far side of each 'zone'
        const float lightRadius = 60f;

        static void Main(string[] args)
        {
            // Initialize device.

            DriverType driverType;
            if (!AskUserForDriver(out driverType))
                return;

            IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
            if (device == null)
                return;

            VideoDriver driver = device.VideoDriver;
            SceneManager smgr = device.SceneManager;
            GUIEnvironment guienv = device.GUIEnvironment;

            GUISkin skin = guienv.Skin;
            if (skin != null)
            {
                skin.SetColor(new Color(255, 255, 255, 255), GUIDefaultColor.ButtonText);
                GUIFont font = guienv.GetFont("../../media/fontlucida.png");
                if (font != null)
                    skin.SetFont(font);
            }

            guienv.AddStaticText(@"1 - No light management", new Recti(10, 10, 200, 30));
            guienv.AddStaticText(@"2 - Closest 3 lights", new Recti(10, 30, 200, 50));
            guienv.AddStaticText(@"3 - Lights in zone", new Recti(10, 50, 200, 70));

            //Add several "zones".  You could use this technique to light individual rooms, for example.
            for (float zoneX = -100f; zoneX <= 100f; zoneX += 50f)
                for (float zoneY = -60; zoneY <= 60f; zoneY += 60f)
                {
                    // Start with an empty scene node, which we will use to represent a zone.
                    SceneNode zoneRoot = smgr.AddEmptySceneNode();
                    zoneRoot.Position = new Vector3Df(zoneX, zoneY, 0);

                    // Each zone contains a rotating cube
                    MeshSceneNode node = smgr.AddCubeSceneNode(15, zoneRoot);
                    SceneNodeAnimator rotation = smgr.CreateRotationAnimator(new Vector3Df(0.25f, 0.5f, 0.75f));
                    node.AddAnimator(rotation);
                    rotation.Drop();

                    // And each cube has three lights attached to it.  The lights are attached to billboards so
                    // that we can see where they are.  The billboards are attached to the cube, so that the
                    // lights are indirect descendents of the same empty scene node as the cube.
                    BillboardSceneNode billboard = smgr.AddBillboardSceneNode(node);
                    billboard.Position = new Vector3Df(0, -14, 30);
                    billboard.SetMaterialType(MaterialType.TransparentAddColor);
                    billboard.SetMaterialTexture(0, driver.GetTexture("../../media/particle.bmp"));
                    billboard.SetMaterialFlag(MaterialFlag.Lighting, false);
                    smgr.AddLightSceneNode(billboard, new Vector3Df(0, 0, 0), new Colorf(1, 0, 0), lightRadius);

                    billboard = smgr.AddBillboardSceneNode(node);
                    billboard.Position = new Vector3Df(-21, -14, -21);
                    billboard.SetMaterialType(MaterialType.TransparentAddColor);
                    billboard.SetMaterialTexture(0, driver.GetTexture("../../media/particle.bmp"));
                    billboard.SetMaterialFlag(MaterialFlag.Lighting, false);
                    smgr.AddLightSceneNode(billboard, new Vector3Df(0, 0, 0), new Colorf(0, 1, 0), lightRadius);

                    billboard = smgr.AddBillboardSceneNode(node);
                    billboard.Position = new Vector3Df(21, -14, -21);
                    billboard.SetMaterialType(MaterialType.TransparentAddColor);
                    billboard.SetMaterialTexture(0, driver.GetTexture("../../media/particle.bmp"));
                    billboard.SetMaterialFlag(MaterialFlag.Lighting, false);
                    smgr.AddLightSceneNode(billboard, new Vector3Df(0, 0, 0), new Colorf(0, 0, 1), lightRadius);

                    // Each cube also has a smaller cube rotating around it, to show that the cubes are being
                    // lit by the lights in their 'zone', not just lights that are their direct children.
                    node = smgr.AddCubeSceneNode(5, node);
                    node.Position = new Vector3Df(0, 21, 0);
                }

            smgr.AddCameraSceneNode(null, new Vector3Df(0, 0, -130), new Vector3Df(0, 0, 0));

            MyLightManager myLightManager = new MyLightManager(smgr);
            smgr.LightManager = null; // This is the default: we won't do light management until told to do it.
            device.OnEvent += new IrrlichtDevice.EventHandler(myLightManager.MyLightManager_OnEvent);

            int lastFps = -1;

            while (device.Run())
            {
                driver.BeginScene(ClearBufferFlag.All, new Color(100, 101, 140));
                smgr.DrawAll();
                guienv.DrawAll();
                driver.EndScene();

                int fps = driver.FPS;
                if (fps != lastFps)
                {
                    lastFps = fps;
                    string str = @"Managed Lights [";
                    str += driver.Name;
                    str += "] FPS:";
                    str += fps;
                    device.SetWindowCaption(str);
                }
            }

            myLightManager.Drop(); // Drop my implicit reference
            device.Drop();
        }

		static bool AskUserForDriver(out DriverType driverType)
		{
			driverType = DriverType.Null;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL\n (b) Direct3D 9.0c\n" +
						" (c) Burning's Software Renderer\n (d) Software Renderer\n" +
						" (e) NullDevice\n (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: driverType = DriverType.OpenGL; break;
				case ConsoleKey.B: driverType = DriverType.Direct3D9; break;
				case ConsoleKey.C: driverType = DriverType.BurningsVideo; break;
				case ConsoleKey.D: driverType = DriverType.Software; break;
				case ConsoleKey.E: driverType = DriverType.Null; break;
				default:
					return false;
			}

			return true;
		}
    }
}
