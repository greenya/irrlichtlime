using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime.Core;
using IrrlichtLime.Scene;
using IrrlichtLime.Video;

namespace L12.StencilShadows
{
	class Shadows
	{
		List<SceneNode> objects = new List<SceneNode>();
		List<SceneNode> lights = new List<SceneNode>();
		Color shadowColor = Color.OpaqueBlack;
		float shadowInfinityRange = 1000.0f;
		float shadowNearMultiplier = 1.0f / 40;

		List<Vector3Df> visibleShadowVerticesBuffer = null;
		object visibleShadowVerticesBufferLocker = new object();

		Thread buildThread = null;

		public Shadows(Color shadowColor, float shadowInfinityRange)
		{
			this.shadowColor = shadowColor;
			this.shadowInfinityRange = shadowInfinityRange;
			this.shadowNearMultiplier = (float)(1.0f / Math.Sqrt(shadowInfinityRange));
		}

		public void Drop()
		{
			if (buildThread != null)
				buildThread.Join();
		}

		public void AddObject(SceneNode node)
		{
			if (buildThread != null)
				buildThread.Join();

			if (!(node is MeshSceneNode) &&
				!(node is AnimatedMeshSceneNode))
				throw new ArgumentException();

			node.UpdateAbsolutePosition();
			objects.Add(node);
		}

		public void RemoveObject(SceneNode node)
		{
			if (buildThread != null)
				buildThread.Join();

			objects.Remove(node);
		}

		public void AddLight(SceneNode node)
		{
			if (buildThread != null)
				buildThread.Join();

			node.UpdateAbsolutePosition();
			lights.Add(node);
		}

		public void RemoveLight(SceneNode node)
		{
			if (buildThread != null)
				buildThread.Join();

			lights.Remove(node);
		}

		public void DrawShadowVolume(VideoDriver driver, bool isDebug = false)
		{
			lock (visibleShadowVerticesBufferLocker)
			{
				if (visibleShadowVerticesBuffer == null ||
					visibleShadowVerticesBuffer.Count == 0)
					return;

				driver.SetTransform(TransformationState.World, Matrix.Identity);

				if (isDebug)
				{
					Material material = new Material();
					material.Lighting = false;
					material.Type = MaterialType.TransparentVertexAlpha;

					driver.SetMaterial(material);
					for (int i = 0; i < visibleShadowVerticesBuffer.Count; i += 3)
						driver.Draw3DTriangle(
							visibleShadowVerticesBuffer[i],
							visibleShadowVerticesBuffer[i + 1],
							visibleShadowVerticesBuffer[i + 2],
							new Color(0x80000000));

					material.Wireframe = true;
					material.BackfaceCulling = false;
					material.ZBuffer = ComparisonFunc.Always;
					driver.SetMaterial(material);
					for (int i = 0; i < visibleShadowVerticesBuffer.Count; i += 3)
						driver.Draw3DTriangle(
							visibleShadowVerticesBuffer[i],
							visibleShadowVerticesBuffer[i + 1],
							visibleShadowVerticesBuffer[i + 2],
							new Color(0x80ff0000));
				}
				else
				{
					driver.DrawStencilShadowVolume(visibleShadowVerticesBuffer);
					driver.DrawStencilShadow(false, shadowColor);
				}
			}
		}

		public int VerticesBuilt
		{
			get
			{
				lock (visibleShadowVerticesBufferLocker)
				{
					return visibleShadowVerticesBuffer != null ? visibleShadowVerticesBuffer.Count : 0;
				}
			}
		}

		public bool BuildShadowVolume()
		{
			if (buildThread != null)
				return false;

			buildThread = new Thread(new ThreadStart(delegate()
			{
				int va = 10000;

				lock (visibleShadowVerticesBufferLocker)
				{
					if (visibleShadowVerticesBuffer != null)
						va = visibleShadowVerticesBuffer.Count;
				}

				List<Vector3Df> v = new List<Vector3Df>(va);

				foreach (SceneNode lightNode in lights)
				{
					Vector3Df l = lightNode.AbsolutePosition;

					foreach (SceneNode objectNode in objects)
					{
						Matrix t = objectNode.AbsoluteTransformation;
						Mesh m = null;

						if (objectNode is MeshSceneNode)
						{
							m = (objectNode as MeshSceneNode).Mesh;
						}
						else if (objectNode is AnimatedMeshSceneNode)
						{
							m = (objectNode as AnimatedMeshSceneNode).Mesh;
						}

						for (int i = 0; i < m.MeshBufferCount; i++)
						{
							buildShadowVolume(v, m.GetMeshBuffer(i), t, l);
						}
					}
				}

				lock (visibleShadowVerticesBufferLocker)
				{
					if (visibleShadowVerticesBuffer != null)
						visibleShadowVerticesBuffer.Clear();

					visibleShadowVerticesBuffer = v;
				}

				buildThread = null;
			}));

			buildThread.Start();

			return true;
		}

		void buildShadowVolume(List<Vector3Df> shadowVertices, MeshBuffer meshbuffer, Matrix matrix, Vector3Df light)
		{
			ushort[] indices = meshbuffer.Indices as ushort[];

			if (indices == null)
				throw new ArgumentException();

			Triangle3Df t123 = new Triangle3Df();

			for (int i = 0; i < indices.Length; i += 3)
			{
				Vector3Df v1 = meshbuffer.GetPosition(indices[i]);
				Vector3Df v2 = meshbuffer.GetPosition(indices[i + 1]);
				Vector3Df v3 = meshbuffer.GetPosition(indices[i + 2]);

				matrix.TransformVector(ref v1);
				matrix.TransformVector(ref v2);
				matrix.TransformVector(ref v3);

				t123.Set(v1, v2, v3);

				Vector3Df v1Dir = v1 - light;

				if (!t123.IsFrontFacing(v1Dir))
					continue;

				Vector3Df v2Dir = v2 - light;
				Vector3Df v3Dir = v3 - light;

				// calc near points

				Vector3Df v1near = v1 + v1Dir * shadowNearMultiplier;
				Vector3Df v2near = v2 + v2Dir * shadowNearMultiplier;
				Vector3Df v3near = v3 + v3Dir * shadowNearMultiplier;

				// calc infinity points

				Vector3Df v1inf = v1 + v1Dir.Normalize() * shadowInfinityRange;
				Vector3Df v2inf = v2 + v2Dir.Normalize() * shadowInfinityRange;
				Vector3Df v3inf = v3 + v3Dir.Normalize() * shadowInfinityRange;

				// top
				shadowVertices.Add(v1near);
				shadowVertices.Add(v2near);
				shadowVertices.Add(v3near);

				// bottom
				shadowVertices.Add(v3inf);
				shadowVertices.Add(v2inf);
				shadowVertices.Add(v1inf);

				// side1

				shadowVertices.Add(v1inf);
				shadowVertices.Add(v2near);
				shadowVertices.Add(v1near);

				shadowVertices.Add(v1inf);
				shadowVertices.Add(v2inf);
				shadowVertices.Add(v2near);

				// side2

				shadowVertices.Add(v2inf);
				shadowVertices.Add(v3near);
				shadowVertices.Add(v2near);

				shadowVertices.Add(v2inf);
				shadowVertices.Add(v3inf);
				shadowVertices.Add(v3near);

				// side3

				shadowVertices.Add(v1near);
				shadowVertices.Add(v3near);
				shadowVertices.Add(v1inf);

				shadowVertices.Add(v3near);
				shadowVertices.Add(v3inf);
				shadowVertices.Add(v1inf);
			}
		}
	}
}
