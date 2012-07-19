using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

using BulletSharp;

namespace L11.BulletSharpTest
{
	class Physics
	{
		public enum Shape
		{
			Box,
			Shpere,
			Mesh
		}

		DefaultCollisionConfiguration bulletCollisionConfiguration;
		CollisionDispatcher bulletCollisionDispatcher;
		BroadphaseInterface bulletBroadphase;
		DiscreteDynamicsWorld bulletWorld;

		Thread simThread = null;
		float simTimeStep = 0;

		public void Setup(Vector3Df gravity)
		{
			bulletCollisionConfiguration = new DefaultCollisionConfiguration();
			bulletCollisionDispatcher = new CollisionDispatcher(bulletCollisionConfiguration);
			bulletBroadphase = new DbvtBroadphase();

			bulletWorld = new DiscreteDynamicsWorld(bulletCollisionDispatcher, bulletBroadphase, null, bulletCollisionConfiguration);
			bulletWorld.Gravity = new Vector3(gravity.X, gravity.Y, gravity.Z);
		}

		public void Drop()
		{
			if (simThread != null)
				simThread.Join();

			bulletWorld.Dispose();
			bulletBroadphase.Dispose();
			bulletCollisionDispatcher.Dispose();
			bulletCollisionConfiguration.Dispose();
		}

		public void AddShape(Shape shape, SceneNode node, float mass = 0.0f, bool sleeping = true, Vector3Df startImpulse = null)
		{
			CollisionShape collShape = bulletGetCollisionShape(shape, node);

			if (simThread != null)
				simThread.Join();

			RigidBody body = bulletCreateRigidBody(
				mass,
				BulletSharp.Matrix.Translation(node.Position.X, node.Position.Y, node.Position.Z),
				collShape);

			if (sleeping)
				body.ForceActivationState(ActivationState.IslandSleeping);

			if (startImpulse != null)
				body.ApplyCentralImpulse(new Vector3(startImpulse.X, startImpulse.Y, startImpulse.Z));

			body.SetSleepingThresholds(body.LinearSleepingThreshold * 20, body.AngularSleepingThreshold * 20);

			body.UserObject = node;
		}

		public bool StepSimulation(float timeStep)
		{
			simTimeStep += timeStep;

			if (simThread != null)
				return false;

			simThread = new System.Threading.Thread(new ParameterizedThreadStart(delegate(object t)
			{
				float s = (float)t;
				if (s > 1.0f / 60)
					s = 1.0f / 60;

				bulletWorld.StepSimulation(s);

				List<CollisionObject> r = new List<CollisionObject>();

				IrrlichtLime.Core.Matrix m = new IrrlichtLime.Core.Matrix();
				foreach (CollisionObject collObj in bulletWorld.CollisionObjectArray)
				{
					if (collObj.IsStaticObject || !collObj.IsActive)
						continue;

					m.SetElementArray(collObj.WorldTransform.ToArray());

					SceneNode n = collObj.UserObject as SceneNode;
					n.Position = m.Translation;
					n.Rotation = m.Rotation;
					
					if (m.Translation.Y < -40000)
						r.Add(collObj);
				}

				foreach (CollisionObject o in r)
				{
					(o.UserObject as SceneNode).SceneManager.AddToDeletionQueue(o.UserObject as SceneNode);
					bulletWorld.RemoveCollisionObject(o);
				}

				simThread = null;
			}));

			simThread.Start(simTimeStep);
			simTimeStep = 0;

			return true;
		}

		public int NumCollisionObject { get { return bulletWorld.NumCollisionObjects; } }

		CollisionShape bulletGetCollisionShape(Shape shape, SceneNode node)
		{
			switch (shape)
			{
				case Shape.Box:
					{
						return new BoxShape(node.BoundingBox.Extent.X / 2);
					}

				case Shape.Shpere:
					{
						return new SphereShape(node.BoundingBox.Extent.X / 2);
					}

				case Shape.Mesh:
					{
						MeshSceneNode meshNode = node as MeshSceneNode;
						if (meshNode == null)
							throw new ArgumentException();

						TriangleMesh triagleMesh = new TriangleMesh();
						for (int i = 0; i < meshNode.Mesh.MeshBufferCount; i++)
						{
							MeshBuffer b = meshNode.Mesh.GetMeshBuffer(i);
							ushort[] inds = b.Indices as ushort[];
							Vertex3DTTCoords[] verts = b.Vertices as Vertex3DTTCoords[];

							if (inds == null || verts == null)
								throw new ArgumentException();

							for (int j = 0; j < inds.Length / 3; j++)
							{
								triagleMesh.AddTriangle(
									new Vector3(verts[inds[j * 3 + 0]].Position.X, verts[inds[j * 3 + 0]].Position.Y, verts[inds[j * 3 + 0]].Position.Z),
									new Vector3(verts[inds[j * 3 + 1]].Position.X, verts[inds[j * 3 + 1]].Position.Y, verts[inds[j * 3 + 1]].Position.Z),
									new Vector3(verts[inds[j * 3 + 2]].Position.X, verts[inds[j * 3 + 2]].Position.Y, verts[inds[j * 3 + 2]].Position.Z));
							}
						}

						return new BvhTriangleMeshShape(triagleMesh, false);
					}

				default:
					throw new ArgumentException();
			}
		}

		RigidBody bulletCreateRigidBody(float mass, BulletSharp.Matrix startTransform, CollisionShape shape)
		{
			bool isDynamic = (mass != 0.0f);

			Vector3 localInertia = Vector3.Zero;
			if (isDynamic)
				shape.CalculateLocalInertia(mass, out localInertia);

			DefaultMotionState motionState = new DefaultMotionState(startTransform);

			RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, motionState, shape, localInertia);
			RigidBody body = new RigidBody(rbInfo);

			bulletWorld.AddRigidBody(body);

			return body;
		}
	}
}
