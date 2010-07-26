using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace _10.Shaders
{
	class Program
	{
		static IrrlichtDevice device = null;
		static bool useHighLevelShaders = false;

		static void Main(string[] args)
		{
			useHighLevelShaders = AskUserForHighLevelShaders();

			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			string vsFileName; // filename for the vertex shader
			string psFileName; // filename for the pixel shader

			switch (driverType)
			{
				case DriverType.Direct3D8:
					psFileName = "../media/d3d8.psh";
					vsFileName = "../media/d3d8.vsh";
					break;

				case DriverType.Direct3D9:
					if (useHighLevelShaders)
					{
						psFileName = "../media/d3d9.hlsl";
						vsFileName = psFileName; // both shaders are in the same file
					}
					else
					{
						psFileName = "../media/d3d9.psh";
						vsFileName = "../media/d3d9.vsh";
					}
					break;

				case DriverType.OpenGL:
					if (useHighLevelShaders)
					{
						psFileName = "../media/opengl.frag";
						vsFileName = "../media/opengl.vert";
					}
					else
					{
						psFileName = "../media/opengl.psh";
						vsFileName = "../media/opengl.vsh";
					}
					break;
			}

			if (!driver.QueryFeature(VideoDriverFeature.PixelShader_1_1) &&
				!driver.QueryFeature(VideoDriverFeature.ARB_FragmentProgram_1))
			{
				device.Logger.Log("WARNING: Pixel shaders disabled because of missing driver/hardware support.");
				psFileName = "";
			}

			if (!driver.QueryFeature(VideoDriverFeature.VertexShader_1_1) &&
				!driver.QueryFeature(VideoDriverFeature.ARB_VertexProgram_1))
			{
				device.Logger.Log("WARNING: Vertex shaders disabled because of missing driver/hardware support.");
				vsFileName = "";
			}

			// create materials

			//GPUProgrammingServices gpu = driver.GPUProgrammingServices;
			int newMaterialType1 = 0;
			int newMaterialType2 = 0;

			//if (gpu != null)
			{
				// create the shaders depending on if the user wanted high level or low level shaders

				if (useHighLevelShaders)
				{
					// ...
				}
				else
				{
					// ...
				}
			}

			// create test scene node 1, with the new created material type 1

			SceneNode node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0);
			node.SetMaterialTexture(0, driver.GetTexture("../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialType((MaterialType)newMaterialType1);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "PS & VS & EMT_SOLID", new Color(255, 255, 255), node);

			SceneNodeAnimator anim = smgr.CreateRotationAnimator(new Vector3Df(0, 0.3f, 0));
			node.AddAnimator(anim);
			anim.Drop();

			// create test scene node 2, with the new created material type 2

			node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0, -10, 50);
			node.SetMaterialTexture(0, driver.GetTexture("../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialType((MaterialType)newMaterialType2);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "PS & VS & EMT_TRANSPARENT", new Color(255, 255, 255), node);

			anim = smgr.CreateRotationAnimator(new Vector3Df(0, 0.3f, 0));
			node.AddAnimator(anim);
			anim.Drop();

			// create test scene node 3, with no shader

			node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0, 50, 25);
			node.SetMaterialTexture(0, driver.GetTexture("../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "NO SHADER", new Color(255, 255, 255), node);

			// add a nice skybox

			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, false);

			SceneNode skybox = smgr.AddSkyBoxSceneNode(
				"../media/irrlicht2_up.jpg",
				"../media/irrlicht2_dn.jpg",
				"../media/irrlicht2_lf.jpg",
				"../media/irrlicht2_rt.jpg",
				"../media/irrlicht2_ft.jpg",
				"../media/irrlicht2_bk.jpg");

			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, true);

			// add a camera and disable the mouse cursor

			CameraSceneNode cam = smgr.AddCameraSceneNodeFPS();
			cam.Position = new Vector3Df(-100, 50, 100);
			cam.Target = new Vector3Df(0);

			device.CursorControl.Visible = false;

			// draw everything

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
							"Vertex and pixel shader example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
		}

		static bool AskUserForHighLevelShaders()
		{
			Console.WriteLine("Please press 'y' if you want to use high level shaders.");
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
