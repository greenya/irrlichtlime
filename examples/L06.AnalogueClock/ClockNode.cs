using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L06.AnalogueClock
{
	class ClockNode : SceneNode
	{
		public static ClockNode AddClockNode(SceneNode parent)
		{
			ClockNode n = new ClockNode(parent, parent.SceneManager);
			n.Drop();

			return n;
		}

		AABBox boundingBox;
		List<Material> materialList = new List<Material>();

		private MeshSceneNode arrowSeconds;
		private MeshSceneNode arrowMinutes;
		private MeshSceneNode arrowHours;

		ClockNode(SceneNode parent, SceneManager smgr)
			: base(parent, smgr)
		{
			OnGetBoundingBox += new GetBoundingBoxEventHandler(ClockNode_OnGetBoundingBox);
			OnGetMaterialCount += new GetMaterialCountEventHandler(ClockNode_OnGetMaterialCount);
			OnGetMaterial += new GetMaterialEventHandler(ClockNode_OnGetMaterial);
			OnRegisterSceneNode += new RegisterSceneNodeEventHandler(ClockNode_OnRegisterSceneNode);
			OnRender += new RenderEventHandler(ClockNode_OnRender);

			// add clock face

			Mesh mesh = SceneManager.GeometryCreator.CreateCylinderMesh(100, 32, 6, new Color(180, 180, 180));
			MeshSceneNode clockFace = SceneManager.AddMeshSceneNode(mesh, this);
			clockFace.Rotation = new Vector3Df(90, 0, 0);
			clockFace.Position = new Vector3Df(0, 0, 10);
			mesh.Drop();

			clockFace.UpdateAbsolutePosition();
			boundingBox = clockFace.BoundingBoxTransformed;
			for (int i = 0; i < clockFace.MaterialCount; i++) materialList.Add(clockFace.GetMaterial(i));
			
			// add clock center

			mesh = SceneManager.GeometryCreator.CreateCylinderMesh(10, 24, 16, new Color(255, 255, 255), false);
			MeshSceneNode clockCenter = SceneManager.AddMeshSceneNode(mesh, this);
			clockCenter.Rotation = new Vector3Df(90, 0, 0);
			clockCenter.Position = new Vector3Df(0, 0, -14);
			mesh.Drop();

			clockCenter.UpdateAbsolutePosition();
			boundingBox.AddInternalBox(clockCenter.BoundingBoxTransformed);
			for (int i = 0; i < clockCenter.MaterialCount; i++) materialList.Add(clockCenter.GetMaterial(i));

			// add clock ticks

			for (int j = 0; j < 12; j++)
			{
				mesh = SceneManager.GeometryCreator.CreateCylinderMesh(5, 10, 16, new Color(255, 255, 255), false);
				MeshSceneNode clockTick = SceneManager.AddMeshSceneNode(mesh, this);
				clockTick.Rotation = new Vector3Df(90, 0, 0);

				float s = (float)Math.Sin((j * (360 / 12)) / (180 / Math.PI));
				float c = (float)Math.Cos((j * (360 / 12)) / (180 / Math.PI));
				clockTick.Position = new Vector3Df(s * 80, c * 80, 0);

				if ((j % 3) == 0)
					clockTick.Scale = new Vector3Df(2, 1, 2);

				mesh.Drop();

				clockTick.UpdateAbsolutePosition();
				boundingBox.AddInternalBox(clockTick.BoundingBoxTransformed);
				for (int i = 0; i < clockTick.MaterialCount; i++) materialList.Add(clockTick.GetMaterial(i));
			}

			// add hour arrow

			mesh = SceneManager.GeometryCreator.CreateArrowMesh(12, 12, 40, 35, 4, 4, new Color(40, 40, 255), new Color(40, 40, 255));
			arrowHours = SceneManager.AddMeshSceneNode(mesh, this);
			arrowHours.GetMaterial(0).EmissiveColor = new Color(0, 0, 255);
			arrowHours.GetMaterial(1).EmissiveColor = new Color(0, 0, 255);
			arrowHours.Position = new Vector3Df(0, 0, 3);
			mesh.Drop();

			arrowHours.UpdateAbsolutePosition();
			boundingBox.AddInternalBox(arrowHours.BoundingBoxTransformed);
			for (int i = 0; i < arrowHours.MaterialCount; i++) materialList.Add(arrowHours.GetMaterial(i));

			// add minute arrow

			mesh = SceneManager.GeometryCreator.CreateArrowMesh(12, 12, 60, 50, 4, 4, new Color(40, 255, 40), new Color(40, 255, 40));
			arrowMinutes = SceneManager.AddMeshSceneNode(mesh, this);
			arrowMinutes.GetMaterial(0).EmissiveColor = new Color(0, 255, 0);
			arrowMinutes.GetMaterial(1).EmissiveColor = new Color(0, 255, 0);
			arrowMinutes.Position = new Vector3Df(0, 0, -5);
			mesh.Drop();

			arrowMinutes.UpdateAbsolutePosition();
			boundingBox.AddInternalBox(arrowMinutes.BoundingBoxTransformed);
			for (int i = 0; i < arrowMinutes.MaterialCount; i++) materialList.Add(arrowMinutes.GetMaterial(i));

			// add second arrow

			mesh = SceneManager.GeometryCreator.CreateArrowMesh(12, 12, 70, 60, 2, 2, new Color(255, 40, 40), new Color(255, 40, 40));
			arrowSeconds = SceneManager.AddMeshSceneNode(mesh, this);
			arrowSeconds.GetMaterial(0).EmissiveColor = new Color(255, 0, 0);
			arrowSeconds.GetMaterial(1).EmissiveColor = new Color(255, 0, 0);
			arrowSeconds.Position = new Vector3Df(0, 0, -11);
			mesh.Drop();

			arrowSeconds.UpdateAbsolutePosition();
			boundingBox.AddInternalBox(arrowSeconds.BoundingBoxTransformed);
			for (int i = 0; i < arrowSeconds.MaterialCount; i++) materialList.Add(arrowSeconds.GetMaterial(i));

			SceneManager.AddLightSceneNode(arrowSeconds, new Vector3Df(0, 70, 0), new Colorf(arrowSeconds.GetMaterial(0).EmissiveColor), 80);
			SceneManager.AddLightSceneNode(arrowMinutes, new Vector3Df(0, 60, 0), new Colorf(arrowMinutes.GetMaterial(0).EmissiveColor), 60);
			SceneManager.AddLightSceneNode(arrowHours, new Vector3Df(0, 40, 0), new Colorf(arrowHours.GetMaterial(0).EmissiveColor), 40);
		}

		AABBox ClockNode_OnGetBoundingBox()
		{
			return boundingBox;
		}

		int ClockNode_OnGetMaterialCount()
		{
			return materialList.Count;
		}

		Material ClockNode_OnGetMaterial(int index)
		{
			return materialList[index];
		}

		void ClockNode_OnRegisterSceneNode()
		{
			if (Visible)
				SceneManager.RegisterNodeForRendering(this);
		}

		void ClockNode_OnRender()
		{
			DateTime time = DateTime.Now;

			arrowSeconds.Rotation = new Vector3Df(0, 0, -time.Second * (360 / 60));
			arrowMinutes.Rotation = new Vector3Df(0, 0, -time.Minute * (360 / 60));
			arrowHours.Rotation = new Vector3Df(0, 0, -(time.Hour % 12) * (360 / 12));
		}
	}
}
