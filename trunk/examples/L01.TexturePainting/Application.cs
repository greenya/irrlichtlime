using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L01.TexturePainting
{
	class Application
	{
		public Application(IrrlichtDevice dev)
		{
			device = dev;
			device.OnEvent += new IrrlichtDevice.EventHandler(OnEvent);

			initScene();
			initGUI(128);
			createTexture(128);
		}

		public void Render()
		{
			VideoDriver drv = device.VideoDriver;

			drv.SetRenderTarget(textureRTT, true, true, new Color(20, 80, 180));
			sceneNodeRTT.Visible = false;
			device.SceneManager.DrawAll();
			device.GUIEnvironment.DrawAll();

			drv.SetRenderTarget(RenderTarget.FrameBuffer, true, true, new Color(40, 180, 240));
			sceneNodeRTT.Visible = true;
			device.SceneManager.DrawAll();
			device.GUIEnvironment.DrawAll();
		}

		private void initScene()
		{
			SceneManager smgr = device.SceneManager;

			AnimatedMesh m = smgr.AddHillPlaneMesh(null, new Dimension2Df(16), new Dimension2Di(16), null, 8);

			sceneNodePainter = smgr.AddAnimatedMeshSceneNode(m);
			sceneNodePainter.Scale = new Vector3Df(0.4f);
			sceneNodePainter.SetMaterialTexture(0, texture);
			sceneNodePainter.SetMaterialFlag(MaterialFlag.Lighting, false);
			SceneNodeAnimator a = smgr.CreateRotationAnimator(new Vector3Df(0, 0.1f, 0));
			sceneNodePainter.AddAnimator(a);
			a.Drop();

			sceneNodeRTT = smgr.AddWaterSurfaceSceneNode(m.GetMesh(0), 2, 100, 20);
			sceneNodeRTT.SetMaterialFlag(MaterialFlag.Lighting, false);
			sceneNodeRTT.SetMaterialType(MaterialType.Solid);
			sceneNodeRTT.Scale = new Vector3Df(0.2f);
			sceneNodeRTT.Position = new Vector3Df(60, 10, 40);
			sceneNodeRTT.Rotation = new Vector3Df(-30, 20, 0);

			textureRTT = smgr.VideoDriver.AddRenderTargetTexture(new Dimension2Di(512));
			sceneNodeRTT.SetMaterialTexture(0, textureRTT);

			smgr.AddCameraSceneNode(null, new Vector3Df(0, 40, -60), new Vector3Df(0, -15, 0));
		}

		private void initGUI(int size)
		{
			GUIEnvironment gui = device.GUIEnvironment;
			VideoDriver drv = gui.VideoDriver;

			gui.Clear();

			gui.AddImage(
				drv.GetTexture("../media/lime_logo_alpha.png"),
				new Vector2Di(30, 0));

			guiWindow = gui.AddWindow(new Recti(20, 120, size + 20 + 20, size + 120 + 20 + 20 + 30), false, "Paint");

			guiSize128 = gui.AddButton(new Recti(10, 30, 40, 30 + 20), guiWindow, -1, "128");
			guiSize256 = gui.AddButton(new Recti(50, 30, 80, 30 + 20), guiWindow, -1, "256");
			guiSize512 = gui.AddButton(new Recti(90, 30, 120, 30 + 20), guiWindow, -1, "512");

			guiImage = gui.AddImage(new Recti(10, 30 + 30, size + 10 - 1, size + 30 - 1 + 30), guiWindow);
			gui.Focus = guiImage;
		}

		private void createTexture(int size)
		{
			VideoDriver drv = device.VideoDriver;

			Texture o = texture;

			texture = drv.AddTexture(new Dimension2Di(size), "tex");
			guiImage.SetImage(texture);
			sceneNodePainter.SetMaterialTexture(0, texture);

			if (o != null)
				drv.RemoveTexture(o);
		}

		bool OnEvent(Event e)
		{
			if (e.Type == EventType.Mouse)
			{
				int x = e.Mouse.X;
				int y = e.Mouse.Y;
				bool l = e.Mouse.IsLeftPressed();

				if (l && guiImage.AbsolutePosition.IsPointInside(new Vector2Di(x, y)))
				{
					Vector2Di p = new Vector2Di(x, y) - guiImage.AbsolutePosition.UpperLeftCorner;

					if (e.Mouse.Type == MouseEventType.Move)
					{
						TexturePainter t = texture.GetTexturePainter();

						if (p.X < texture.Size.Width &&
							p.Y < texture.Size.Height &&
							t.Lock(TextureLockMode.WriteOnly))
						{
							t.SetLine(oldMouseX, oldMouseY, p.X, p.Y, new Color(255, 0, 0));
							t.Unlock(true);
						}
					}

					oldMouseX = p.X;
					oldMouseY = p.Y;

					return true;
				}
			}

			if (e.Type == EventType.GUI)
			{
				if (e.GUI.Type == GUIEventType.ElementClosed &&
					e.GUI.Caller is GUIWindow)
				{
					device.Close();
					return true;
				}

				if (e.GUI.Type == GUIEventType.ButtonClicked)
				{
					if (e.GUI.Caller == guiSize128)
					{
						initGUI(128);
						createTexture(128);
						return true;
					}

					if (e.GUI.Caller == guiSize256)
					{
						initGUI(256);
						createTexture(256);
						return true;
					}

					if (e.GUI.Caller == guiSize512)
					{
						initGUI(512);
						createTexture(512);
						return true;
					}
				}
			}

			return false;
		}

		IrrlichtDevice device;

		Texture texture;
		SceneNode sceneNodePainter;

		Texture textureRTT;
		SceneNode sceneNodeRTT;

		GUIWindow guiWindow;
		GUIImage guiImage;
		GUIButton guiSize128;
		GUIButton guiSize256;
		GUIButton guiSize512;

		int oldMouseX = 0;
		int oldMouseY = 0;
	}
}
