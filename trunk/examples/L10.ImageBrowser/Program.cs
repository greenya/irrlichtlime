using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L10.ImageBrowser
{
	class Program
	{
		static IrrDevice irr;
		static TextureManager textureManager;
		static AnimationManager animationManager;

		static bool wantChangeFolder = false;
		static bool wantUpdateActiveCameraAspectRatio = false;
		static Dimension2Di PreviewTextureSize = new Dimension2Di(128);
		static float maxScrollPosition = 0;
		static int tasksAddedToTextureManager = 0;

		const int TextureManagerThreadCount = 4;
		const int PreviewPlateSize = 80;
		const int PreviewRootNodeId = 1001;
		const int ChooseFolderButtonId = 1002;
		const int CurrentFolderStaticTextId = 1003;
		const string PreviewPlateMeshName = "previewPlate";
		const int PreviewPlateNodeIdFlag = 1 << 17;
		const int SelectableNodeIdFlag = 1 << 18;

		static SceneNode hoveredNode;
		static SceneNode selectedNode;
		static Dictionary<int, string> previewPlateInfo = new Dictionary<int, string>();

		[STAThreadAttribute]
		static void Main(string[] args)
		{
			irr = new IrrDevice();
			irr.CreateDevice(DriverType.Direct3D9, new Dimension2Di(1024, 600));
			animationManager = new AnimationManager(irr);
			textureManager = new TextureManager(irr);
			textureManager.OnTextureLoaded += new TextureManager.TextureLoadedDelegate(textureManager_OnTextureLoaded);

			irr.Lock();

			irr.Device.SetWindowResizable(true);
			irr.Device.OnEvent += new IrrlichtDevice.EventHandler(Device_OnEvent);

			irr.Scene.AddCameraSceneNode();
			irr.Scene.AddEmptySceneNode(null, PreviewRootNodeId);
			irr.Scene.AddHillPlaneMesh(PreviewPlateMeshName, new Dimension2Df(PreviewPlateSize), new Dimension2Di(1));

			initUI();
			openFolder(Path.GetFullPath("../../media"));

			int lastFPS = -1;
			while (irr.Device.Run())
			{
				irr.Driver.BeginScene(true, true, new Color(0x112233));

				irr.Scene.DrawAll();

				if (selectedNode == null)
					irr.GUI.DrawAll();

				drawScrollPosition();
				drawTextureManagerActivity();
				drawPreviewPlateTooltip();

				irr.Driver.EndScene();

				int fps = irr.Driver.FPS;
				if (lastFPS != fps)
				{
					irr.Device.SetWindowCaption(String.Format(
						"Image Browser - Irrlicht Lime [{0}] fps: {1}",
						irr.Driver.Name, fps));

					lastFPS = fps;
				}

				irr.Unlock();

				animationManager.Run();

				if (wantChangeFolder)
				{
					wantChangeFolder = false;
					string p = irr.GUI.RootElement.GetElementFromID(CurrentFolderStaticTextId).Text;
					System.Windows.Forms.FolderBrowserDialog d = new System.Windows.Forms.FolderBrowserDialog();
					d.SelectedPath = p;
					if (d.ShowDialog() == System.Windows.Forms.DialogResult.OK &&
						d.SelectedPath != p)
					{
						openFolder(d.SelectedPath);
					}
				}

				if (wantUpdateActiveCameraAspectRatio)
				{
					wantUpdateActiveCameraAspectRatio = false;
					irr.Scene.ActiveCamera.AspectRatio = (float)irr.DriverNoCheck.ScreenSize.Width / irr.DriverNoCheck.ScreenSize.Height;
				}

				irr.Lock();
			}

			irr.Unlock();
			textureManager.Stop();
			animationManager.Clear();
			irr.Drop();
		}

		static void textureManager_OnTextureLoaded(SceneNode node, Texture texture, Dimension2Di sourceDimension)
		{
			if (texture.Size == PreviewTextureSize || texture.Name.Path == "NoPreviewTexture")
			{
				float a = (float)sourceDimension.Height / sourceDimension.Width;
				animationManager.Remove(node);
				animationManager.Add(node, 400, new Vector3Df(node.Position.X, 0, node.Position.Z), null, new Vector3Df(1, 1, a));

				if (texture.Name.Path != "NoPreviewTexture")
				{
					previewPlateInfo[node.ID] += "\n" + sourceDimension.ToString();
					node.ID |= SelectableNodeIdFlag;
				}
			}
		}

		static bool Device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.GUI &&
				evnt.GUI.Type == GUIEventType.ButtonClicked &&
				evnt.GUI.Caller.ID == ChooseFolderButtonId)
			{
				wantChangeFolder = true;
				return true;
			}

			if (evnt.Type == EventType.Mouse &&
				evnt.Mouse.Type == MouseEventType.Wheel &&
				selectedNode == null)
			{
				Vector3Df p = irr.Scene.ActiveCamera.Position;
				Vector3Df t = irr.Scene.ActiveCamera.Target;
				float s = irr.Scene.ActiveCamera.Position.Z + evnt.Mouse.Wheel * 16;

				if (s < 0)
					s = 0;

				if (s > maxScrollPosition)
					s = maxScrollPosition;

				t.Z = t.Z - p.Z + s;
				p.Z = s;

				irr.Scene.ActiveCamera.Position = p;
				irr.Scene.ActiveCamera.Target = t;

				return true;
			}

			if (evnt.Type == EventType.Mouse &&
				evnt.Mouse.Type == MouseEventType.Move &&
				selectedNode == null)
			{
				SceneNode n =
					irr.Scene.SceneCollisionManager.GetSceneNodeFromScreenCoordinatesBB(
					new Vector2Di(evnt.Mouse.X, evnt.Mouse.Y),
					0,
					irr.Scene.GetSceneNodeFromID(PreviewRootNodeId));

				if (hoveredNode != n)
				{
					if (hoveredNode != null)
					{
						animationManager.Remove(hoveredNode);

						animationManager.Add(
							hoveredNode,
							500,
							new Vector3Df(hoveredNode.Position.X, hoveredNode.Position.Y - 15, hoveredNode.Position.Z),
							new Vector3Df(0),
							hoveredNode.Scale / 1.5f);
					}

					if (n != null)
					{
						animationManager.Remove(n);

						animationManager.Add(
							n,
							40,
							new Vector3Df(n.Position.X, n.Position.Y + 15, n.Position.Z),
							new Vector3Df(-20, 0, 0),
							n.Scale * 1.5f);
					}

					hoveredNode = n;
				}

				return true;
			}

			if (evnt.Type == EventType.Mouse &&
				evnt.Mouse.Type == MouseEventType.LeftUp &&
				hoveredNode != null &&
				(hoveredNode.ID & SelectableNodeIdFlag) == SelectableNodeIdFlag &&
				selectedNode == null)
			{
				animationManager.Remove(hoveredNode);

				Mesh m = irr.Scene.MeshCache.GetMesh(PreviewPlateMeshName);
				MeshSceneNode n = irr.Scene.AddMeshSceneNode(m);
				n.SetMaterialFlag(MaterialFlag.Lighting, false);
				n.Position = hoveredNode.Position;
				n.Rotation = hoveredNode.Rotation;
				n.Scale = hoveredNode.Scale;

				string t = hoveredNode.GetMaterial(0).GetTexture(0).Name.Path.Split('|')[0];

				Dimension2Di d = new Dimension2Di(2048);
				if (d.Area > irr.Driver.MaxTextureSize.Area)
					d = irr.Driver.MaxTextureSize;

				n.SetMaterialTexture(0, hoveredNode.GetMaterial(0).GetTexture(0));
				textureManager.LoadTexture(n, t, d, true);

				animationManager.Add(
					n,
					200,
					irr.Scene.ActiveCamera.AbsolutePosition + new Vector3Df(0, -48, 40), // TODO: this magic numbers should be calculated somehow
					new Vector3Df(-39.85f, 0, 0), // using current active camera info (like view matrix or projection one)
					n.Scale * ((irr.Scene.ActiveCamera.FOV - 0.125f) / n.Scale.Z));

				selectedNode = n;
				hoveredNode.Visible = false;
				irr.GUI.RootElement.GetElementFromID(ChooseFolderButtonId).Enabled = false;

				return true;
			}

			if (evnt.Type == EventType.Mouse &&
				evnt.Mouse.Type == MouseEventType.LeftUp &&
				selectedNode != null)
			{
				if (animationManager.IsAnimated(selectedNode))
					return true;

				Texture t = selectedNode.GetMaterial(0).GetTexture(0);
				if (t != null)
				{
					string s = t.Name.Path;
					selectedNode.SetMaterialTexture(0, null);
					textureManager.UnloadTexture(s);
				}

				selectedNode.Remove();
				selectedNode = null;

				hoveredNode.Visible = true;
				irr.GUI.RootElement.GetElementFromID(ChooseFolderButtonId).Enabled = true;

				return true;
			}

			if (evnt.Type == EventType.Log &&
				evnt.Log.Text.StartsWith("Resizing window"))
			{
				wantUpdateActiveCameraAspectRatio = true;
			}

			return false;
		}

		static void initUI()
		{
			irr.GUI.Skin.SetFont(irr.GUI.GetFont("../../media/fontlucida.png"));

			irr.GUI.AddButton(new Recti(20, 10, 160, 40), null, ChooseFolderButtonId, "Choose folder...");

			GUIStaticText t = irr.GUI.AddStaticText("???", new Recti(180, 10, irr.Device.VideoDriver.ScreenSize.Width - 20, 40), false, false, null, CurrentFolderStaticTextId);
			t.SetTextAlignment(GUIAlignment.UpperLeft, GUIAlignment.Center);
			t.OverrideColor = Color.OpaqueWhite;
		}

		static void openFolder(string newFolder)
		{
			textureManager.Stop();
			textureManager.Start(TextureManagerThreadCount);
			textureManager.EnqueueUnloadingOfAllLoadedTextures();
			animationManager.Clear();
			previewPlateInfo.Clear();

			irr.GUI.RootElement.GetElementFromID(CurrentFolderStaticTextId).Text = newFolder;

			SceneNode p = irr.Scene.GetSceneNodeFromID(PreviewRootNodeId);
			p.RemoveChildren();

			int r = 10;
			float x = 0, z = 0;
			Mesh m = irr.Scene.MeshCache.GetMesh(PreviewPlateMeshName);
			string[] f = Directory.GetFiles(newFolder, "*.*", SearchOption.TopDirectoryOnly);
			for (int i = 0; i < f.Length; i++)
			{
				x += PreviewPlateSize * 1.1f;
				if ((i % r) == 0)
				{
					x = 0;
					z += PreviewPlateSize * 1.1f;
				}

				MeshSceneNode n = irr.Scene.AddMeshSceneNode(m, p, i | PreviewPlateNodeIdFlag);
				n.SetMaterialFlag(MaterialFlag.Lighting, false);
				n.Position = new Vector3Df(x, 1000, z);

				textureManager.LoadTexture(n, f[i], PreviewTextureSize);

				TriangleSelector s = irr.Scene.CreateTriangleSelector(n.Mesh, n);
				n.TriangleSelector = s;
				s.Drop();

				previewPlateInfo.Add(n.ID, Path.GetFileName(f[i]));
			}

			irr.Scene.ActiveCamera.Position = new Vector3Df(PreviewPlateSize * (r - 1) * 1.1f / 2, 6 * PreviewPlateSize, 0);
			irr.Scene.ActiveCamera.Target = new Vector3Df(irr.Scene.ActiveCamera.Position.X, 0, PreviewPlateSize * 5);
			maxScrollPosition = (f.Length / r) * PreviewPlateSize * 1.1f;

			tasksAddedToTextureManager = textureManager.GetCommandQueueLength();
		}

		static void drawScrollPosition()
		{
			if (selectedNode != null)
				return;

			if (maxScrollPosition < 1)
				return;

			VideoDriver v = irr.Driver;
			if (v.ScreenSize.Height < 200)
				return;

			float p = irr.Scene.ActiveCamera.Position.Z / maxScrollPosition;

			v.Draw2DLine(v.ScreenSize.Width - 26, 80, v.ScreenSize.Width - 26, v.ScreenSize.Height - 80, new Color(0x88446699));

			float y = (v.ScreenSize.Height - 80 - 80 - 40) * (1.0f - p);
			Recti r = new Recti(v.ScreenSize.Width - 30, (int)y + 80, v.ScreenSize.Width - 23, (int)y + 80 + 40);
			v.Draw2DRectangle(r, new Color(0x88446699));
		}

		static void drawTextureManagerActivity()
		{
			if (selectedNode != null)
				return;

			if (tasksAddedToTextureManager == 0)
				return;

			int l = textureManager.GetCommandQueueLength();
			if (l == 0)
			{
				tasksAddedToTextureManager = 0;
				return;
			}

			VideoDriver v = irr.Driver;
			float p = (tasksAddedToTextureManager - l) / (float)tasksAddedToTextureManager;
			if (p > 1)
				p = 1;

			Recti r = new Recti(v.ScreenSize.Width - 140, 20, v.ScreenSize.Width - 24, 30);
			v.Draw2DRectangleOutline(r, new Color(0x88446699));

			r.Inflate(-4, -4);
			r.LowerRightCorner = new Vector2Di(r.UpperLeftCorner.X + (int)(r.Width * p), r.LowerRightCorner.Y);
			v.Draw2DRectangle(r, new Color(0x88446699));
		}

		static void drawPreviewPlateTooltip()
		{
			if (hoveredNode == null ||
				!hoveredNode.Visible)
				return;

			int k = hoveredNode.ID;

			Texture t = hoveredNode.GetMaterial(0).GetTexture(0);
			if (t != null && t.Name.Path != "NoPreviewTexture")
				k = hoveredNode.ID & (0xFFFFFFF ^ SelectableNodeIdFlag);

			string s = previewPlateInfo.ContainsKey(k)
				? previewPlateInfo[k]
				: "???";

			if (s != null)
			{
				Vector2Di p = irr.Device.CursorControl.Position + new Vector2Di(16);
				GUIFont f = irr.GUI.Skin.GetFont(GUIDefaultFont.Default);

				Dimension2Di d = f.GetDimension(s);
				d.Inflate(16, 12);

				Recti r = new Recti(p, d);
				VideoDriver v = irr.Driver;

				int ax = r.LowerRightCorner.X - v.ScreenSize.Width;
				int ay = r.LowerRightCorner.Y - v.ScreenSize.Height;
				if (ax > 0 || ay > 0)
				{
					if (ax < 0) ax = 0;
					if (ay < 0) ay = 0;
					r.Offset(-ax, -ay);
				}

				v.Draw2DRectangle(r, new Color(0xbb223355));
				v.Draw2DRectangleOutline(r, new Color(0xbb445577));

				f.Draw(s, r.UpperLeftCorner + new Vector2Di(8, 6), Color.OpaqueYellow);
			}
		}
	}
}
