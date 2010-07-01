#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

ref class GUIFont;

public ref class GUIStaticText : GUIElement
{
public:

	void SetBackgroundColor(Video::Color^ color);
	void SetDrawBackground(bool draw);
	void SetDrawBorder(bool draw);
	void SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical);

	property Video::Color^ OverrideColor { Video::Color^ get(); void set(Video::Color^ value); }
	property bool OverrideColorEnabled { bool get(); void set(bool value); }
	property GUIFont^ OverrideFont { GUIFont^ get(); void set(GUIFont^ value); }
	property int TextHeight { int get(); }
	property int TextWidth { int get(); }
	property bool WordWrap { bool get(); void set(bool value); }

internal:

	static GUIStaticText^ Wrap(gui::IGUIStaticText* ref);
	GUIStaticText(gui::IGUIStaticText* ref);

	gui::IGUIStaticText* m_GUIStaticText;
};

} // end namespace GUI
} // end namespace IrrlichtLime