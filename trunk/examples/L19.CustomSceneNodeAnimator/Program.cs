using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L19.CustomSceneNodeAnimator
{
	class Program
	{

		static SceneNodeAnimator customAnimator;
		static IrrlichtDevice device;

		static void Main(string[] args)
		{
			device = IrrlichtDevice.CreateDevice(DriverType.OpenGL, new Dimension2Di(640, 480), 16, false);

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			smgr.AddCameraSceneNode(null, new Vector3Df(0, -40, 0), new Vector3Df(0));

			smgr.AddLightSceneNode(null, new Vector3Df(3f, 4f, 1f));
			smgr.AmbientLight = new Colorf(0.3f, 0.3f, 0.4f);

			MeshSceneNode node = smgr.AddCubeSceneNode();
			node.SetMaterialTexture(0, driver.GetTexture("../../media/stones.jpg"));

			customAnimator = new SampleSceneNodeAnimator();

			if (customAnimator != null)
			{
				node.AddAnimator(customAnimator);

				//usually, we would drop it, but we keep it so the user can pause the animation by pressing space
				//customAnimator.Drop();
				//customAnimator = null;
			}

			node = null;

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);

			int frames = 0;
			while (device.Run())
			{
				driver.BeginScene(ClearBufferFlag.All, new Color(100, 100, 100));
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

			//now we really don't need it anymore
			customAnimator.Drop();
			customAnimator = null;
			device.Drop();
		}

		static bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Key)
				if (evnt.Key.Char == ' ')
				{
					customAnimator.SetEnabled(!customAnimator.Enabled, device.Timer.Time);
					return true;
				}
			return false;
		}
	}

	class SampleSceneNodeAnimator : SceneNodeAnimator
#if DEBUG
        , IDisposable   //Only extend IDisposable in debug mode. This is only for demonstration. You only extend IDisposable if you need it as well in the release.
#endif
	{
		public SampleSceneNodeAnimator()
			: base(true)
		{
			this.OnAnimateNode += new AnimateNodeEventHandler(SampleSceneNodeAnimator_OnAnimateNode);
			this.OnGetFinished += new GetFinishedEventHandler(SampleSceneNodeAnimator_OnGetFinished);
			this.OnCreateClone += new CreateCloneEventHandler(SampleSceneNodeAnimator_OnCreateClone);
			this.OnIsEventReceiverEnabled += new IsEventReceiverEnabledEventHandler(SampleSceneNodeAnimator_OnIsEventReceiverEnabled);
		}

		bool SampleSceneNodeAnimator_OnIsEventReceiverEnabled()
		{  
			//Does not receive events from camera.
			return false;
		}

		void SampleSceneNodeAnimator_OnAnimateNode(SceneNode node, uint time)
		{
			if (node == null)
				return;
			//calculate new time without pause and relative to the start time
			int newTime = ((int)time - (int)(StartTime + PauseTimeSum));
			//simply move up and down
			node.Position = new Vector3Df((float)Math.Sin((double)newTime / 1000) * 5, 0, 0);
		}

		bool SampleSceneNodeAnimator_OnGetFinished()
		{
			//Never finishes.
			return false;
		}

		SceneNodeAnimator SampleSceneNodeAnimator_OnCreateClone(SceneNode node, SceneManager newManager)
		{
			//We don't have to copy any attributes.
			//The properties Enabled, StartTime, PauseTimeStart and PauseTime are copied automaticly.
			return new SampleSceneNodeAnimator();
		}

#if DEBUG   //Only compiles in debug mode
        public void Dispose()
		{
			//This method is called, when the scene node is being deleted. You can use it for cleanup purpose.
			//It is called immediatly when the node's reference count is 0, unlike a finalizer, which is called after a random amount of time.
			//It only works, if you inherit IDisposable.
            Console.WriteLine(ToString() + " disposed!");
            Console.ReadKey();
        }
#endif
    }
}
