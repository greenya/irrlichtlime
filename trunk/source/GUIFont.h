#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class GUIFont : ReferenceCounted
{
public:

	void Draw(String^ text, Recti^ position, Video::Coloru^ color, bool hcenter, bool vcenter, Recti^ clip);
	void Draw(String^ text, Recti^ position, Video::Coloru^ color, bool hcenter, bool vcenter);
	void Draw(String^ text, Recti^ position, Video::Coloru^ color, bool hcenter);
	void Draw(String^ text, Recti^ position, Video::Coloru^ color);

	int GetCharacterFromPos(String^ text, int pixel_x);
	Dimension2Du^ GetDimension(String^ text);
	int GetKerningWidth(Char thisLetter, Char previousLetter);
	int GetKerningWidth(Char thisLetter);
	void SetInvisibleCharacters(String^ s);

	property int KerningHeight { int get(); void set(int value); }
	property int KerningWidth { int get(); void set(int value); }
	property GUIFontType Type { GUIFontType get(); }

	virtual String^ ToString() override;

internal:

	static GUIFont^ Wrap(gui::IGUIFont* ref);
	GUIFont(gui::IGUIFont* ref);

	gui::IGUIFont* m_GUIFont;
};

} // end namespace GUI
} // end namespace IrrlichtLime