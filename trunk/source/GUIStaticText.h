#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public ref class GUIStaticText : GUIElement
{
public:

internal:

	GUIStaticText(gui::IGUIStaticText* guiStaticText);

	gui::IGUIStaticText* m_GUIStaticText;
};

} // end namespace GUI
} // end namespace IrrlichtLime