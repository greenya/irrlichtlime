using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.Core;

namespace L04.ParticleEmitterViewer
{
	/// <summary>
	/// This class do all the rendering work.
	/// This class is the only place where we actually use IrrlichtLime.
	/// </summary>
	class Viewport
	{
		Thread irrThread;
		IrrlichtDevice irrDevice;
		Queue<Command> commandQueue;

		public void Start(IntPtr windowHandle)
		{
			if (irrThread != null)
				throw new InvalidOperationException("Previous viewport needs to be stopped!");

			commandQueue = new Queue<Command>();

			irrThread = new Thread(new ParameterizedThreadStart(irrThreadMain));
			irrThread.Name = "Irrlicht rendering";

			IrrlichtCreationParameters p = new IrrlichtCreationParameters();
			//p.AntiAliasing = 4;
			p.DriverType = DriverType.Direct3D8;
			p.WindowID = windowHandle;

			irrThread.Start(p);
		}

		public void Stop()
		{
			EnqueueCommand(CommandType.Abort, null);
			irrThread.Join(200);

			if (irrThread.IsAlive)
				irrThread.Abort();

			irrThread = null;
		}

		public void EnqueueCommand(CommandType type, object param)
		{
			Command c = new Command();
			c.Type = type;
			c.Param = param;

			// If this is Abort command -- we clean up all the queue (all old commands that still waiting
			// for processing) and add this Abort command, since it is a top priority command.
			if (c.Type == CommandType.Abort)
			{
				lock (commandQueue)
				{
					commandQueue.Clear();
					commandQueue.Enqueue(c);
				}
				return;
			}

			// We check for old same command and use it instead of adding new one -- for optimization.
			// This way we make not more than only one command of same type to be in the queue.
			lock (commandQueue)
			{
				foreach (Command n in commandQueue)
				{
					if (n.Type == c.Type)
					{
						n.Param = c.Param;
						return;
					}
				}
			}

			// We add new command to queue.
			lock (commandQueue)
			{
				commandQueue.Enqueue(c);
			}
		}

		enum SceneNodeID
		{
			Camera,
			AxisX,
			AxisY,
			AxisZ,
			Plane,
			ParticleSystem
		}

		ParticleFadeOutAffector affFadeOut; // We store these pointers because when affector once added
		ParticleGravityAffector affGravity; // to particle system, there is no any method to retrieve
		ParticleRotationAffector affRotation; // its pointer back later :(

		void irrThreadMain(object args)
		{
			irrDevice = IrrlichtDevice.CreateDevice(args as IrrlichtCreationParameters);

			// Camera

			CameraSceneNode camera = irrDevice.SceneManager.AddCameraSceneNode(null, new Vector3Df(0), new Vector3Df(0, 80, 0), (int)SceneNodeID.Camera);
			SceneNodeAnimator anim = irrDevice.SceneManager.CreateFlyCircleAnimator(new Vector3Df(0, 100, 0), 200.0f, 0.0002f);
			camera.AddAnimator(anim);
			anim.Drop();

			// Skydome

			irrDevice.SceneManager.AddSkyDomeSceneNode(irrDevice.VideoDriver.GetTexture("../media/skydome.jpg"), 16, 8, 0.95f, 2.0f);

			// Plane

			var m = irrDevice.SceneManager.AddHillPlaneMesh("plane", new Dimension2Df(1000), new Dimension2Di(1), null, 0, new Dimension2Df(0), new Dimension2Df(8));
			var n = irrDevice.SceneManager.AddAnimatedMeshSceneNode(m, null, (int)SceneNodeID.Plane);
			n.SetMaterialFlag(MaterialFlag.Lighting, false);
			n.SetMaterialTexture(0, irrDevice.VideoDriver.GetTexture("../media/rockwall.jpg"));

			// Axes

			m = irrDevice.SceneManager.AddArrowMesh("axisX");
			n = irrDevice.SceneManager.AddAnimatedMeshSceneNode(m, null, (int)SceneNodeID.AxisX, new Vector3Df(), new Vector3Df(0, 0, -90), new Vector3Df(50, 120, 50));
			n.GetMaterial(0).EmissiveColor = new Color(250, 250, 250);
			n.GetMaterial(1).EmissiveColor = new Color(250, 0, 0);

			m = irrDevice.SceneManager.AddArrowMesh("axisY");
			n = irrDevice.SceneManager.AddAnimatedMeshSceneNode(m, null, (int)SceneNodeID.AxisY, new Vector3Df(), new Vector3Df(0, 0, 0), new Vector3Df(50, 120, 50));
			n.GetMaterial(0).EmissiveColor = new Color(250, 250, 250);
			n.GetMaterial(1).EmissiveColor = new Color(0, 250, 0);

			m = irrDevice.SceneManager.AddArrowMesh("axisZ");
			n = irrDevice.SceneManager.AddAnimatedMeshSceneNode(m, null, (int)SceneNodeID.AxisZ, new Vector3Df(), new Vector3Df(90, 0, 0), new Vector3Df(50, 120, 50));
			n.GetMaterial(0).EmissiveColor = new Color(250, 250, 250);
			n.GetMaterial(1).EmissiveColor = new Color(0, 0, 250);

			irrThreadShowAxes(false);

			// Particle system

			var ps = irrDevice.SceneManager.AddParticleSystemSceneNode(false, null, (int)SceneNodeID.ParticleSystem);

			ps.SetMaterialFlag(MaterialFlag.Lighting, false);
			ps.SetMaterialFlag(MaterialFlag.ZWrite, false);
			ps.SetMaterialTexture(0, irrDevice.VideoDriver.GetTexture("../media/particle.bmp"));
			ps.SetMaterialType(MaterialType.TransparentAddColor);

			ParticleEmitter em = ps.CreateSphereEmitter(
				new Vector3Df(), 20,				// position and radius
				new Vector3Df(0.0f, 0.1f, 0.0f),	// initial direction
				150, 300,							// emit rate
				new Color(255, 255, 255, 0),		// darkest color
				new Color(255, 255, 255, 0),		// brightest color
				750, 1500, 0,						// min and max age, angle
				new Dimension2Df(20.0f),			// min size
				new Dimension2Df(40.0f));			// max size

			ps.Emitter = em;
			em.Drop();

			// Particle affectors

			affFadeOut = ps.CreateFadeOutParticleAffector();
			ps.AddAffector(affFadeOut);
			affFadeOut.Drop();

			affGravity = ps.CreateGravityAffector(new Vector3Df(0, -1, 0), 3);
			affGravity.Enabled = false;
			ps.AddAffector(affGravity);
			affGravity.Drop();

			affRotation = ps.CreateRotationAffector(new Vector3Df(-90, 240, -120), new Vector3Df(0, 100, 0));
			ps.AddAffector(affRotation);
			affRotation.Drop();

			// Rendering loop

			uint rs = 0, re = 0; // render frame time
			while (irrDevice.Run())
			{
				if (irrDevice.VideoDriver.ScreenSize.Area != 0)
				{
					irrDevice.VideoDriver.BeginScene();
					irrDevice.SceneManager.DrawAll();
					re = irrDevice.Timer.Time;

					irrThreadDrawText(new Vector2Di(8, 8),
						"Frame time: " + (irrDevice.VideoDriver.FPS > 1000 ? "< 1" : (re - rs).ToString()) + " ms");

					irrDevice.VideoDriver.EndScene();
				}
				else
				{
					Thread.Sleep(50);
				}

				irrThreadProcessCommandQueue();
				rs = irrDevice.Timer.Time;
			}

			irrDevice.Drop();
		}

		private void irrThreadDrawText(Vector2Di p, string s)
		{
			Dimension2Di d = irrDevice.GUIEnvironment.BuiltInFont.GetDimension(s);
			d.Width += 8;
			d.Height += 6;
			irrDevice.VideoDriver.Draw2DRectangle(new Recti(p, d), new Color(0x7F000000));
			irrDevice.GUIEnvironment.BuiltInFont.Draw(s, p + new Vector2Di(4, 3), new Color(250, 250, 250));
		}

		private void irrThreadShowAxes(bool v)
		{
			irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.AxisX).Visible = v;
			irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.AxisY).Visible = v;
			irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.AxisZ).Visible = v;
		}

		private void irrThreadProcessCommandQueue()
		{
			if (commandQueue.Count == 0)
				return;

			Command c;
			lock (commandQueue)
			{
				c = commandQueue.Dequeue();
			}

			switch (c.Type)
			{
				case CommandType.Abort:
					{
						irrDevice.Close();
						break;
					}

				case CommandType.Axes:
					{
						irrThreadShowAxes((bool)c.Param);
						break;
					}

				case CommandType.Plane:
					{
						var n = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.Plane);
						n.Visible = (bool)c.Param;
						break;
					}

				case CommandType.Particle:
					{
						var n = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem);
						n.SetMaterialTexture(0, irrDevice.VideoDriver.GetTexture(((ParticleInfo)c.Param).FileName));
						break;
					}

				case CommandType.Resize:
					{
						int[] i = (int[])c.Param;
						Dimension2Di d = new Dimension2Di(i[0], i[1]);
						irrDevice.VideoDriver.ResizeNotify(d);
						(irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.Camera) as CameraSceneNode).AspectRatio =
							i[2] == 1 ? (float)i[0] / i[1] : 1.333333f;
						break;
					}

				case CommandType.Position:
					{
						float[] f = (float[])c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
						(p.Emitter as ParticleSphereEmitter).Center = new Vector3Df(f[0], f[1], f[2]);
						break;
					}

				case CommandType.Radius:
					{
						float f = (float)c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
						(p.Emitter as ParticleSphereEmitter).Radius = f;
						break;
					}

				case CommandType.CameraView:
					{
						float f = (float)c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.Camera) as CameraSceneNode;
						p.Target = new Vector3Df(p.Target.X, f, p.Target.Z);
						//p.FOV = 1.25f + (f - 80) / 100.0f;
						break;
					}

				case CommandType.Rate:
					{
						int v = (int)c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
						p.Emitter.MaxParticlesPerSecond = v;
						p.Emitter.MinParticlesPerSecond = v/2;
						break;
					}

				case CommandType.Size:
					{
						int v = (int)c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
						p.Emitter.MaxStartSize = new Dimension2Df(v);
						p.Emitter.MinStartSize = new Dimension2Df(v/2);
						break;
					}

				case CommandType.Direction:
					{
						float[] f = (float[])c.Param;
						var p = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
						p.Emitter.Direction = new Vector3Df(f[0], f[1], f[2]);
						break;
					}

				case CommandType.FadeOut:
					{
						affFadeOut.Enabled = (bool)c.Param;
						break;
					}

				case CommandType.Rotation:
					{
						affRotation.Enabled = (bool)c.Param;
						break;
					}

				case CommandType.Gravity:
					{
						affGravity.Enabled = (bool)c.Param;
						break;
					}

				default:
					throw new InvalidOperationException("Unexpected command type: " + c.Type.ToString());
			}
		}
	}
}
