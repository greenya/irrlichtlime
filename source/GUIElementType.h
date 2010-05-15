#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace GUI
{
	public enum class GUIElementType : Int32
	{
		Button = gui::EGUIET_BUTTON,
		CheckBox = gui::EGUIET_CHECK_BOX,
		ComboBox = gui::EGUIET_COMBO_BOX,
		ContextMenu = gui::EGUIET_CONTEXT_MENU,
		Menu = gui::EGUIET_MENU,
		EditBox = gui::EGUIET_EDIT_BOX,
		FileOpenDialog = gui::EGUIET_FILE_OPEN_DIALOG,
		ColorSelectDialog = gui::EGUIET_COLOR_SELECT_DIALOG,
		InOutFader = gui::EGUIET_IN_OUT_FADER,
		Image = gui::EGUIET_IMAGE,
		ListBox = gui::EGUIET_LIST_BOX,
		MeshViewer = gui::EGUIET_MESH_VIEWER,
		MessageBox = gui::EGUIET_MESSAGE_BOX,
		ModalScreen = gui::EGUIET_MODAL_SCREEN,
		ScrollBar = gui::EGUIET_SCROLL_BAR,
		SpinBox = gui::EGUIET_SPIN_BOX,
		StaticText = gui::EGUIET_STATIC_TEXT,
		Tab = gui::EGUIET_TAB,
		TabControl = gui::EGUIET_TAB_CONTROL,
		Table = gui::EGUIET_TABLE,
		ToolBar = gui::EGUIET_TOOL_BAR,
		TreeView = gui::EGUIET_TREE_VIEW,
		Window = gui::EGUIET_WINDOW,
		Element = gui::EGUIET_ELEMENT
	};
}
}