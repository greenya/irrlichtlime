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
				IrrlichtDevice.CreateDevice(DriverType.OpenGL, new Dimension2Di(640, 480), 16, false);

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			smgr.AddCameraSceneNode(null, new Vector3Df(0, -40, 0), new Vector3Df(0));

			CSampleSceneNode myNode = new CSampleSceneNode(smgr.RootNode, smgr, 667);

			SceneNodeAnimator anim = smgr.CreateRotationAnimator(new Vector3Df(0.8f, 0, 0.8f));

			if (anim != null)
			{
				myNode.AddAnimator(anim);
				anim.Drop();
				anim = null;
			}

			myNode.Drop();
			myNode = null;

			int frames = 0;
			while (device.Run())
			{
				driver.BeginScene(true, true, new Color(100, 100, 100));
				smgr.DrawAll();
				driver.EndScene();

				if (++frames == 100)
				{
					device.SetWindowCaption(String.Format(
						"Custom Scene Node - Irrlicht Engine [{0}] fps: {1}",
						driver.Name, driver.FPS));

					frames = 0;
				}
			}

			device.Drop();
		}
	}

	class CSampleSceneNode : SceneNode
	{
		AABBox bbox = new AABBox();
		List<Vertex3D> vertices = new List<Vertex3D>();
		Material material = new Material();

		public CSampleSceneNode(SceneNode parent, SceneManager smgr, int id)
			: base(parent, smgr, id)
		{
			this.OnRegisterSceneNode += new RegisterSceneNodeEventHandler(CSampleSceneNode_OnRegisterSceneNode);
			this.OnRender += new RenderEventHandler(CSampleSceneNode_OnRender);
			this.OnGetBoundingBox += new GetBoundingBoxEventHandler(CSampleSceneNode_OnGetBoundingBox);
			this.OnGetMaterialCount += new GetMaterialCountEventHandler(CSampleSceneNode_OnGetMaterialCount);
			this.OnGetMaterial += new GetMaterialEventHandler(CSampleSceneNode_OnGetMaterial);

			material.Wireframe = false;
			material.Lighting = false;

			vertices.Add(new Vertex3D(0, 0, 10, 1, 1, 0, new Color(0, 255, 255), 0, 1));
			vertices.Add(new Vertex3D(10, 0, -10, 1, 0, 0, new Color(255, 0, 255), 1, 1));
			vertices.Add(new Vertex3D(0, 20, 0, 0, 1, 1, new Color(255, 255, 0), 1, 0));
			vertices.Add(new Vertex3D(-10, 0, -10, 0, 0, 1, new Color(0, 255, 0), 0, 0));

			bbox.Set(vertices[0].Position);
			for (int i = 1; i < vertices.Count; i++)
				bbox.AddInternalPoint(vertices[i].Position);
		}

		void CSampleSceneNode_OnRegisterSceneNode()
		{
			if (Visible)
				SceneManager.RegisterNodeForRendering(this);
		}

		void CSampleSceneNode_OnRender()
		{
			List<ushort> indices = new List<ushort>() { 0, 2, 3, 2, 1, 3, 1, 0, 3, 2, 0, 1 };
			VideoDriver driver = SceneManager.VideoDriver;

			driver.SetMaterial(material);
			driver.SetTransform(TransformationState.World, AbsoluteTransformation);
			driver.DrawVertexPrimitiveList(vertices, indices);
		}

		AABBox CSampleSceneNode_OnGetBoundingBox()
		{
			return bbox;
		}

		int CSampleSceneNode_OnGetMaterialCount()
		{
			return 1;
		}

		Material CSampleSceneNode_OnGetMaterial(int index)
		{
			return material;
		}
	}
}
