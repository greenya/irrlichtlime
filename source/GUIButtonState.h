#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIButtonState
{
	ButtonUp = EGBS_BUTTON_UP,
	ButtonDown = EGBS_BUTTON_DOWN,
	MouseOver = EGBS_BUTTON_MOUSE_OVER,
	MouseOff = EGBS_BUTTON_MOUSE_OFF,
	Focused = EGBS_BUTTON_FOCUSED,
	NotFocused = EGBS_BUTTON_NOT_FOCUSED
};

} // end namespace GUI
} // end namespace IrrlichtLime