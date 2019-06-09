﻿using IrrlichtLime;
using IrrlichtLime.Scene;
using IrrlichtLime.Video;
using IrrlichtLime.Core;

namespace L03.RGBSwirl
{
	class Program
	{
		static void Main()
		{
			IrrlichtDevice device = IrrlichtDevice.CreateDevice(DriverType.Direct3D9, new Dimension2Di(800, 600));
			device.SetWindowCaption("RGB swirl example - Irrlicht Lime");

			VideoDriver driver = device.VideoDriver;
			SceneManager scene = device.SceneManager;

			var camera = scene.AddCameraSceneNode(null, new Vector3Df(0, 0, -15), new Vector3Df());
			camera.ViewMatrixAffector = camera.ProjectionMatrix.GetInverse();

			var lightRed = scene.AddLightSceneNode(null, new Vector3Df(0, 40, 0));
			lightRed.LightData.DiffuseColor = new Colorf(1, 0, 0);
			var a = scene.CreateFlyCircleAnimator(new Vector3Df(), 40, 0.0003f, new Vector3Df(0, 0, 1), 0.000f);
			lightRed.AddAnimator(a);
			a.Drop();

			var lightGreen = scene.AddLightSceneNode(null, new Vector3Df(-30, -20, 0));
			lightGreen.LightData.DiffuseColor = new Colorf(0, 1, 0);
			a = scene.CreateFlyCircleAnimator(new Vector3Df(), 40, 0.0003f, new Vector3Df(0, 0, 1), 0.333f);
			lightGreen.AddAnimator(a);
			a.Drop();

			var lightBlue = scene.AddLightSceneNode(null, new Vector3Df(30, -20, 0));
			lightBlue.LightData.DiffuseColor = new Colorf(0, 0, 1);
			a = scene.CreateFlyCircleAnimator(new Vector3Df(), 40, 0.0003f, new Vector3Df(0, 0, 1), 0.667f);
			lightBlue.AddAnimator(a);
			a.Drop();

			var node = scene.AddSphereSceneNode(5.5f, 255);
			node.SetMaterialFlag(MaterialFlag.BackFaceCulling, false);
			node.SetMaterialFlag(MaterialFlag.PointCloud, true);
			node.GetMaterial(0).Thickness = 4;

			while (device.Run())
			{
				node.Rotation = new Vector3Df(device.Timer.Time / 1, device.Timer.Time / 2, device.Timer.Time / 3);

				driver.BeginScene(ClearBufferFlag.Depth);
				scene.DrawAll();
				driver.EndScene();
			}

			device.Drop();
		}
	}
}
