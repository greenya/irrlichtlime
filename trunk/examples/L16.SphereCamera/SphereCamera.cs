using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Scene;

namespace L16.SphereCamera
{
	class SphereCamera
	{
		IrrlichtDevice device;
		CameraSceneNode camera;
		Vector3Df target;

		double radius, minRadius, maxRadius;
		double inclination;
		double azimuth;

		public SphereCamera(IrrlichtDevice device, Vector3Df target, double minRadius, double maxRadius, double initRadius, double initInclination, double initAzimuth)
		{
			this.device = device;
			this.target = target;

			this.camera = device.SceneManager.AddCameraSceneNode();

			this.minRadius = minRadius;
			this.maxRadius = maxRadius;
			this.radius = initRadius;
			this.inclination = initInclination;
			this.azimuth = initAzimuth;
			setupCameraProperties();

			device.OnEvent += new IrrlichtDevice.EventHandler(device_OnEvent);
		}

		public double Radius
		{
			get { return radius; }
			set
			{
				if (value < minRadius)
					value = minRadius;

				if (value > maxRadius)
					value = maxRadius;

				radius = value;
				setupCameraProperties();
			}
		}

		public double Inclination
		{
			get { return inclination; }
			set
			{
				value %= 360; // (-360..+360)

				if (value < 0)
					value = 360 + value; // [0..360)

				inclination = value;
				setupCameraProperties();
			}
		}

		public double Azimuth
		{
			get { return azimuth; }
			set
			{
				if (value > 75)
					value = 75;

				if (value < -75)
					value = -75;

				azimuth = value;
				setupCameraProperties();
			}
		}

		int prevMouseX, prevMouseY;

		bool device_OnEvent(Event evnt)
		{
			if (evnt.Type == EventType.Mouse)
			{
				if (evnt.Mouse.Type == MouseEventType.Wheel) // zoom
				{
					Radius += evnt.Mouse.Wheel;
					return true;
				}

				if (evnt.Mouse.Type == MouseEventType.LeftDown)
				{
					prevMouseX = evnt.Mouse.X;
					prevMouseY = evnt.Mouse.Y;
					return true;
				}

				if (evnt.Mouse.Type == MouseEventType.Move && // rotation
					evnt.Mouse.IsLeftPressed())
				{
					Inclination -= (evnt.Mouse.X - prevMouseX) / 4;
					Azimuth += (evnt.Mouse.Y - prevMouseY) / 3;

					prevMouseX = evnt.Mouse.X;
					prevMouseY = evnt.Mouse.Y;

					return true;
				}
			}

			return false;
		}

		void setupCameraProperties()
		{
			const double deg2rad = Math.PI / 180;

			Vector3Df p = new Vector3Df();
			p.X = (float)(radius * Math.Cos(inclination * deg2rad) * Math.Cos(azimuth * deg2rad));
			p.Y = (float)(radius * Math.Sin(azimuth * deg2rad));
			p.Z = (float)(radius * Math.Sin(inclination * deg2rad) * Math.Cos(azimuth * deg2rad));

			camera.Position = p + target;
			camera.Target = target;
		}

		public override string ToString()
		{
			return string.Format("[SphereCamera] Radius={0} Inclination={1} Azimuth={2}", Radius, Inclination, Azimuth);
		}
	}
}
