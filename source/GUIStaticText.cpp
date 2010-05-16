#pragma once

#include "stdafx.h"
#include "GUIElement.h"
#include "GUIStaticText.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIStaticText::GUIStaticText(gui::IGUIStaticText* guiStaticText)
	: GUIElement(guiStaticText)
{
	LIME_ASSERT(guiStaticText != nullptr);
	m_GUIStaticText = guiStaticText;
}

} // end namespace GUI
} // end namespace IrrlichtLime