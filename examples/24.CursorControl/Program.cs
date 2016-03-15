using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.GUI;
using IrrlichtLime.Video;

namespace _24.CursorControl
{
	enum TimerActionType
	{
		MouseVisible,
		MouseInvisible
	}

	/*
	Structure to allow delayed execution of some actions.
	*/
	struct TimerAction
	{
		public uint TargetTime;
		public TimerActionType Action;
	}

	class AppContext
	{
		public AppContext()
		{
			Device = null;
			InfoStatic = null;
			EventBox = null;
			CursorBox = null;
			SpriteBox = null;
			ButtonSetVisible = null;
			ButtonSetInvisible = null;
			ButtonSimulateBadFps = null;
			ButtonChangeIcon = null;
			TimerActions = new List<TimerAction>();
			SimulateBadFps = false;
			Sprites = new List<CursorSprite>();
		}

		public void Update()
		{
			if (Device == null)
				return;

			uint timeNow = Device.Timer.Time;
			for (int i = 0; i < TimerActions.Count; i++)
			{
				if (timeNow >= TimerActions[i].TargetTime)
				{
					runTimerAction(TimerActions[i]);
					TimerActions.RemoveAt(i);
				}
				else
				{
					i++;
				}
			}
		}

		private void runTimerAction(TimerAction action)
		{
			if (action.Action == TimerActionType.MouseVisible)
			{
				Device.CursorControl.Visible = true;
				ButtonSetVisible.Enabled = true;
			}
			else if (action.Action == TimerActionType.MouseInvisible)
			{
				Device.CursorControl.Visible = false;
				ButtonSetInvisible.Enabled = true;
			}
		}

		public void AddIcon(String name, CursorSprite sprite, bool addCursor = true)
		{
			SpriteBox.AddItem(name, sprite.SpriteID);
			Sprites.Add(sprite);
			if (addCursor)
			{
				Device.CursorControl.AddIcon(sprite);
				CursorBox.AddItem(name);
			}
		}

		public IrrlichtDevice Device;
		public GUIStaticText InfoStatic;
		public GUIListBox EventBox;
		public GUIListBox CursorBox;
		public GUIListBox SpriteBox;
		public GUIButton ButtonSetVisible;
		public GUIButton ButtonSetInvisible;
		public GUIButton ButtonSimulateBadFps;
		public GUIButton ButtonChangeIcon;
		public List<TimerAction> TimerActions;
		public bool SimulateBadFps;
		public List<CursorSprite> Sprites;
	}

	class Program
	{
		static bool AskUserForDriver(out DriverType driverType)
		{
			driverType = DriverType.Null;

			Console.Write("Please select the driver you want for this example:\n" +
						" (a) OpenGL\n (b) Direct3D 9.0c\n" +
						" (c) Burning's Software Renderer\n (d) Software Renderer\n" +
						" (e) NullDevice\n (otherKey) exit\n\n");

			ConsoleKeyInfo i = Console.ReadKey();

			switch (i.Key)
			{
				case ConsoleKey.A: driverType = DriverType.OpenGL; break;
				case ConsoleKey.B: driverType = DriverType.Direct3D9; break;
				case ConsoleKey.C: driverType = DriverType.BurningsVideo; break;
				case ConsoleKey.D: driverType = DriverType.Software; break;
				case ConsoleKey.E: driverType = DriverType.Null; break;
				default:
					return false;
			}

			return true;
		}

		const int delayTime = 3000;
		static AppContext Context;

		public static String PrintMouseEventName(Event e)
		{
			return e.Mouse.Type.ToString();
		}

		public static String PrintMouseState(Event e)
		{
			Event.MouseEvent mouse = e.Mouse;

			String result = "";
			result += "X: " + mouse.X + "\n";
			result += "Y: " + mouse.Y + "\n";
			result += "Wheel: " + mouse.Wheel + "\n";
			result += "Shift: " + mouse.Shift + "\n";
			result += "Control: " + mouse.Control + "\n";
			result += "ButtonStates: " + mouse.ButtonStates + "\n";
			result += "IsLeftPressed: " + mouse.IsLeftPressed() + "\n";
			result += "IsRightPressed: " + mouse.IsRightPressed() + "\n";
			result += "IsMiddlePressed: " + mouse.IsMiddlePressed() + "\n";
			result += "Event: " + PrintMouseEventName(e) + "\n";

			return result;
		}

		static bool device_OnEvent(Event e)
		{
			if (e.Type == EventType.GUI)
			{
				Event.GUIEvent ev = e.GUI;
				switch (ev.Type)
				{
					case GUIEventType.ButtonClicked:
						{
							uint timeNow = Context.Device.Timer.Time;
							TimerAction action;
							action.TargetTime = timeNow + delayTime;
							if (ev.Caller.Equals(Context.ButtonSetVisible))
							{
								action.Action = TimerActionType.MouseVisible;
								Context.TimerActions.Add(action);
								Context.ButtonSetVisible.Enabled = false;
							}
							else if (ev.Caller.Equals(Context.ButtonSetInvisible))
							{
								action.Action = TimerActionType.MouseInvisible;
								Context.TimerActions.Add(action);
								Context.ButtonSetInvisible.Enabled = false;
							}
							else if (ev.Caller.Equals(Context.ButtonSimulateBadFps))
							{
								Context.SimulateBadFps = Context.ButtonSimulateBadFps.Pressed;
							}
							else if (ev.Caller.Equals(Context.ButtonChangeIcon))
							{
								int selectedCursor = Context.CursorBox.SelectedIndex;
								int selectedSprite = Context.SpriteBox.SelectedIndex;

								if (selectedCursor >= 0 && selectedSprite >= 0)
								{
									//replace the icon:
									Context.Device.CursorControl.ChangeIcon((CursorIcon)selectedCursor, Context.Sprites[selectedSprite]);
									//show the new icon:
									Context.Device.CursorControl.ActiveIcon = (CursorIcon)selectedCursor;
								}
							}
						}
						break;

					case GUIEventType.ListBoxChanged:
					case GUIEventType.ListBoxSelectedAgain:
						{
							if (ev.Caller.Equals(Context.CursorBox))
							{
								int selected = Context.CursorBox.SelectedIndex;
								if (selected >= 0)
								{
									Context.Device.CursorControl.ActiveIcon = (CursorIcon)selected;
								}
							}
						}
						break;
					default:
						break;
				}
			}

			if (e.Type == EventType.Mouse)
			{
				Event.MouseEvent ev = e.Mouse;
				String infoText = PrintMouseState(e);
				Context.InfoStatic.Text = infoText;
				if (ev.Type != MouseEventType.Move && ev.Type != MouseEventType.Wheel) // no spam
				{
					infoText = PrintMouseEventName(e);
					Context.EventBox.InsertItem(0, infoText, -1);
				}
			}

			return false;
		}

		static int AddAnimatedIconToSpriteBank(GUISpriteBank spriteBank, VideoDriver driver, List<String> files, uint frameTime)
		{
			if (spriteBank == null || driver == null || files.Count == 0)
				return -1;

			Texture tex = driver.GetTexture(files[0]);
			if (tex != null)
			{
				NativeList<Recti> spritePositions = spriteBank.Positions;
				uint idxRect = (uint)spritePositions.Count;
				spritePositions.Add(new Recti(tex.Size));

				GUISprite sprite = new GUISprite();
				sprite.FrameTime = frameTime;

				NativeList<GUISprite> sprites = spriteBank.Sprites;
				uint startIdx = spriteBank.TextureCount;
				for (int f = 0; f < files.Count; f++)
				{
					tex = driver.GetTexture(files[f]);
					if (tex != null)
					{
						spriteBank.AddTexture(tex);
						GUISpriteFrame frame = new GUISpriteFrame();
						frame.RectNumber = idxRect;
						frame.TextureNumber = startIdx + (uint)f;
						sprite.Frames.Add(frame);
					}
				}

				sprites.Add(sprite);
				return sprites.Count - 1;
			}

			return -1;
		}

		static int AddAnimatedIconToSpriteBank(GUISpriteBank spriteBank, VideoDriver driver, String file, List<Recti> rects, uint frameTime)
		{
			if (spriteBank == null || driver == null || file == null)
				return -1;

			Texture tex = driver.GetTexture(file);
			if (tex != null)
			{
				NativeList<Recti> spritePositions = spriteBank.Positions;
				uint idxRect = (uint)spritePositions.Count;
				uint idxTex = spriteBank.TextureCount;
				spriteBank.AddTexture(tex);
				GUISprite sprite = new GUISprite();
				sprite.FrameTime = frameTime;
				NativeList<GUISprite> sprites = spriteBank.Sprites;
				for (int i = 0; i < rects.Count; i++)
				{
					spritePositions.Add(rects[i]);

					GUISpriteFrame frame = new GUISpriteFrame();
					frame.RectNumber = idxRect + (uint)i;
					frame.TextureNumber = idxTex;
					sprite.Frames.Add(frame);
				}

				sprites.Add(sprite);
				return sprites.Count - 1;
			}

			return -1;
		}

		static int AddIconToSpriteBank(GUISpriteBank spriteBank, VideoDriver driver, String file, Recti rect)
		{
			if (spriteBank == null || driver == null)
				return -1;

			Texture tex = driver.GetTexture(file);
			if (tex != null)
			{
				NativeList<Recti> spritePositions = spriteBank.Positions;
				spritePositions.Add(rect);
				NativeList<GUISprite> sprites = spriteBank.Sprites;
				spriteBank.AddTexture(tex);

				GUISpriteFrame frame = new GUISpriteFrame();
				frame.RectNumber = (uint)spritePositions.Count - 1;
				frame.TextureNumber = spriteBank.TextureCount - 1;

				GUISprite sprite = new GUISprite();
				sprite.FrameTime = 0;
				sprite.Frames.Add(frame);

				sprites.Add(sprite);

				return sprites.Count - 1;
			}

			return -1;
		}

		static int Main(string[] args)
		{
			DriverType driverType;
			if (!AskUserForDriver(out driverType))
				return 1;

			IrrlichtDevice device = IrrlichtDevice.CreateDevice(driverType, new Dimension2Di(640, 480));
			if (device == null)
				return 1;

			device.SetWindowResizable(true);
			device.SetWindowCaption("Cursor control - Irrlicht engine tutorial");
			VideoDriver driver = device.VideoDriver;
			GUIEnvironment env = device.GUIEnvironment;

			GUISpriteBank SpriteBankIcons;

			Context = new AppContext();
			Context.Device = device;

			Recti rectInfoStatic = new Recti(10, 10, 200, 200);
			env.AddStaticText("Cursor state information", rectInfoStatic, true, true);
			rectInfoStatic.UpperLeftCorner += new Vector2Di(0, 15);
			Context.InfoStatic = env.AddStaticText("", rectInfoStatic, true, true);

			Recti rectEventBox = new Recti(10, 210, 200, 400);
			env.AddStaticText("click events (new on top)", rectEventBox, true, true);
			rectEventBox.UpperLeftCorner += new Vector2Di(0, 15);
			Context.EventBox = env.AddListBox(rectEventBox);

			Recti rectCursorBox = new Recti(210, 10, 400, 250);
			env.AddStaticText("cursors, click to set the active one", rectCursorBox, true, true);
			rectCursorBox.UpperLeftCorner += new Vector2Di(0, 15);
			Context.CursorBox = env.AddListBox(rectCursorBox);

			Recti rectSpriteBox = new Recti(210, 260, 400, 400);
			env.AddStaticText("sprites", rectSpriteBox, true, true);
			rectSpriteBox.UpperLeftCorner += new Vector2Di(0, 15);
			Context.SpriteBox = env.AddListBox(rectSpriteBox);

			Context.ButtonSetVisible = env.AddButton(new Recti(410, 20, 560, 40), null, -1, "set visible (delayed)");
			Context.ButtonSetInvisible = env.AddButton(new Recti(410, 50, 560, 70), null, -1, "set invisible (delayed)");
			Context.ButtonSimulateBadFps = env.AddButton(new Recti(410, 80, 560, 100), null, -1, "simulate bad FPS");
			Context.ButtonSimulateBadFps.PushButton = true;
			Context.ButtonChangeIcon = env.AddButton(new Recti(410, 140, 560, 160), null, -1, "replace cursor icon\n(cursor+sprite must be selected)");

			String[] cursorIconNames = System.Enum.GetNames(typeof(CursorIcon));
			for (int i = 0; i < cursorIconNames.Length; i++)
				Context.CursorBox.AddItem(cursorIconNames[i]);

			SpriteBankIcons = env.AddEmptySpriteBank("cursor_icons");
			Context.SpriteBox.SetSpriteBank(SpriteBankIcons);

			const String mediaPath = "../../media/";

			List<String> files = new List<string>();
			files.Add(mediaPath + "icon_crosshairs16x16bw1.png");
			files.Add(mediaPath + "icon_crosshairs16x16bw2.png");
			files.Add(mediaPath + "icon_crosshairs16x16bw3.png");
			files.Add(mediaPath + "icon_crosshairs16x16bw3.png");
			files.Add(mediaPath + "icon_crosshairs16x16bw2.png");

			CursorSprite spriteBw = new CursorSprite();
			spriteBw.SpriteID = AddAnimatedIconToSpriteBank(SpriteBankIcons, driver, files, 200);
			spriteBw.SpriteBank = SpriteBankIcons;
			spriteBw.HotSpot = new Vector2Di(7, 7);
			Context.AddIcon("crosshair_bw", spriteBw);

			List<Recti> iconRects = new List<Recti>();
			iconRects.Add(new Recti(0, 0, 16, 16));
			iconRects.Add(new Recti(16, 0, 32, 16));
			iconRects.Add(new Recti(0, 16, 16, 32));
			iconRects.Add(new Recti(0, 16, 16, 32));
			iconRects.Add(new Recti(16, 0, 32, 16));
			CursorSprite spriteCol = new CursorSprite();
			spriteCol.SpriteID = AddAnimatedIconToSpriteBank(SpriteBankIcons, driver, mediaPath + "icon_crosshairs16x16col.png", iconRects, 200);
			spriteCol.HotSpot = new Vector2Di(7, 7);
			spriteCol.SpriteBank = SpriteBankIcons;
			Context.AddIcon("crosshair_colored", spriteCol);

			Recti rectIcon;
			CursorSprite spriteNonAnimated = new CursorSprite(SpriteBankIcons, 0, new Vector2Di(7,7));

			rectIcon = new Recti(0, 0, 16, 16);
			spriteNonAnimated.SpriteID = AddIconToSpriteBank(SpriteBankIcons, driver, mediaPath + "icon_crosshairs16x16col.png", rectIcon);
			Context.AddIcon("crosshair_col1", spriteNonAnimated, false);

			rectIcon = new Recti(16, 0, 32, 16);
			spriteNonAnimated.SpriteID = AddIconToSpriteBank(SpriteBankIcons, driver, mediaPath + "icon_crosshairs16x16col.png", rectIcon);
			Context.AddIcon("crosshair_col2", spriteNonAnimated, false);

			rectIcon = new Recti(0, 16, 16, 32);
			spriteNonAnimated.SpriteID = AddIconToSpriteBank(SpriteBankIcons, driver, mediaPath + "icon_crosshairs16x16col.png", rectIcon);
			Context.AddIcon("crosshair_col3", spriteNonAnimated, false);

			device.OnEvent += device_OnEvent;

			while (device.Run() && driver != null)
			{
				uint realTimeNow = device.Timer.Time;
				Context.Update();

				driver.BeginScene(ClearBufferFlag.Color | ClearBufferFlag.Depth, new Color(200, 200, 200, 0));
				
				env.DrawAll();

				if (Context.SpriteBox != null)
				{
					int selectedSprite = Context.SpriteBox.SelectedIndex;
					if (selectedSprite >= 0 && Context.Sprites[selectedSprite].SpriteID >= 0)
					{
						SpriteBankIcons.Draw2DSprite((uint)Context.Sprites[selectedSprite].SpriteID, new Vector2Di(580, 140), null, Color.OpaqueWhite, 0, realTimeNow);
					}
				}
				driver.EndScene();

				if (Context.SimulateBadFps)
				{
					device.Sleep(500);
				}
				else
				{
					device.Sleep(10);
				}
			}

			device.Drop();

			return 0;
		}
	}
}
