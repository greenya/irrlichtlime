using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Video;
using IrrlichtLime.Core;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L12.StencilShadows
{
	class Program
	{
		static IrrlichtDevice device;
		static Shadows shadows;

		static CameraSceneNode cameraNode;
		static SceneNode quakeLevelNode;
		static AnimatedMeshSceneNode faerieNode;

		static SceneNode lightMovementHelperNode;
		static SceneNode lightNode;
		static SceneNode flashlightNode;

		static bool useLightBinding = true;
		static bool useShadowsRendering = true;
		static bool useShadowsRebuilding = true;
		static bool useShadowsQuakeLevel = false;
		static bool useFlashlight = false;

		static void Main(string[] args)
		{
			// setup Irrlicht

			device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1024, 768), 32, false, true);
			if (device == null)
				return;

			device.SetWindowCaption("Stencil Shadows - Irrlicht Engine");
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			GUIFont statsFont = device.GUIEnvironment.GetFont("../../media/fontlucida.png");
			Material statsMaterial = Material.IdentityNoLighting;

			cameraNode = scene.AddCameraSceneNodeFPS();
			cameraNode.FarValue = 20000;

			device.CursorControl.Visible = false;

			// setup shadows

			shadows = new Shadows(new Color(0xa0000000), 4000);

			// load quake level

			device.FileSystem.AddFileArchive("../../media/map-20kdm2.pk3");

			Mesh m = scene.GetMesh("20kdm2.bsp").GetMesh(0);
			MeshSceneNode n = scene.AddOctreeSceneNode(m, null, -1, 1024);
			n.Position = new Vector3Df(-1300, -144, -1249);
			quakeLevelNode = n;

			// add faerie

			faerieNode = scene.AddAnimatedMeshSceneNode(
				scene.GetMesh("../../media/faerie.md2"),
				null, -1,
				new Vector3Df(100, -40, 80),
				new Vector3Df(0, 30, 0),
				new Vector3Df(1.6f));

			faerieNode.SetMD2Animation(AnimationTypeMD2.Wave);
			faerieNode.AnimationSpeed = 20;
			faerieNode.GetMaterial(0).SetTexture(0, driver.GetTexture("../../media/faerie2.bmp"));
			faerieNode.GetMaterial(0).Lighting = false;
			faerieNode.GetMaterial(0).NormalizeNormals = true;

			shadows.AddObject(faerieNode);

			// add light

			lightMovementHelperNode = scene.AddEmptySceneNode();

			n = scene.AddSphereSceneNode(2, 6, lightMovementHelperNode, -1, new Vector3Df(15, -10, 15));
			n.SetMaterialFlag(MaterialFlag.Lighting, false);

			lightNode = n;
			shadows.AddLight(lightNode);

			// add flashlight

			m = scene.GetMesh("../../media/flashlight.obj");
			n = scene.AddMeshSceneNode(m, lightNode, -1, new Vector3Df(0), new Vector3Df(0), new Vector3Df(5));
			n.SetMaterialFlag(MaterialFlag.Lighting, false);

			flashlightNode = n;
			flashlightNode.Visible = false;

			// render

			uint shdFrameTime = 0;
			uint shdFrames = 0;
			uint shdFps = 0;

			while (device.Run())
			{
				if (useShadowsRebuilding &&
					shadows.BuildShadowVolume())
					shdFrames++;

				uint t = device.Timer.Time;
				if (t - shdFrameTime > 1000)
				{
					shdFrameTime = t;
					shdFps = shdFrames;
					shdFrames = 0;
				}

				if (useLightBinding)
				{
					lightMovementHelperNode.Position = cameraNode.AbsolutePosition.GetInterpolated(lightMovementHelperNode.Position, 0.1);
					lightMovementHelperNode.Rotation = cameraNode.AbsoluteTransformation.Rotation;
				}

				driver.BeginScene(true, true, new Color(0xff112244));

				scene.DrawAll();

				if (useShadowsRendering)
					shadows.DrawShadowVolume(driver);

				// display stats

				device.VideoDriver.SetMaterial(statsMaterial);

				driver.Draw2DRectangle(new Recti(10, 10, 150, 220), new Color(0x7f000000));

				Vector2Di v = new Vector2Di(20, 20);
				statsFont.Draw("Rendering", v, Color.OpaqueYellow);
				v.Y += 16;
				statsFont.Draw(driver.FPS + " fps", v, Color.OpaqueWhite);
				v.Y += 16;
				statsFont.Draw("[S]hadows " + (useShadowsRendering ? "ON" : "OFF"), v, Color.OpaqueGreen);
				v.Y += 16;
				statsFont.Draw("[L]ight binding " + (useLightBinding ? "ON" : "OFF"), v, Color.OpaqueGreen);
				v.Y += 16;
				statsFont.Draw("[F]lashlight " + (useFlashlight ? "ON" : "OFF"), v, Color.OpaqueGreen);
				v.Y += 32;
				statsFont.Draw("Shadows", v, Color.OpaqueYellow);
				v.Y += 16;
				statsFont.Draw(shdFps + " fps", v, Color.OpaqueWhite);
				v.Y += 16;
				statsFont.Draw(shadows.VerticesBuilt + " vertices", v, Color.OpaqueWhite);
				v.Y += 16;
				statsFont.Draw("[R]ebuilding " + (useShadowsRebuilding ? "ON" : "OFF"), v, Color.OpaqueGreen);
				v.Y += 16;
				statsFont.Draw("[Q]uake level " + (useShadowsQuakeLevel ? "ON" : "OFF"), v, Color.OpaqueGreen);

				driver.EndScene();
			}

			shadows.Drop();
			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Key &&
				evnt.Key.PressedDown)
			{
				switch (evnt.Key.Key)
				{
					case KeyCode.KeyL:
						useLightBinding = !useLightBinding;
						return true;

					case KeyCode.KeyS:
						useShadowsRendering = !useShadowsRendering;
						return true;

					case KeyCode.KeyR:
						useShadowsRebuilding = !useShadowsRebuilding;
						return true;

					case KeyCode.KeyQ:
						useShadowsQuakeLevel = !useShadowsQuakeLevel;

						if (useShadowsQuakeLevel)
							shadows.AddObject(quakeLevelNode);
						else
							shadows.RemoveObject(quakeLevelNode);

						return true;

					case KeyCode.KeyF:
						useFlashlight = !useFlashlight;

						if (useFlashlight)
							shadows.AddObject(flashlightNode);
						else
							shadows.RemoveObject(flashlightNode);

						flashlightNode.Visible = useFlashlight;

						return true;
				}
			}

			return false;
		}
	}
}
