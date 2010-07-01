#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace GUI {

public ref class GUIImage : GUIElement
{
public:

	void SetColor(Video::Color^ color);
	void SetImage(Video::Texture^ image);

	property bool AlphaChannel { bool get(); void set(bool value); }
	property bool ScaleImage { bool get(); void set(bool value); }

internal:

	static GUIImage^ Wrap(gui::IGUIImage* ref);
	GUIImage(gui::IGUIImage* ref);

	gui::IGUIImage* m_GUIImage;
};

} // end namespace GUI
} // end namespace IrrlichtLime