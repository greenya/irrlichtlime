﻿using System;
using System.Collections.Generic;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _15.LoadIrrFile
{
	class Program
	{
		static void Main(string[] args)
		{
			DriverType? driverType = AskForDriver();
			if (!driverType.HasValue)
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType.Value, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			// load the scene
			if (args.Length > 0)
				smgr.LoadScene(args[0]);
			else
				smgr.LoadScene("../../media/example.irr");

			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS(null, 50, 0.1f);

			// create a meta triangle selector to hold several triangle selectors
			MetaTriangleSelector meta = smgr.CreateMetaTriangleSelector();

			List<SceneNode> nodes = smgr.GetSceneNodesFromType(SceneNodeType.Any); // find all nodes
			foreach (SceneNode n in nodes)
			{
				TriangleSelector selector = null;

				switch (n.Type)
				{
					case SceneNodeType.Cube:
					case SceneNodeType.AnimatedMesh:
						// because the selector won't animate with the mesh,
						// and is only being used for camera collision, we'll just use an approximate
						// bounding box instead of "(node as AnimatedMeshSceneNode).GetMesh(0)"
						selector = smgr.CreateTriangleSelectorFromBoundingBox(n);
						break;

					case SceneNodeType.Mesh:
					case SceneNodeType.Sphere:
						// derived from MeshSceneNode
						selector = smgr.CreateTriangleSelector((n as MeshSceneNode).Mesh, n);
						break;

					case SceneNodeType.Terrain:
						selector = smgr.CreateTerrainTriangleSelector(n as TerrainSceneNode);
						break;

					case SceneNodeType.Octree:
						selector = smgr.CreateOctreeTriangleSelector((n as MeshSceneNode).Mesh, n);
						break;
				}

				if (selector != null)
				{
					// add it to the meta selector, which will take a reference to it
					meta.AddTriangleSelector(selector);
					// and drop my reference to it, so that the meta selector owns it
					selector.Drop();
				}
			}

			SceneNodeAnimator anim = smgr.CreateCollisionResponseAnimator(meta, camera, new Vector3Df(5), new Vector3Df(0));
			meta.Drop(); // i'm done with the meta selector now

			camera.AddAnimator(anim);
			anim.Drop(); // i'm done with the animator now

			// and set the camera position so that it doesn't start off stuck in the geometry
			camera.Position = new Vector3Df(0, 20, 0);

			// point the camera at the cube node, by finding the first node of type SceneNodeType.Cube
			SceneNode cube = smgr.GetSceneNodeFromType(SceneNodeType.Cube);
			if (cube != null)
				camera.Target = cube.AbsolutePosition;

			int lastFPS = -1;

			while (device.Run())
			{
				if (device.WindowActive)
				{
					driver.BeginScene(ClearBufferFlag.All, new Color(200, 200, 200));
					smgr.DrawAll();
					driver.EndScene();

					int fps = driver.FPS;
					if (lastFPS != fps)
					{
						device.SetWindowCaption(String.Format(
							"Load Irrlicht File example - Irrlicht Engine [{0}] fps: {1}",
							driver.Name, fps));

						lastFPS = fps;
					}
				}
			}

			device.Drop();
		}

		static DriverType? AskForDriver()
		{
			Console.Write("Please select the driver you want for this example:\n" +
				" (a) OpenGL\n" +
				" (b) Direct3D 9.0c\n" +
				" (c) Burning's Software Renderer\n" +
				" (d) Software Renderer\n" +
				" (e) NullDevice\n" +
				" (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: return DriverType.OpenGL;
				case ConsoleKey.B: return DriverType.Direct3D9;
				case ConsoleKey.C: return DriverType.BurningsVideo;
				case ConsoleKey.D: return DriverType.Software;
				case ConsoleKey.E: return DriverType.Null;
				default: return null;
			}
		}
	}
}
