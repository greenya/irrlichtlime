using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using IrrlichtLime;
using IrrlichtLime.Scene;
using IrrlichtLime.Video;
using IrrlichtLime.Core;

namespace L10.ImageBrowser
{
	class TextureManager
	{
		IrrDevice irrDevice;
		Texture noPreviewTexture;

		Thread[] threads;
		Queue<ThreadCommand> threadCommands;
		List<string> loadedTextures;

		public delegate void TextureLoadedDelegate(SceneNode node, Texture texture, Dimension2Di sourceDimension);
		public event TextureLoadedDelegate OnTextureLoaded;

		public TextureManager(IrrDevice irrDevice)
		{
			this.irrDevice = irrDevice;

			threadCommands = new Queue<ThreadCommand>();
			loadedTextures = new List<string>();

			// generate "no preview" texture

			int h = 256;
			Image i = irrDevice.DriverNoCheck.CreateImage(ColorFormat.A8R8G8B8, new Dimension2Di(h));
			i.Fill(new Color(0x112233));
			for (int a = 0; a < h; a++)
			{
				i.SetPixel(a, 0, new Color(0x557799));
				i.SetPixel(a, h - 1, new Color(0x557799));
				i.SetPixel(0, a, new Color(0x557799));
				i.SetPixel(h - 1, a, new Color(0x557799));

				if (a > 16 && a < h - 16)
				{
					i.SetPixel(a, a, new Color(0x557799));
					i.SetPixel(h - a - 1, a, new Color(0x557799));
				}
			}

			irrDevice.Lock();
			noPreviewTexture = irrDevice.Driver.AddTexture("NoPreviewTexture", i);
			irrDevice.Unlock();

			i.Drop();
		}

		public void Start(int threadCount)
		{
			threads = new Thread[threadCount];
			for (int i = 0; i < threadCount; i++)
			{
				threads[i] = new Thread(thread_Main);
				threads[i].Name = GetType().Name + "/Thread#" + (i + 1);
				threads[i].Start();
			}
		}

		public void Stop()
		{
			if (threads == null)
				return;

			addThreadCommand(ThreadCommandType.Stop, false);
			foreach (Thread t in threads)
				t.Join();

			System.Diagnostics.Debug.Assert(threadCommands.Count == 1);
			threadCommands.Dequeue();
		}

		public void LoadTexture(SceneNode node, string path, Dimension2Di size, bool topPriority = false)
		{
			node.Grab();
			addThreadCommand(ThreadCommandType.LoadTexture, topPriority, node, path, size);
		}

		public void UnloadTexture(string path)
		{
			addThreadCommand(ThreadCommandType.UnloadTexture, false, path);
		}

		public void EnqueueUnloadingOfAllLoadedTextures()
		{
			lock (loadedTextures)
			{
				foreach (string t in loadedTextures)
					addThreadCommand(ThreadCommandType.UnloadTexture, false, t);

				loadedTextures.Clear();
			}
		}

		public int GetCommandQueueLength()
		{
			lock (threadCommands)
			{
				return threadCommands.Count;
			}
		}

		void addThreadCommand(ThreadCommandType command, bool topPriority, params object[] args)
		{
			ThreadCommand cmd = new ThreadCommand();
			cmd.Type = command;
			cmd.Params = args;

			lock (threadCommands)
			{
				if (cmd.Type == ThreadCommandType.Stop)
				{
					foreach (ThreadCommand c in threadCommands)
						if (c.Type == ThreadCommandType.LoadTexture)
							(c.Params[0] as SceneNode).Drop();

					threadCommands.Clear();
				}

				if (topPriority && threadCommands.Count > 0)
				{
					ThreadCommand[] a = threadCommands.ToArray();
					threadCommands.Clear();
					threadCommands.Enqueue(cmd);
					for (int i = 0; i < a.Length; i++)
						threadCommands.Enqueue(a[i]);
				}
				else
				{
					threadCommands.Enqueue(cmd);
				}
			}
		}

		void thread_Main()
		{
			irrDevice.Logger.Log(Thread.CurrentThread.Name, "Started", LogLevel.Information);

			while (true)
			{
				ThreadCommand cmd = thread_GetNextCommand();

				if (cmd == null)
				{
					Thread.Sleep(1);
					continue;
				}

				switch (cmd.Type)
				{
					case ThreadCommandType.Stop:
						irrDevice.Logger.Log(Thread.CurrentThread.Name, "Finished", LogLevel.Information);
						return;

					case ThreadCommandType.LoadTexture:
						irrDevice.Logger.Log(Thread.CurrentThread.Name, "Loading " + (cmd.Params[1] as string) + "|" + (cmd.Params[2] as Dimension2Di), LogLevel.Information);
						thread_LoadTexture(cmd.Params[0] as SceneNode, cmd.Params[1] as string, cmd.Params[2] as Dimension2Di);
						break;

					case ThreadCommandType.UnloadTexture:
						irrDevice.Logger.Log(Thread.CurrentThread.Name, "Unloading " + (cmd.Params[0] as string), LogLevel.Information);
						thread_UnloadTexture(cmd.Params[0] as string);
						break;
				}
			}
		}

		ThreadCommand thread_GetNextCommand()
		{
			ThreadCommand cmd = null;

			lock (threadCommands)
			{
				if (threadCommands.Count > 0)
				{
					// We do first Peek and only then Dequeue, because we do not want Stop command to be processed only by one thread (so other will not get this command)

					cmd = threadCommands.Peek();

					if (cmd.Type != ThreadCommandType.Stop)
						threadCommands.Dequeue();
				}
			}

			return cmd;
		}

		void thread_LoadTexture(SceneNode node, string path, Dimension2Di size)
		{
			Texture t;
			Dimension2Di si;
			Image i = irrDevice.DriverNoCheck.CreateImage(path);

			if (i != null)
			{
				Image j = irrDevice.DriverNoCheck.CreateImage(ColorFormat.A8R8G8B8, size);
				i.CopyToScaling(j);

				irrDevice.Lock();
				t = irrDevice.Driver.AddTexture(path + "|" + size.ToString(), j);
				irrDevice.Unlock();

				si = i.Dimension;

				i.Drop();
				j.Drop();

				lock (loadedTextures)
				{
					loadedTextures.Add(t.Name.Path);
				}
			}
			else
			{
				t = noPreviewTexture;
				si = noPreviewTexture.Size;
			}

			irrDevice.Lock();
			node.SetMaterialTexture(0, t);
			irrDevice.Unlock();

			if (OnTextureLoaded != null)
				OnTextureLoaded(node, t, si);

			node.Drop();
		}

		void thread_UnloadTexture(string path)
		{
			irrDevice.Lock();

			Texture t = irrDevice.Driver.FindTexture(path);
			if (t != null)
				irrDevice.Driver.RemoveTexture(t);

			irrDevice.Unlock();
		}

		enum ThreadCommandType
		{
			Stop, // Params = null
			LoadTexture, // Params = [SceneNode] the node witch will get SetMaterialTexture() call, [string] path to the texture, [Dimension2Di] resize loaded texture to this size
			UnloadTexture // Params = [string] name of the texture
		}

		class ThreadCommand
		{
			public ThreadCommandType Type;
			public object[] Params;
		}
	}
}
