#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIElementType : unsigned int
{
	Button = EGUIET_BUTTON,
	CheckBox = EGUIET_CHECK_BOX,
	ComboBox = EGUIET_COMBO_BOX,
	ContextMenu = EGUIET_CONTEXT_MENU,
	Menu = EGUIET_MENU,
	EditBox = EGUIET_EDIT_BOX,
	FileOpenDialog = EGUIET_FILE_OPEN_DIALOG,
	ColorSelectDialog = EGUIET_COLOR_SELECT_DIALOG,
	InOutFader = EGUIET_IN_OUT_FADER,
	Image = EGUIET_IMAGE,
	ListBox = EGUIET_LIST_BOX,
	MeshViewer = EGUIET_MESH_VIEWER,
	MessageBox = EGUIET_MESSAGE_BOX,
	ModalScreen = EGUIET_MODAL_SCREEN,
	ScrollBar = EGUIET_SCROLL_BAR,
	SpinBox = EGUIET_SPIN_BOX,
	StaticText = EGUIET_STATIC_TEXT,
	Tab = EGUIET_TAB,
	TabControl = EGUIET_TAB_CONTROL,
	Table = EGUIET_TABLE,
	ToolBar = EGUIET_TOOL_BAR,
	TreeView = EGUIET_TREE_VIEW,
	Window = EGUIET_WINDOW,
	Unknown = EGUIET_ELEMENT
};

} // end namespace GUI
} // end namespace IrrlichtLime