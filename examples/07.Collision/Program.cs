﻿using System;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _07.Collision
{
	class Program
	{
		const int ID_IsNotPickable = 0;
		const int IDFlag_IsPickable = 1 << 0;
		const int IDFlag_IsHighlightable = 1 << 1;

		static void Main()
		{
			DriverType? driverType = AskForDriver();
			if (!driverType.HasValue)
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType.Value, new Dimension2Di(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			device.FileSystem.AddFileArchive("../../media/map-20kdm2.pk3");

			AnimatedMesh q3levelmesh = smgr.GetMesh("20kdm2.bsp");
			MeshSceneNode q3node = null;

			// The Quake mesh is pickable, but doesn't get highlighted.
			if (q3levelmesh != null)
				q3node = smgr.AddOctreeSceneNode(q3levelmesh.GetMesh(0), null, IDFlag_IsPickable);

			TriangleSelector selector = null;

			if (q3node != null)
			{
				q3node.Position = new Vector3Df(-1350, -130, -1400);
				selector = smgr.CreateOctreeTriangleSelector(q3node.Mesh, q3node, 128);
				q3node.TriangleSelector = selector;
				// We're not done with this selector yet, so don't drop it.
			}

			// Set a jump speed of 3 units per second, which gives a fairly realistic jump
			// when used with the gravity of (0, -1000, 0) in the collision response animator.
			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS(null, 100.0f, 0.3f, ID_IsNotPickable, null, true, 3.0f);
			camera.Position = new Vector3Df(50, 50, -60);
			camera.Target = new Vector3Df(-70, 30, -60);

			if (selector != null)
			{
				SceneNodeAnimator anim = smgr.CreateCollisionResponseAnimator(
					selector,
					camera,
					new Vector3Df(30, 50, 30),
					new Vector3Df(0, -1000, 0),
					new Vector3Df(0, 30, 0));

				selector.Drop(); // As soon as we're done with the selector, drop it.
				camera.AddAnimator(anim);
				anim.Drop(); // And likewise, drop the animator when we're done referring to it.
			}

			// Now I create three animated characters which we can pick, a dynamic light for
			// lighting them, and a billboard for drawing where we found an intersection.

			// First, let's get rid of the mouse cursor. We'll use a billboard to show what we're looking at.
			device.CursorControl.Visible = false;

			// Add the billboard.
			BillboardSceneNode bill = smgr.AddBillboardSceneNode();
			bill.SetMaterialType(MaterialType.TransparentAddColor);
			bill.SetMaterialTexture(0, driver.GetTexture("../../media/particle.bmp"));
			bill.SetMaterialFlag(MaterialFlag.Lighting, false);
			bill.SetMaterialFlag(MaterialFlag.ZBuffer, false);
			bill.SetSize(20, 20, 20);
			bill.ID = ID_IsNotPickable; // This ensures that we don't accidentally ray-pick it

			AnimatedMeshSceneNode node = null;

			// Add an MD2 node, which uses vertex-based animation.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/faerie.md2"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Position = new Vector3Df(-90, -15, -140); // Put its feet on the floor.
			node.Scale = new Vector3Df(1.6f); // Make it appear realistically scaled
			node.SetMD2Animation(AnimationTypeMD2.Point);
			node.AnimationSpeed = 20.0f;
			node.GetMaterial(0).SetTexture(0, driver.GetTexture("../../media/faerie2.bmp"));
			node.GetMaterial(0).Lighting = true;
			node.GetMaterial(0).NormalizeNormals = true;

			// Now create a triangle selector for it.  The selector will know that it
			// is associated with an animated node, and will update itself as necessary.
			selector = smgr.CreateTriangleSelector(node);
			node.TriangleSelector = selector;
			selector.Drop(); // We're done with this selector, so drop it now.

			// And this B3D file uses skinned skeletal animation.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/ninja.b3d"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Scale = new Vector3Df(10);
			node.Position = new Vector3Df(-75, -66, -80);
			node.Rotation = new Vector3Df(0, 90, 0);
			node.AnimationSpeed = 8.0f;
			node.GetMaterial(0).NormalizeNormals = true;
			// Just do the same as we did above.
			selector = smgr.CreateTriangleSelector(node);
			node.TriangleSelector = selector;
			selector.Drop();

			// This X files uses skeletal animation, but without skinning.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/dwarf.x"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Position = new Vector3Df(-70, -66, -30); // Put its feet on the floor.
			node.Rotation = new Vector3Df(0, -90, 0); // And turn it towards the camera.
			node.AnimationSpeed = 20.0f;
			selector = smgr.CreateTriangleSelector(node);
			node.TriangleSelector = selector;
			selector.Drop();

			// And this mdl file uses skinned skeletal animation.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../../media/yodan.mdl"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Position = new Vector3Df(-90, -25, 20);
			node.Scale = new Vector3Df(0.8f);
			node.GetMaterial(0).Lighting = true;
			node.AnimationSpeed = 20.0f;

			// Just do the same as we did above.
			selector = smgr.CreateTriangleSelector(node);
			node.TriangleSelector = selector;
			selector.Drop();

			// Add a light, so that the unselected nodes aren't completely dark.
			LightSceneNode light = smgr.AddLightSceneNode(null, new Vector3Df(-60, 100, 400), new Colorf(1.0f, 1.0f, 1.0f), 600.0f);
			light.ID = ID_IsNotPickable; // Make it an invalid target for selection.

			// Remember which scene node is highlighted
			SceneNode highlightedSceneNode = null;
			SceneCollisionManager collMan = smgr.SceneCollisionManager;
			int lastFPS = -1;

			// draw the selection triangle only as wireframe
			Material material = new Material();
			material.Lighting = false;
			material.Wireframe = true;

			while (device.Run())
			if (device.WindowActive)
			{
				driver.BeginScene(ClearBufferFlag.All, new Color(0));
				smgr.DrawAll();

				// Unlight any currently highlighted scene node
				if (highlightedSceneNode != null)
				{
					highlightedSceneNode.SetMaterialFlag(MaterialFlag.Lighting, true);
					highlightedSceneNode = null;
				}

				// All intersections in this example are done with a ray cast out from the camera to
				// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
				// trajectory or a sword's position, or create a ray from a mouse click position using
				// collMan.GetRayFromScreenCoordinates()
				Line3Df ray = new Line3Df();
				ray.Start = camera.Position;
				ray.End = ray.Start + (camera.Target - ray.Start).Normalize() * 1000.0f;

				// This call is all you need to perform ray/triangle collision on every scene node
				// that has a triangle selector, including the Quake level mesh.  It finds the nearest
				// collision point/triangle, and returns the scene node containing that point.
				// Irrlicht provides other types of selection, including ray/triangle selector,
				// ray/box and ellipse/triangle selector, plus associated helpers.
				// See the methods of ISceneCollisionManager
				SceneNode selectedSceneNode =
					collMan.GetSceneNodeAndCollisionPointFromRay(
						ray,
						out Vector3Df intersection, // This will be the position of the collision
						out Triangle3Df hitTriangle, // This will be the triangle hit in the collision
						IDFlag_IsPickable); // This ensures that only nodes that we have set up to be pickable are considered

				// If the ray hit anything, move the billboard to the collision position
				// and draw the triangle that was hit.
				if (selectedSceneNode != null)
				{
					bill.Position = intersection;

					// We need to reset the transform before doing our own rendering.
					driver.SetTransform(TransformationState.World, Matrix.Identity);
					driver.SetMaterial(material);
					driver.Draw3DTriangle(hitTriangle, new Color(255, 0, 0));

					// We can check the flags for the scene node that was hit to see if it should be
					// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
					if ((selectedSceneNode.ID & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
					{
						highlightedSceneNode = selectedSceneNode;

						// Highlighting in this case means turning lighting OFF for this node,
						// which means that it will be drawn with full brightness.
						highlightedSceneNode.SetMaterialFlag(MaterialFlag.Lighting, false);
					}
				}

				// We're all done drawing, so end the scene.
				driver.EndScene();

				int fps = driver.FPS;
				if (lastFPS != fps)
				{
					device.SetWindowCaption(String.Format(
						"Collision detection example - Irrlicht Engine [{0}] fps: {1}",
						driver.Name, fps));

					lastFPS = fps;
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
