using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L11.BulletSharpTest
{
	class Particles
	{
		IrrlichtDevice device;
		List<ParticleNode> particleNodes;

		public Particles(IrrlichtDevice device)
		{
			this.device = device;
			particleNodes = new List<ParticleNode>();
		}

		public void Add(SceneNode parent, uint time)
		{
			ParticleSystemSceneNode ps = device.SceneManager.AddParticleSystemSceneNode(false, parent);

			ParticleEmitter em = ps.CreateBoxEmitter(
				new AABBox(parent.BoundingBox.MinEdge / 4, parent.BoundingBox.MaxEdge / 4),
				new Vector3Df(0.0f, 0.025f, 0.0f),
				100, 200,
				new Color(0xffffffff), new Color(0xffffffff),
				1500, 2500);

			em.MinStartSize = new Dimension2Df(parent.BoundingBox.Extent.X, parent.BoundingBox.Extent.Y);
			em.MaxStartSize = em.MinStartSize * 1.5f;

			ps.Emitter = em;
			em.Drop();

			ParticleAffector paf = ps.CreateFadeOutParticleAffector();
			ps.AddAffector(paf);
			paf.Drop();

			ps.SetMaterialFlag(MaterialFlag.Lighting, false);
			ps.SetMaterialFlag(MaterialFlag.ZWrite, false);
			ps.SetMaterialTexture(0, device.VideoDriver.GetTexture("../../media/fireball.bmp"));
			ps.SetMaterialType(MaterialType.TransparentAddColor);

			particleNodes.Add(new ParticleNode(ps, time));
		}

		public void Winnow(uint time, bool simPaused)
		{
			List<ParticleNode> r = new List<ParticleNode>();

			foreach (ParticleNode n in particleNodes)
			{
				if (simPaused)
				{
					n.TimeOfSteady = time;
					continue;
				}

				Matrix m = n.Node.AbsoluteTransformation;

				if (m.Translation.Y < -20000)
				{
					r.Add(n);
				}
				else
				{
					if (n.LastAbsoluteTransformation != m)
					{
						n.LastAbsoluteTransformation = m;
						n.TimeOfSteady = time;
					}
					else
					{
						if (time - n.TimeOfSteady > 1000)
						{
							r.Add(n);
						}
					}
				}
			}

			foreach (ParticleNode n in r)
			{
				n.Node.Remove();
				particleNodes.Remove(n);
			}
		}

		class ParticleNode
		{
			public SceneNode Node;
			public uint TimeOfSteady;
			public Matrix LastAbsoluteTransformation;

			public ParticleNode(SceneNode n, uint time)
			{
				Node = n;
				TimeOfSteady = time;
				LastAbsoluteTransformation = Matrix.Identity;
			}
		}
	}
}
