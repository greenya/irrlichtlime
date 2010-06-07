using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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

		static void Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Du(640, 480));
			if (device == null)
				return;

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			device.FileSystem.AddFileArchive("../media/map-20kdm2.pk3");

			AnimatedMesh q3levelmesh = smgr.GetMesh("20kdm2.bsp");
			MeshSceneNode q3node = null;

			// The Quake mesh is pickable, but doesn't get highlighted.
			if (q3levelmesh != null)
				q3node = smgr.AddOctreeSceneNode(q3levelmesh.GetMesh(0), null, IDFlag_IsPickable);

			//scene::ITriangleSelector* selector = 0;

			if (q3node != null)
			{
				q3node.Position = new Vector3Df(-1350, -130, -1400);
				//selector = smgr->createOctreeTriangleSelector(q3node->getMesh(), q3node, 128);
				//q3node->setTriangleSelector(selector);
				// We're not done with this selector yet, so don't drop it.
			}

			// Set a jump speed of 3 units per second, which gives a fairly realistic jump
			// when used with the gravity of (0, -10, 0) in the collision response animator.
			CameraSceneNode camera = smgr.AddCameraSceneNodeFPS(null, 100.0f, 0.3f, ID_IsNotPickable, null, true, 3.0f);
			camera.Rotation = new Vector3Df(50, 50, -60);
			//camera->setTarget(core::vector3df(-70,30,-60));

			//if (selector)
			//{
			//    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			//            selector, camera, core::vector3df(30,50,30),
			//            core::vector3df(0,-10,0), core::vector3df(0,30,0));
			//    selector->drop(); // As soon as we're done with the selector, drop it.
			//    camera->addAnimator(anim);
			//    anim->drop();  // And likewise, drop the animator when we're done referring to it.
			//}

			// Now I create three animated characters which we can pick, a dynamic light for
			// lighting them, and a billboard for drawing where we found an intersection.

			// First, let's get rid of the mouse cursor.  We'll use a billboard to show
			// what we're looking at.
			device.CursorControl.Visible = false;

			// Add the billboard.
			//scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
			//bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
			//bill->setMaterialTexture(0, driver->getTexture("../../media/particle.bmp"));
			//bill->setMaterialFlag(video::EMF_LIGHTING, false);
			//bill->setMaterialFlag(video::EMF_ZBUFFER, false);
			//bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
			//bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

			AnimatedMeshSceneNode node = null;

			// Add an MD2 node, which uses vertex-based animation.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../media/faerie.md2"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Position = new Vector3Df(-70, -15, -120); // Put its feet on the floor.
			node.Scale = new Vector3Df(2); // Make it appear realistically scaled
			node.SetMD2Animation(AnimationTypeMD2.Point);
			node.AnimationSpeed = 20.0f;
			node.GetMaterial(0).SetTexture(0, driver.GetTexture("../media/faerie2.bmp"));
			node.GetMaterial(0).Lighting = true;
			node.GetMaterial(0).NormalizeNormals = true;

			// Now create a triangle selector for it.  The selector will know that it
			// is associated with an animated node, and will update itself as necessary.
			//selector = smgr->createTriangleSelector(node);
			//node->setTriangleSelector(selector);
			//selector->drop(); // We're done with this selector, so drop it now.

			// This X files uses skeletal animation, but without skinning.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../media/dwarf.x"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Position = new Vector3Df(-70, -66, 0); // Put its feet on the floor.
			node.Rotation = new Vector3Df(0, -90, 0); // And turn it towards the camera.
			node.AnimationSpeed = 20.0f;
			//selector = smgr->createTriangleSelector(node);
			//node->setTriangleSelector(selector);
			//selector->drop();

			// And this B3D file uses skinned skeletal animation.
			node = smgr.AddAnimatedMeshSceneNode(smgr.GetMesh("../media/ninja.b3d"), null, IDFlag_IsPickable | IDFlag_IsHighlightable);
			node.Scale = new Vector3Df(10, 10, 10);
			node.Position = new Vector3Df(-70, -66, -60);
			node.Rotation = new Vector3Df(0, 90, 0);
			node.AnimationSpeed = 10.0f;
			node.GetMaterial(0).NormalizeNormals = true;
			// Just do the same as we did above.
			//selector = smgr->createTriangleSelector(node);
			//node->setTriangleSelector(selector);
			//selector->drop();

			// Add a light, so that the unselected nodes aren't completely dark.
			//scene::ILightSceneNode * light = smgr->addLightSceneNode(0, core::vector3df(-60,100,400), video::SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
			//light->setID(ID_IsNotPickable); // Make it an invalid target for selection.

			// Remember which scene node is highlighted
			SceneNode highlightedSceneNode = null;
			//scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
			int lastFPS = -1;

			// draw the selection triangle only as wireframe
			Material material = new Material();
			material.Lighting = false;
			material.Wireframe = true;

			while (device.Run())
			{
				if (!device.WindowActive)
					continue;

				driver.BeginScene(true, true, new Coloru(0));
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
				// ISceneCollisionManager::getRayFromScreenCoordinates()
				//core::line3d<f32> ray;
				//ray.start = camera->getPosition();
				//ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

				// Tracks the current intersection point with the level or a mesh
				Vector3Df intersection;
				// Used to show with triangle has been hit
				//core::triangle3df hitTriangle;

				// This call is all you need to perform ray/triangle collision on every scene node
				// that has a triangle selector, including the Quake level mesh.  It finds the nearest
				// collision point/triangle, and returns the scene node containing that point.
				// Irrlicht provides other types of selection, including ray/triangle selector,
				// ray/box and ellipse/triangle selector, plus associated helpers.
				// See the methods of ISceneCollisionManager
				//scene::ISceneNode* selectedSceneNode =
				//        collMan->getSceneNodeAndCollisionPointFromRay(
				//                        ray,
				//                        intersection, // This will be the position of the collision
				//                        hitTriangle, // This will be the triangle hit in the collision
				//                        IDFlag_IsPickable, // This ensures that only nodes that we have set up to be pickable are considered
				//                        0); // Check the entire scene (this is actually the implicit default)

				// If the ray hit anything, move the billboard to the collision position
				// and draw the triangle that was hit.
				//if (selectedSceneNode != null)
				//{
				//    //bill->setPosition(intersection);

				//    // We need to reset the transform before doing our own rendering.
				//    driver.SetTransform(TransformationState.World, new Matrix4f());
				//    driver.SetMaterial(material);
				//    //driver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));

				//    // We can check the flags for the scene node that was hit to see if it should be
				//    // highlighted. The animated nodes can be highlighted, but not the Quake level mesh
				//    //if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
				//    //{
				//    //    highlightedSceneNode = selectedSceneNode;

				//    //    // Highlighting in this case means turning lighting OFF for this node,
				//    //    // which means that it will be drawn with full brightness.
				//    //    highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
				//    //}
				//}

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
