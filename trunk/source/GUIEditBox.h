#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

ref class GUIFont;

public ref class GUIEditBox : GUIElement
{
public:

	void SetDrawBorder(bool draw);
	void SetOverrideColor(bool enable, Video::Color^ color);
	void SetOverrideColor(bool enable);
	void SetOverrideFont(GUIFont^ font);
	void SetPasswordChar(Char x);
	void SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical);

	property bool AutoScroll { bool get(); void set(bool value); }
	property int MaxLength { int get(); void set(int value); }
	property bool MultiLine { bool get(); void set(bool value); }
	property bool PasswordBox { bool get(); void set(bool value); }
	property Dimension2Di^ TextDimension { Dimension2Di^ get(); }
	property bool WordWrap { bool get(); void set(bool value); }

internal:

	static GUIEditBox^ Wrap(gui::IGUIEditBox* ref);
	GUIEditBox(gui::IGUIEditBox* ref);

	gui::IGUIEditBox* m_GUIEditBox;
};

} // end namespace GUI
} // end namespace IrrlichtLime