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
			p.DriverType = DriverType.OpenGL;
			p.WindowID = windowHandle;

			irrThread.Start(p);
		}

		public void Stop()
		{
			EnqueueCommand(CommandType.Abort);
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

			lock (commandQueue)
			{
				commandQueue.Enqueue(c);
			}
		}

		public void EnqueueCommand(CommandType type)
		{
			EnqueueCommand(type, null);
		}

		enum SceneNodeID
		{
			AxisX,
			AxisY,
			AxisZ,
			Plane,
			ParticleSystem
		}

		void irrThreadMain(object args)
		{
			irrDevice = IrrlichtDevice.CreateDevice(args as IrrlichtCreationParameters);

			// Camera

			CameraSceneNode camera = irrDevice.SceneManager.AddCameraSceneNode(null, new Vector3Df(0), new Vector3Df(0, 80, 0));
			SceneNodeAnimator anim = irrDevice.SceneManager.CreateFlyCircleAnimator(new Vector3Df(0, 100, 0), 200.0f, 0.0002f);
			camera.AddAnimator(anim);
			anim.Drop();

			// Skydome

			irrDevice.SceneManager.AddSkyDomeSceneNode(irrDevice.VideoDriver.GetTexture("../media/skydome.jpg"), 16, 8, 0.95f, 2.0f);

			// Cube

			//var rr = irrDevice.SceneManager.AddCubeSceneNode(150);
			////rr.GetMaterial(0).Lighting = false;
			//rr.GetMaterial(0).EmissiveColor = new Color(0, 40, 0, 120);
			//rr.SetMaterialType(MaterialType.TransparentAddColor);

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

			ParticleEmitter em = ps.CreateBoxEmitter(
				new AABBox(-20, 0, -20, 20, 4, 20),	// emitter size
				new Vector3Df(0.0f, 0.1f, 0.0f),	// initial direction
				80, 250,							// emit rate
				new Color(255, 255, 255, 0),		// darkest color
				new Color(255, 255, 255, 0),		// brightest color
				800, 1500, 0,						// min and max age, angle
				new Dimension2Df(20.0f),			// min size
				new Dimension2Df(40.0f));			// max size

			ps.Emitter = em;
			em.Drop();

			// Rendering loop

			while (irrDevice.Run())
			{
				irrDevice.VideoDriver.BeginScene();
				irrDevice.SceneManager.DrawAll();

				irrThreadDrawText(new Vector2Di(8, 8), irrDevice.VideoDriver.FPS.ToString() + " fps");
				irrDevice.VideoDriver.EndScene();

				irrThreadProcessCommandQueue();
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
					irrDevice.Close();
					break;

				case CommandType.Axes:
					irrThreadShowAxes((bool)c.Param);
					break;

				case CommandType.Plane:
					irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.Plane).Visible = (bool)c.Param;
					break;

				case CommandType.Particle:
					irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem).SetMaterialTexture(0,
					    irrDevice.VideoDriver.GetTexture(((ParticleInfo)c.Param).FileName));
					break;

				case CommandType.Emmit:
					var ps = irrDevice.SceneManager.GetSceneNodeFromID((int)SceneNodeID.ParticleSystem) as ParticleSystemSceneNode;
					ps.Emitter.MaxParticlesPerSecond = (bool)c.Param ? 250 : 0;
					break;

				default:
					throw new InvalidOperationException("Unexpected command type: " + c.Type.ToString());
			}
		}
	}
}
