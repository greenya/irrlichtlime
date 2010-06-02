#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class GUIElement : IO::AttributeExchangingObject
{
public:

	GUIElement^ GetElementFromID(int id, bool searchchildren);
	GUIElement^ GetElementFromID(int id);
	GUIElement^ GetElementFromPoint(Vector2Di^ point);

	bool IsMyChild(GUIElement^ child);
	bool IsPointInside(Vector2Di^ point);

	property Recti^ AbsoluteClippingRect { Recti^ get(); }
	property Recti^ AbsolutePosition { Recti^ get(); }
	property bool Enabled { bool get(); void set(bool value); }
	property int ID { int get(); void set(int value); }
	property bool NotClipped { bool get(); void set(bool value); }
	property Recti^ RelativePosition { Recti^ get(); void set(Recti^ value); }
	property int TabOrder { int get(); void set(int value); }
	property bool TabStop { bool get(); void set(bool value); }
	property String^ Text { String^ get(); void set(String^ value); }
	property String^ ToolTipText { String^ get(); void set(String^ value); }
	property GUIElementType Type { GUIElementType get(); }
	property bool Visible { bool get(); void set(bool value); }

	virtual String^ ToString() override;

internal:

	static GUIElement^ Wrap(gui::IGUIElement* ref);
	GUIElement(gui::IGUIElement* ref);

	gui::IGUIElement* m_GUIElement;
};

} // end namespace GUI
} // end namespace IrrlichtLime