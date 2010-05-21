using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _03.CustomSceneNode
{
	class Program
	{
		static void Main(string[] args)
		{
			IrrlichtDevice device =
				IrrlichtDevice.CreateDevice(DriverType.OpenGL, new Dimension2Du(640, 480), 16, false);

			device.WindowCaption = "Custom Scene Node - Irrlicht Engine Demo";

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			smgr.AddCameraSceneNode(null, new Vector3Df(0, -40, 0), new Vector3Df(0));

			CSampleSceneNode myNode = new CSampleSceneNode(smgr.RootSceneNode, smgr, 666);

			//scene::ISceneNodeAnimator* anim =
			//    smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

			//if(anim)
			//{
			//    myNode->addAnimator(anim);
			//    anim->drop();
			//    anim = 0;
			//}

			myNode.Drop();
			myNode = null;

			int frames = 0;
			while (device.Run())
			{
				driver.BeginScene(true, true, new Coloru(0, 100, 100, 100));
				smgr.DrawAll();
				driver.EndScene();

				if (++frames == 100)
				{
					device.WindowCaption = String.Format(
						"Irrlicht Engine [{0}] FPS: {1}",
						driver.Name, driver.FPS);

					frames = 0;
				}
			}

			device.Drop();
		}
	}

	class CSampleSceneNode : SceneNode
	{
		AABBox3Df Box = new AABBox3Df();
		List<Vertex3D> Vertices = new List<Vertex3D>();
		Material Material = new Material();

		public CSampleSceneNode(SceneNode parent, SceneManager smgr, int id)
			: base(parent, smgr, id, new Vector3Df(), new Vector3Df(), new Vector3Df())
		{
			this.OnRender += new RenderEventHandler(CSampleSceneNode_OnRender);

			Material.Wireframe = false;
			Material.Lighting = false;

			Vertices.Add(new Vertex3D(0, 0, 10, 1, 1, 0, new Coloru(255, 0, 255, 255), 0, 1));
			Vertices.Add(new Vertex3D(10, 0, -10, 1, 0, 0, new Coloru(255, 255, 0, 255), 1, 1));
			Vertices.Add(new Vertex3D(0, 20, 0, 0, 1, 1, new Coloru(255, 255, 255, 0), 1, 0));
			Vertices.Add(new Vertex3D(-10, 0, -10, 0, 0, 1, new Coloru(255, 0, 255, 0), 0, 0));

			Box.Reset(Vertices[0].Position);
			for (int i = 1; i < Vertices.Count; i++)
				Box.AddInternalPoint(Vertices[i].Position);
		}

		void CSampleSceneNode_OnRender()
		{
			Console.WriteLine(">>> Hello from CSampleSceneNode_OnRender()!");

			//u16 indices[] = {       0,2,3, 2,1,3, 1,0,3, 2,0,1      };
			//video::IVideoDriver* driver = SceneManager->getVideoDriver();

			//driver->setMaterial(Material);
			//driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
			//driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
		}
	}
}
