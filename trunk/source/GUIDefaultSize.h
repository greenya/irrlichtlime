#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIDefaultSize
{
	ScrollBarSize = EGDS_SCROLLBAR_SIZE,
	MenuHeight = EGDS_MENU_HEIGHT,
	WindowButtonWidth = EGDS_WINDOW_BUTTON_WIDTH,
	CheckBoxWidth = EGDS_CHECK_BOX_WIDTH,
	MessageBoxWidth = EGDS_MESSAGE_BOX_WIDTH,
	MessageBoxHeight = EGDS_MESSAGE_BOX_HEIGHT,
	ButtonWidth = EGDS_BUTTON_WIDTH,
	ButtonHeight = EGDS_BUTTON_HEIGHT,
	TextDistanceX = EGDS_TEXT_DISTANCE_X,
	TextDistanceY = EGDS_TEXT_DISTANCE_Y,
	TitleBarTextDistanceX = EGDS_TITLEBARTEXT_DISTANCE_X,
	TitleBarTextDistanceY = EGDS_TITLEBARTEXT_DISTANCE_Y,
	MessageBoxGapSpace = EGDS_MESSAGE_BOX_GAP_SPACE,
	MessageBoxMinTextWidth = EGDS_MESSAGE_BOX_MIN_TEXT_WIDTH,
	MessageBoxMaxTextWidth = EGDS_MESSAGE_BOX_MAX_TEXT_WIDTH,
	MessageBoxMinTextHeight = EGDS_MESSAGE_BOX_MIN_TEXT_HEIGHT,
	MessageBoxMaxTextHeight = EGDS_MESSAGE_BOX_MAX_TEXT_HEIGHT,
	ButtonPressedImageOffsetX = EGDS_BUTTON_PRESSED_IMAGE_OFFSET_X,
	ButtonPressedImageOffsetY = EGDS_BUTTON_PRESSED_IMAGE_OFFSET_Y,
	ButtonPressedTextOffsetX = EGDS_BUTTON_PRESSED_TEXT_OFFSET_X,
	ButtonPressedTextOffsetY = EGDS_BUTTON_PRESSED_TEXT_OFFSET_Y
};

} // end namespace GUI
} // end namespace IrrlichtLime