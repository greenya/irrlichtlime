#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIDefaultIcon
{
	WindowMaximize = EGDI_WINDOW_MAXIMIZE,
	WindowRestore = EGDI_WINDOW_RESTORE,
	WindowClose = EGDI_WINDOW_CLOSE,
	WindowMinimize = EGDI_WINDOW_MINIMIZE,
	WindowResize = EGDI_WINDOW_RESIZE,
	CursorUp = EGDI_CURSOR_UP,
	CursorDown = EGDI_CURSOR_DOWN,
	CursorLeft = EGDI_CURSOR_LEFT,
	CursorRight = EGDI_CURSOR_RIGHT,
	MenuMore = EGDI_MENU_MORE,
	CheckBoxChecked = EGDI_CHECK_BOX_CHECKED,
	DropDown = EGDI_DROP_DOWN,
	CursorUp_Small = EGDI_SMALL_CURSOR_UP,
	CursorDown_Small = EGDI_SMALL_CURSOR_DOWN,
	RadioButtonChecked = EGDI_RADIO_BUTTON_CHECKED,
	MoreLeft = EGDI_MORE_LEFT,
	MoreRight = EGDI_MORE_RIGHT,
	MoreUp = EGDI_MORE_UP,
	MoreDown = EGDI_MORE_DOWN,
	Expand = EGDI_EXPAND,
	Collapse = EGDI_COLLAPSE,
	File = EGDI_FILE,
	Directory = EGDI_DIRECTORY
};

} // end namespace GUI
} // end namespace IrrlichtLime