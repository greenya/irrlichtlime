using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Scene;

namespace L10.ImageBrowser
{
	class AnimationManager
	{
		IrrDevice irrDevice;
		List<AnimationItem> animationItems = new List<AnimationItem>();

		public AnimationManager(IrrDevice irrDevice)
		{
			this.irrDevice = irrDevice;
		}

		public void Add(SceneNode node, uint duration, Vector3Df targetPosition, Vector3Df targetRotation, Vector3Df targetScale)
		{
			Remove(node);

			irrDevice.Timer.Tick();

			AnimationItem a = new AnimationItem();
			a.Node = node;
			a.Node.Grab();
			a.Duration = duration;
			a.StartTime = irrDevice.Timer.Time;
			
			if (targetPosition != null)
			{
				a.TargetPosition = targetPosition;
				a.StartPosition = node.Position;
			}

			if (targetRotation != null)
			{
				a.TargetRotation = targetRotation;
				a.StartRotation = node.Rotation;
			}

			if (targetScale != null)
			{
				a.TargetScale = targetScale;
				a.StartScale = node.Scale;
			}

			lock (animationItems)
			{
				animationItems.Add(a);
			}
		}

		public void Remove(SceneNode node)
		{
			lock (animationItems)
			{
				int i = 0;
				for (i = 0; i < animationItems.Count; i++)
				{
					if (animationItems[i].Node == node)
						break;
				}

				if (i < animationItems.Count)
				{
					setFinalAnimationState(i);
					animationItems[i].Node.Drop();
					animationItems.RemoveAt(i);
				}
			}
		}

		public bool IsAnimated(SceneNode node)
		{
			lock (animationItems)
			{
				int i = 0;
				for (i = 0; i < animationItems.Count; i++)
				{
					if (animationItems[i].Node == node)
						break;
				}

				return i < animationItems.Count;
			}
		}

		public void Run()
		{
			lock (animationItems)
			{
				uint t = irrDevice.Timer.Time;
				List<int> candidatesToBeRemoved = new List<int>();

				for (int i = 0; i < animationItems.Count; i++)
				{
					AnimationItem a = animationItems[i];
					if (t >= a.StartTime + a.Duration)
					{
						setFinalAnimationState(i);
						candidatesToBeRemoved.Add(i);
					}
					else
					{
						double d = (double)(t - a.StartTime) / a.Duration;

						if (a.TargetPosition != null)
						{
							Vector3Df v = a.Node.Position;
							v.Interpolate(a.TargetPosition, a.StartPosition, d);
							a.Node.Position = v;
						}

						if (a.TargetRotation != null)
						{
							Vector3Df v = a.Node.Rotation;
							v.Interpolate(a.TargetRotation, a.StartRotation, d);
							a.Node.Rotation = v;
						}

						if (a.TargetScale != null)
						{
							Vector3Df v = a.Node.Scale;
							v.Interpolate(a.TargetScale, a.StartScale, d);
							a.Node.Scale = v;
						}
					}
				}

				for (int i = candidatesToBeRemoved.Count - 1; i >= 0; i--)
				{
					animationItems[candidatesToBeRemoved[i]].Node.Drop();
					animationItems.RemoveAt(candidatesToBeRemoved[i]);
				}
			}
		}

		public void Clear()
		{
			lock (animationItems)
			{
				for (int i = 0; i < animationItems.Count; i++)
					animationItems[i].Node.Drop();

				animationItems.Clear();
			}
		}

		void setFinalAnimationState(int i)
		{
			AnimationItem a = animationItems[i];

			if (a.TargetPosition != null)
				a.Node.Position = a.TargetPosition;

			if (a.TargetRotation != null)
				a.Node.Rotation = a.TargetRotation;

			if (a.TargetScale != null)
				a.Node.Scale = a.TargetScale;
		}

		class AnimationItem
		{
			public SceneNode Node;
			public uint Duration;

			public uint StartTime;
			public Vector3Df StartPosition;
			public Vector3Df StartRotation;
			public Vector3Df StartScale;

			public Vector3Df TargetPosition;
			public Vector3Df TargetRotation;
			public Vector3Df TargetScale;
		}
	}
}
