#pragma once

#include "stdafx.h"
#include "GUIFont.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

ref class GUISpriteBank;

public ref class GUIFontBitmap : GUIFont
{
public:

	int GetKerningWidth(Nullable<Char> thisLetter, Nullable<Char> previousLetter);
	int GetKerningWidth(Nullable<Char> thisLetter);
	int GetKerningWidth();

	unsigned int GetSpriteNoFromChar(Char c);

	property GUISpriteBank^ SpriteBank { GUISpriteBank^ get(); }
	
internal:

	static GUIFontBitmap^ Wrap(gui::IGUIFontBitmap* ref);
	GUIFontBitmap(gui::IGUIFontBitmap* ref);

	gui::IGUIFontBitmap* m_GUIFontBitmap;
};

} // end namespace GUI
} // end namespace IrrlichtLime