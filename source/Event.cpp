#include "stdafx.h"
#include "Event.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

Event::Event(const SEvent& other)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent(other);
}

Event::Event(IrrlichtLime::GUI::GUIEventType type, IrrlichtLime::GUI::GUIElement^ caller, IrrlichtLime::GUI::GUIElement^ element)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_GUI_EVENT;

	m_NativeValue->GUIEvent.EventType = (EGUI_EVENT_TYPE)type;
	m_NativeValue->GUIEvent.Caller = LIME_SAFEREF(caller, m_GUIElement);
	m_NativeValue->GUIEvent.Element = LIME_SAFEREF(element, m_GUIElement);
}

Event::Event(IrrlichtLime::GUI::GUIEventType type, IrrlichtLime::GUI::GUIElement^ caller)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_GUI_EVENT;

	m_NativeValue->GUIEvent.EventType = (EGUI_EVENT_TYPE)type;
	m_NativeValue->GUIEvent.Caller = LIME_SAFEREF(caller, m_GUIElement);
	m_NativeValue->GUIEvent.Element = nullptr;
}

Event::Event(MouseEventType type, int x, int y, float wheel, unsigned int buttonStates, bool shift, bool control)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_MOUSE_INPUT_EVENT;

	m_NativeValue->MouseInput.Event = (EMOUSE_INPUT_EVENT)type;
	m_NativeValue->MouseInput.X = x;
	m_NativeValue->MouseInput.Y = y;
	m_NativeValue->MouseInput.Wheel = wheel;
	m_NativeValue->MouseInput.ButtonStates = buttonStates;
	m_NativeValue->MouseInput.Shift = shift;
	m_NativeValue->MouseInput.Control = control;
}

Event::Event(MouseEventType type, int x, int y, float wheel, unsigned int buttonStates)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_MOUSE_INPUT_EVENT;

	m_NativeValue->MouseInput.Event = (EMOUSE_INPUT_EVENT)type;
	m_NativeValue->MouseInput.X = x;
	m_NativeValue->MouseInput.Y = y;
	m_NativeValue->MouseInput.Wheel = wheel;
	m_NativeValue->MouseInput.ButtonStates = buttonStates;
	m_NativeValue->MouseInput.Shift = false;
	m_NativeValue->MouseInput.Control = false;
}

Event::Event(MouseEventType type, int x, int y, float wheel)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_MOUSE_INPUT_EVENT;

	m_NativeValue->MouseInput.Event = (EMOUSE_INPUT_EVENT)type;
	m_NativeValue->MouseInput.X = x;
	m_NativeValue->MouseInput.Y = y;
	m_NativeValue->MouseInput.Wheel = wheel;
	m_NativeValue->MouseInput.ButtonStates = 0;
	m_NativeValue->MouseInput.Shift = false;
	m_NativeValue->MouseInput.Control = false;
}

Event::Event(MouseEventType type, int x, int y)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_MOUSE_INPUT_EVENT;

	m_NativeValue->MouseInput.Event = (EMOUSE_INPUT_EVENT)type;
	m_NativeValue->MouseInput.X = x;
	m_NativeValue->MouseInput.Y = y;
	m_NativeValue->MouseInput.Wheel = 0.0f;
	m_NativeValue->MouseInput.ButtonStates = 0;
	m_NativeValue->MouseInput.Shift = false;
	m_NativeValue->MouseInput.Control = false;
}

Event::Event(System::Char ch, KeyCode key, bool pressedDown, bool shift, bool control)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_KEY_INPUT_EVENT;

	m_NativeValue->KeyInput.Char = ch;
	m_NativeValue->KeyInput.Key = (EKEY_CODE)key;
	m_NativeValue->KeyInput.PressedDown = pressedDown;
	m_NativeValue->KeyInput.Shift = shift;
	m_NativeValue->KeyInput.Control = control;
}

Event::Event(System::Char ch, KeyCode key, bool pressedDown)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_KEY_INPUT_EVENT;

	m_NativeValue->KeyInput.Char = ch;
	m_NativeValue->KeyInput.Key = (EKEY_CODE)key;
	m_NativeValue->KeyInput.PressedDown = pressedDown;
	m_NativeValue->KeyInput.Shift = false;
	m_NativeValue->KeyInput.Control = false;
}

Event::Event(unsigned __int8 joystick, array<__int16>^ axis, unsigned __int16 pov, unsigned int buttonStates)
	: Lime::NativeValue<SEvent>(true)
{
	LIME_ASSERT(axis != nullptr);
	LIME_ASSERT(axis->Length == Event::JoystickEvent::AxisCount);

	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_JOYSTICK_INPUT_EVENT;

	m_NativeValue->JoystickEvent.Joystick = joystick;
	
	for (int i = 0; i < Event::JoystickEvent::AxisCount; i++)
		m_NativeValue->JoystickEvent.Axis[i] = axis[i];
	
	m_NativeValue->JoystickEvent.POV = pov;
	m_NativeValue->JoystickEvent.ButtonStates = buttonStates;
}

Event::Event(unsigned __int8 joystick, array<__int16>^ axis, unsigned __int16 pov)
	: Lime::NativeValue<SEvent>(true)
{
	LIME_ASSERT(axis != nullptr);
	LIME_ASSERT(axis->Length == Event::JoystickEvent::AxisCount);

	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_JOYSTICK_INPUT_EVENT;

	m_NativeValue->JoystickEvent.Joystick = joystick;
	
	for (int i = 0; i < Event::JoystickEvent::AxisCount; i++)
		m_NativeValue->JoystickEvent.Axis[i] = axis[i];
	
	m_NativeValue->JoystickEvent.POV = pov;
	m_NativeValue->JoystickEvent.ButtonStates = 0;
}

Event::Event(String^ logText, LogLevel logLevel)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_LOG_TEXT_EVENT;

	m_NativeValue->LogEvent.Text = Lime::StringToStringC(logText).c_str();
	m_NativeValue->LogEvent.Level = (ELOG_LEVEL)logLevel;
}

Event::Event(String^ logText)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_LOG_TEXT_EVENT;

	m_NativeValue->LogEvent.Text = Lime::StringToStringC(logText).c_str();
	m_NativeValue->LogEvent.Level = ELL_NONE;
}

Event::Event(int userData1, int userData2)
	: Lime::NativeValue<SEvent>(true)
{
	m_NativeValue = new SEvent();
	m_NativeValue->EventType = EET_USER_EVENT;

	m_NativeValue->UserEvent.UserData1 = userData1;
	m_NativeValue->UserEvent.UserData2 = userData2;
}

Event::GUIEvent Event::GUI::get()
{
	LIME_ASSERT(Type == EventType::GUI);

	// !!! patch for currently present bug (http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=38669) {
	switch (m_NativeValue->GUIEvent.EventType)
	{
	case gui::EGET_ELEMENT_LEFT :
	case gui::EGET_TABLE_HEADER_CHANGED :
	case gui::EGET_TABLE_CHANGED :
	case gui::EGET_TABLE_SELECTED_AGAIN :
	case gui::EGET_TREEVIEW_NODE_DESELECT :
	case gui::EGET_TREEVIEW_NODE_SELECT :
	case gui::EGET_TREEVIEW_NODE_EXPAND :
	case gui::EGET_TREEVIEW_NODE_COLLAPS :
		m_NativeValue->GUIEvent.Element = nullptr;
		break;
	}
	// }

	return Event::GUIEvent(m_NativeValue->GUIEvent);
}

Event::JoystickEvent Event::Joystick::get()
{
	LIME_ASSERT(Type == EventType::Joystick);
	return Event::JoystickEvent(m_NativeValue->JoystickEvent);
}

Event::KeyEvent Event::Key::get()
{
	LIME_ASSERT(Type == EventType::Key);
	return Event::KeyEvent(m_NativeValue->KeyInput);
}

Event::LogEvent Event::Log::get()
{
	LIME_ASSERT(Type == EventType::Log);
	return Event::LogEvent(m_NativeValue->LogEvent);
}

Event::MouseEvent Event::Mouse::get()
{
	LIME_ASSERT(Type == EventType::Mouse);
	return Event::MouseEvent(m_NativeValue->MouseInput);
}

Event::UserEvent Event::User::get()
{
	LIME_ASSERT(Type == EventType::User);
	return Event::UserEvent(m_NativeValue->UserEvent);
}

EventType Event::Type::get()
{
	return (EventType)m_NativeValue->EventType;
}

String^ Event::ToString()
{
	return String::Format("Event: Type={0}", Type);
}

} // end namespace IrrlichtLime