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

	void AddChild(GUIElement^ child);

	bool BringToFront(GUIElement^ child);

	void Draw();

	GUIElement^ GetElementFromID(int id, bool searchchildren);
	GUIElement^ GetElementFromID(int id);
	GUIElement^ GetElementFromPoint(Vector2Di^ point);

	bool GetNextElement(int startOrder, bool reverse, bool group, [Out] GUIElement^% first, [Out] GUIElement^% closest, bool includeInvisible);
	bool GetNextElement(int startOrder, bool reverse, bool group, [Out] GUIElement^% first, [Out] GUIElement^% closest);

	bool IsMyChild(GUIElement^ child);
	bool IsPointInside(Vector2Di^ point);

	void Move(Vector2Di^ absoluteMovement);

	void Remove();
	void RemoveChild(GUIElement^ child);

	void SetAlignment(GUIAlignment left, GUIAlignment right, GUIAlignment top, GUIAlignment bottom);

	void SetMaxSize(Dimension2Du^ size);
	void SetMinSize(Dimension2Du^ size);

	void SetRelativePositionProportional(Rectf^ relativePosition);

	void UpdateAbsolutePosition();

	property Recti^ AbsoluteClippingRect { Recti^ get(); }
	property Recti^ AbsolutePosition { Recti^ get(); }
	property List<GUIElement^>^ ChildList { List<GUIElement^>^ get(); }
	property bool Clipped { bool get(); void set(bool value); }
	property bool Enabled { bool get(); void set(bool value); }
	property int ID { int get(); void set(int value); }
	property GUIElement^ Parent { GUIElement^ get(); }
	property Recti^ RelativePosition { Recti^ get(); void set(Recti^ value); }
	property bool SubElement { bool get(); void set(bool value); }
	property bool TabGroup { bool get(); void set(bool value); }
	property GUIElement^ TabGroupElement { GUIElement^ get(); }
	property int TabOrder { int get(); void set(int value); }
	property bool TabStop { bool get(); void set(bool value); }
	property String^ Text { String^ get(); void set(String^ value); }
	property String^ ToolTipText { String^ get(); void set(String^ value); }
	property GUIElementType Type { GUIElementType get(); }
	property String^ TypeName { String^ get(); }
	property bool Visible { bool get(); void set(bool value); }

	virtual String^ ToString() override;

internal:

	static GUIElement^ Wrap(gui::IGUIElement* ref);
	GUIElement(gui::IGUIElement* ref);

	gui::IGUIElement* m_GUIElement;
};

} // end namespace GUI
} // end namespace IrrlichtLime