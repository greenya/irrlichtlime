using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L18.LightningShots
{
	class Program
	{
		static IrrlichtDevice device;
		static LightningShot lightningShot;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.OpenGL, new Dimension2Di(1024, 600));
			device.SetWindowCaption("LightningShots - Irrlicht Engine");
			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			device.FileSystem.AddFileArchive("../../media/map-20kdm2.pk3");

			AnimatedMesh mesh = smgr.GetMesh("20kdm2.bsp");
			MeshSceneNode node = smgr.AddMeshSceneNode(mesh.GetMesh(0));
			node.Position = new Vector3Df(-1300, -144, -1249);
			
			node.SetMaterialType(MaterialType.LightMapLightingM4);
			node.SetMaterialFlag(MaterialFlag.Lighting, true);

			node.TriangleSelector = smgr.CreateTriangleSelector(node.Mesh, node);
			node.TriangleSelector.Drop();

			smgr.AmbientLight = new Colorf(0.15f, 0.14f, 0.13f);

			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS();

			lightningShot = new LightningShot(smgr, node.TriangleSelector);
			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
			device.CursorControl.Visible = false;

			while (device.Run())
			{
				driver.BeginScene(true, true, new Color(100, 80, 75));

				smgr.DrawAll();

				lightningShot.Draw(device.Timer.Time);

				GUIFont f = device.GUIEnvironment.BuiltInFont;
				f.Draw("Use [LMB] to shoot", 10, 10, Color.OpaqueYellow);
				f.Draw("Total lightnings: " + lightningShot.TotalLightnings, 10, 20, Color.OpaqueWhite);
				f.Draw("Total shots: " + lightningShot.TotalShots, 10, 30, Color.OpaqueWhite);
				f.Draw(driver.FPS + " fps", 10, 40, Color.OpaqueWhite);

				driver.EndScene();
			}

			lightningShot.Drop();
			device.Drop();
		}

		static bool mouseCanShoot = true;
		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Mouse)
			{
				if (evnt.Mouse.IsLeftPressed())
				{
					if (!mouseCanShoot)
						return true;

					Vector3Df p = device.SceneManager.ActiveCamera.Position;
					Vector3Df d = (device.SceneManager.ActiveCamera.Target - p).Normalize();
					lightningShot.Fire(p + d * 20, d, device.Timer.Time);

					mouseCanShoot = false;
					return true;
				}
				else
				{
					mouseCanShoot = true;
				}
			}

			return false;
		}
	}
}
