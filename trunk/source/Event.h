#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public ref class Event : Lime::NativeValue<SEvent>
{
public:

	value class GUIEvent
	{
	public:
		IrrlichtLime::GUI::GUIElement^ Caller;
		IrrlichtLime::GUI::GUIElement^ Element;
		IrrlichtLime::GUI::GUIEventType Type;
	internal:
		GUIEvent(const SEvent::SGUIEvent& v)
			: Caller(IrrlichtLime::GUI::GUIElement::Wrap(v.Caller))
			, Element(IrrlichtLime::GUI::GUIElement::Wrap(v.Element))
			, Type((IrrlichtLime::GUI::GUIEventType)v.EventType) {}
	};

	value class MouseEvent
	{
	public:
		int X;
		int Y;
		float Wheel;
		bool Shift;
		bool Control;
		unsigned int ButtonStates;
		MouseEventType Type;
		bool IsLeftPressed() { return 0 != (ButtonStates & EMBSM_LEFT); }
		bool IsRightPressed() { return 0 != (ButtonStates & EMBSM_RIGHT); }
		bool IsMiddlePressed() { return 0 != (ButtonStates & EMBSM_MIDDLE); }
	internal:
		MouseEvent(const SEvent::SMouseInput& v)
			: X(v.X)
			, Y(v.Y)
			, Wheel(v.Wheel)
			, Shift(v.Shift)
			, Control(v.Control)
			, ButtonStates(v.ButtonStates)
			, Type((MouseEventType)v.Event) {}
	};

	value class KeyEvent
	{
	public:
		System::Char Char;
		KeyCode Key;
		bool PressedDown;
		bool Shift;
		bool Control;
	internal:
		KeyEvent(const SEvent::SKeyInput& v)
			: Char(v.Char)
			, Key((KeyCode)v.Key)
			, PressedDown(v.PressedDown)
			, Shift(v.Shift)
			, Control(v.Control) {}
	};

	value class JoystickEvent
	{
	public:
		static property int ButtonCount { int get() { return SEvent::SJoystickEvent::NUMBER_OF_BUTTONS; } }
		static property int AxisCount { int get() { return SEvent::SJoystickEvent::NUMBER_OF_AXES; } }

		unsigned int ButtonStates;
		array<__int16>^ Axis;
		unsigned __int16 POV;
		unsigned __int8 Joystick;
		bool IsButtonPressed(int button)
		{
			LIME_ASSERT(button >= 0 && button < ButtonCount);
			return (ButtonStates & (1 << (unsigned int)button)) ? true : false;
		}
	internal:
		JoystickEvent(const SEvent::SJoystickEvent& v)
			: ButtonStates(v.ButtonStates)
			, Axis(gcnew array<__int16>(AxisCount))
			, POV(v.POV)
			, Joystick(v.Joystick)
		{
			for (int i = 0; i < AxisCount; i++)
				Axis[i] = v.Axis[i];
		}
	};

	value class LogEvent
	{
	public:
		String^ Text;
		LogLevel Level;
	internal:
		LogEvent(const SEvent::SLogEvent& v)
			: Text(gcnew String(v.Text))
			, Level((LogLevel)v.Level) {}
	};

	value class UserEvent
	{
	public:
		int UserData1;
		int UserData2;
	internal:
		UserEvent(const SEvent::SUserEvent& v)
			: UserData1(v.UserData1)
			, UserData2(v.UserData2) {}
	};

	Event(IrrlichtLime::GUI::GUIEventType type, IrrlichtLime::GUI::GUIElement^ caller, IrrlichtLime::GUI::GUIElement^ element);
	Event(IrrlichtLime::GUI::GUIEventType type, IrrlichtLime::GUI::GUIElement^ caller);

	Event(MouseEventType type, int x, int y, float wheel, unsigned int buttonStates, bool shift, bool control);
	Event(MouseEventType type, int x, int y, float wheel, unsigned int buttonStates);
	Event(MouseEventType type, int x, int y, float wheel);
	Event(MouseEventType type, int x, int y);

	Event(System::Char ch, KeyCode key, bool pressedDown, bool shift, bool control);
	Event(System::Char ch, KeyCode key, bool pressedDown);

	Event(unsigned __int8 joystick, array<__int16>^ axis, unsigned __int16 pov, unsigned int buttonStates);
	Event(unsigned __int8 joystick, array<__int16>^ axis, unsigned __int16 pov);

	Event(String^ logText, LogLevel logLevel);
	Event(String^ logText);

	Event(int userData1, int userData2);

	property GUIEvent GUI { GUIEvent get(); }
	property JoystickEvent Joystick { JoystickEvent get(); }
	property KeyEvent Key { KeyEvent get(); }
	property LogEvent Log { LogEvent get(); }
	property MouseEvent Mouse { MouseEvent get(); }
	property UserEvent User { UserEvent get(); }
	property EventType Type { EventType get(); }

	virtual String^ ToString() override;

internal:

	Event(const SEvent& other);
};

} // end namespace IrrlichtLime