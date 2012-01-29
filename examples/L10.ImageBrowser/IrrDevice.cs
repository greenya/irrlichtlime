using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;
using IrrlichtLime.GUI;

namespace L10.ImageBrowser
{
	class IrrDevice
	{
		object locker = new object();
		bool locked = false;
		IrrlichtDevice device;

		public IrrlichtDevice Device { get { if (!IsLocked()) throw new InvalidOperationException(); else return device; } }
		public VideoDriver Driver { get { if (!IsLocked()) throw new InvalidOperationException(); else return device.VideoDriver; } }
		public VideoDriver DriverNoCheck { get { return device.VideoDriver; } } // this one used for creating software images
		public SceneManager Scene { get { return device.SceneManager; } }
		public GUIEnvironment GUI { get { return device.GUIEnvironment; } }
		public IrrlichtLime.Timer Timer { get { return device.Timer; } }
		public Randomizer Randomizer { get { return device.Randomizer; } }
		public Logger Logger { get { return device.Logger; } }

		public void Lock()
		{
			while (true)
			{
				Thread.Sleep(1);

				lock (locker)
				{
					if (locked)
						continue;

					locked = true;
					break;
				}
			}
		}

		public void Unlock()
		{
			lock (locker)
			{
				if (!locked)
					throw new InvalidOperationException();

				locked = false;
			}
		}

		public bool IsLocked()
		{
			lock (locker)
			{
				return locked;
			}
		}

		public void CreateDevice(DriverType driverType, Dimension2Di windowSize)
		{
			device = IrrlichtDevice.CreateDevice(driverType, windowSize);
		}

		public void Drop()
		{
			if (IsLocked())
				throw new InvalidOperationException();

			device.Drop();
		}
	}
}
