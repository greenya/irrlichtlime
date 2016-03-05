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

		static bool shaderFirstUpdate = true;
		static int shaderInvWorldId;
		static int shaderWorldViewProjId;
		static int shaderLightPosId;
		static int shaderLightColorId;
		static int shaderTransWorldId;
		static int shaderTextureId;

		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			useHighLevelShaders = AskUserForHighLevelShaders(driverType);

			device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			string vsFileName = null; // filename for the vertex shader
			string psFileName = null; // filename for the pixel shader

			switch (driverType)
			{
				case DriverType.Direct3D9:
					if (useHighLevelShaders)
					{
						// Cg can also handle this syntax
						psFileName = "../../media/d3d9.hlsl";
						vsFileName = psFileName; // both shaders are in the same file
					}
					else
					{
						psFileName = "../../media/d3d9.psh";
						vsFileName = "../../media/d3d9.vsh";
					}
					break;

				case DriverType.OpenGL:
					if (useHighLevelShaders)
					{
						psFileName = "../../media/opengl.frag";
						vsFileName = "../../media/opengl.vert";
					}
					else
					{
						psFileName = "../../media/opengl.psh";
						vsFileName = "../../media/opengl.vsh";
					}
					break;
			}

			if (!driver.QueryFeature(VideoDriverFeature.PixelShader_1_1) &&
				!driver.QueryFeature(VideoDriverFeature.ARB_FragmentProgram_1))
				device.Logger.Log("WARNING: Pixel shaders disabled because of missing driver/hardware support.");

			if (!driver.QueryFeature(VideoDriverFeature.VertexShader_1_1) &&
				!driver.QueryFeature(VideoDriverFeature.ARB_VertexProgram_1))
				device.Logger.Log("WARNING: Vertex shaders disabled because of missing driver/hardware support.");

			// create materials
			
			GPUProgrammingServices gpu = driver.GPUProgrammingServices;
			MaterialType newMaterialType1 = MaterialType.Solid;
			MaterialType newMaterialType2 = MaterialType.TransparentAddColor;

			ShaderCallBack shaderCallback1 = null;
			ShaderCallBack shaderCallback2 = null;

			if (gpu != null && psFileName != null && vsFileName != null)
			{
				// create the shaders depending on if the user wanted high level or low level shaders

				if (useHighLevelShaders)
				{
					GPUShadingLanguage shadingLanguage = GPUShadingLanguage.Default;

					shaderCallback1 = gpu.AddHighLevelShaderMaterialFromFiles(
						vsFileName, "vertexMain", VertexShaderType.VS_1_1,
						psFileName, "pixelMain", PixelShaderType.PS_1_1,
						MaterialType.Solid, 0, shadingLanguage);

					shaderCallback2 = gpu.AddHighLevelShaderMaterialFromFiles(
						vsFileName, "vertexMain", VertexShaderType.VS_1_1,
						psFileName, "pixelMain", PixelShaderType.PS_1_1,
						MaterialType.TransparentAddColor, 0, shadingLanguage);
				}
				else
				{
					// create material from low level shaders (asm or arb_asm)

					shaderCallback1 = gpu.AddShaderMaterialFromFiles(vsFileName,
						psFileName, MaterialType.Solid);

					shaderCallback2 = gpu.AddShaderMaterialFromFiles(vsFileName,
						psFileName, MaterialType.TransparentAddColor);
				}
			}

			if (shaderCallback1 != null)	//if we got a shader callback (shader was created successfully)
			{
				shaderCallback1.OnSetConstants += gpu_OnSetConstants;	//add the event handler
				newMaterialType1 = shaderCallback1;	//assign the new material type. ShaderCallback implicitly converts to MaterialType.
			}

			if (shaderCallback2 != null)
			{
				shaderCallback2.OnSetConstants += gpu_OnSetConstants;
				newMaterialType2 = shaderCallback2;
			}



			// create test scene node 1, with the new created material type 1

			SceneNode node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0);
			node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialType(newMaterialType1);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "PS & VS & EMT_SOLID", new Color(255, 255, 255), node);

			SceneNodeAnimator anim = smgr.CreateRotationAnimator(new Vector3Df(0, 0.3f, 0));
			node.AddAnimator(anim);
			anim.Drop();

			// create test scene node 2, with the new created material type 2

			node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0, -10, 50);
			node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);
			node.SetMaterialFlag(MaterialFlag.BlendOperation, true);
			node.SetMaterialType(newMaterialType2);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "PS & VS & EMT_TRANSPARENT", new Color(255, 255, 255), node);

			anim = smgr.CreateRotationAnimator(new Vector3Df(0, 0.3f, 0));
			node.AddAnimator(anim);
			anim.Drop();

			// create test scene node 3, with no shader

			node = smgr.AddCubeSceneNode(50);
			node.Position = new Vector3Df(0, 50, 25);
			node.SetMaterialTexture(0, driver.GetTexture("../../media/wall.bmp"));
			node.SetMaterialFlag(MaterialFlag.Lighting, false);

			smgr.AddTextSceneNode(device.GUIEnvironment.BuiltInFont, "NO SHADER", new Color(255, 255, 255), node);

			// add a nice skybox

			driver.SetTextureCreationFlag(TextureCreationFlag.CreateMipMaps, false);

			SceneNode skybox = smgr.AddSkyBoxSceneNode(
				"../../media/irrlicht2_up.jpg",
				"../../media/irrlicht2_dn.jpg",
				"../../media/irrlicht2_lf.jpg",
				"../../media/irrlicht2_rt.jpg",
				"../../media/irrlicht2_ft.jpg",
				"../../media/irrlicht2_bk.jpg");

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
					driver.BeginScene(ClearBufferFlag.All, new Color(0));
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

		static void gpu_OnSetConstants(MaterialRendererServices services, int userData)
		{
			VideoDriver driver = services.VideoDriver;

			if (useHighLevelShaders && shaderFirstUpdate)
			{
				shaderWorldViewProjId = services.GetVertexShaderConstantID("mWorldViewProj");
				shaderTransWorldId = services.GetVertexShaderConstantID("mTransWorld");
				shaderInvWorldId = services.GetVertexShaderConstantID("mInvWorld");
				shaderLightPosId = services.GetVertexShaderConstantID("mLightPos");
				shaderLightColorId = services.GetVertexShaderConstantID("mLightColor");

				// textures id are important only for OpenGL interface
				if (driver.DriverType == DriverType.OpenGL)
					shaderTextureId = services.GetVertexShaderConstantID("myTexture");

				shaderFirstUpdate = false;
			}

			// set inverted world matrix
			// if we are using highlevel shaders (the user can select this when
			// starting the program), we must set the constants by name

			Matrix invWorld = driver.GetTransform(TransformationState.World);
			invWorld.MakeInverse();

			if (useHighLevelShaders)
				services.SetVertexShaderConstant(shaderInvWorldId, invWorld.ToArray(), true);
			else
				services.SetVertexShaderConstant(0, invWorld.ToArray());

			// set clip matrix

			Matrix worldViewProj = driver.GetTransform(TransformationState.Projection);
			worldViewProj *= driver.GetTransform(TransformationState.View);
			worldViewProj *= driver.GetTransform(TransformationState.World);

			if (useHighLevelShaders)
				services.SetVertexShaderConstant(shaderWorldViewProjId, worldViewProj.ToArray(), true);
			else
				services.SetVertexShaderConstant(4, worldViewProj.ToArray());

			// set camera position

			Vector3Df pos = device.SceneManager.ActiveCamera.AbsolutePosition;

			if (useHighLevelShaders)
				services.SetVertexShaderConstant(shaderLightPosId, pos.ToArray(), true);
			else
				services.SetVertexShaderConstant(8, pos.ToArray());

			// set light color

			Colorf col = new Colorf(0, 1, 1, 0);

			if (useHighLevelShaders)
				services.SetVertexShaderConstant(shaderLightColorId, col.ToArray(), true);
			else
				services.SetVertexShaderConstant(9, col.ToArray());

			// set transposed world matrix

			Matrix transpWorld = driver.GetTransform(TransformationState.World).Transposed;

			if (useHighLevelShaders)
			{
				services.SetVertexShaderConstant(shaderTransWorldId, transpWorld.ToArray(), true);
				if(driver.DriverType == DriverType.OpenGL)
                    services.SetPixelShaderConstant(shaderTextureId, new int[] { 0 }, true);
			}
			else
			{
				services.SetVertexShaderConstant(10, transpWorld.ToArray());
			}
		}

		static bool AskUserForHighLevelShaders(DriverType driverType)
		{
			if (driverType != DriverType.Direct3D9 &&
				driverType != DriverType.OpenGL)
				return false;

			Console.WriteLine("\nPlease press 'y' if you want to use high level shaders.");
			return Console.ReadKey().Key == ConsoleKey.Y;
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
