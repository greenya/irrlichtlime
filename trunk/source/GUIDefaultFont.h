#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIDefaultFont
{
	Default = EGDF_DEFAULT,
	Button = EGDF_BUTTON,
	Window = EGDF_WINDOW,
	Menu = EGDF_MENU,
	Tooltip = EGDF_TOOLTIP
};

} // end namespace GUI
} // end namespace IrrlichtLime