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

        static void Main(string[] args)
        {
            IrrlichtDevice device =
				IrrlichtDevice.CreateDevice(DriverType.OpenGL, new Dimension2Di(640, 480), 16, false);

			VideoDriver driver = device.VideoDriver;
			SceneManager smgr = device.SceneManager;

			smgr.AddCameraSceneNode(null, new Vector3Df(0, -40, 0), new Vector3Df(0));

            smgr.AddLightSceneNode(null, new Vector3Df(3f, 4f, 1f));
            smgr.AmbientLight = new Colorf(0.3f, 0.3f, 0.4f);

            MeshSceneNode node = smgr.AddCubeSceneNode();
            node.SetMaterialTexture(0, driver.GetTexture("../../media/stones.jpg"));

            SceneNodeAnimator anim = new SampleSceneNodeAnimator();

			if (anim != null)
			{
                node.AddAnimator(anim);
				anim.Drop();
				anim = null;
			}

            //node.Drop();
            node = null;

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

    class SampleSceneNodeAnimator : SceneNodeAnimator
    {
        public SampleSceneNodeAnimator()
            : base(true)
        {
            this.OnAnimateNode += new AnimateNodeEventHandler(SampleSceneNodeAnimator_OnAnimateNode);
            this.OnGetFinished +=new GetFinishedEventHandler(SampleSceneNodeAnimator_OnGetFinished);
        }

        void SampleSceneNodeAnimator_OnAnimateNode(SceneNode node, uint time)
        {
            node.Position = new Vector3Df((float)Math.Sin((double)time/1000)*5, 0, 0);
        }

        bool SampleSceneNodeAnimator_OnGetFinished()
        {
            return false;
        }
    }
}
