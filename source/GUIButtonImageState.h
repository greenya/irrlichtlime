#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIButtonImageState
{
	ImageUp = EGBIS_IMAGE_UP,
	ImageUpMouseover = EGBIS_IMAGE_UP_MOUSEOVER,
	ImageUpFocused = EGBIS_IMAGE_UP_FOCUSED,
	ImageUpFocusedMouseover = EGBIS_IMAGE_UP_FOCUSED_MOUSEOVER,
	ImageDown = EGBIS_IMAGE_DOWN,
	ImageDownMouseover = EGBIS_IMAGE_DOWN_MOUSEOVER,
	ImageDownFocused = EGBIS_IMAGE_DOWN_FOCUSED,
	ImageDownFocusedMouseover = EGBIS_IMAGE_DOWN_FOCUSED_MOUSEOVER,
	ImageDisabled = EGBIS_IMAGE_DISABLED,
};

} // end namespace GUI
} // end namespace IrrlichtLime