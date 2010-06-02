#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIListBoxColor
{
	Text = EGUI_LBC_TEXT,
	SelectedText = EGUI_LBC_TEXT_HIGHLIGHT,
	Icon = EGUI_LBC_ICON,
	SelectedIcon = EGUI_LBC_ICON_HIGHLIGHT
};

} // end namespace GUI
} // end namespace IrrlichtLime