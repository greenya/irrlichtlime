#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIEventType
{
	ElementFocusLost = EGET_ELEMENT_FOCUS_LOST,
	ElementFocused = EGET_ELEMENT_FOCUSED,
	ElementMouseHovered = EGET_ELEMENT_HOVERED,
	ElementMouseLeft = EGET_ELEMENT_LEFT,
	ElementClosed = EGET_ELEMENT_CLOSED,
	ButtonClicked = EGET_BUTTON_CLICKED,
	ScrollbarChanged = EGET_SCROLL_BAR_CHANGED,
	CheckboxChanged = EGET_CHECKBOX_CHANGED,
	ListboxChanged = EGET_LISTBOX_CHANGED,
	ListboxSelectedAgain = EGET_LISTBOX_SELECTED_AGAIN,
	FileDialogFileSelected = EGET_FILE_SELECTED,
	FileDialogDirectorySelected = EGET_DIRECTORY_SELECTED,
	FileDialogCancelled = EGET_FILE_CHOOSE_DIALOG_CANCELLED,
	MessageBoxYes = EGET_MESSAGEBOX_YES,
	MessageBoxNo = EGET_MESSAGEBOX_NO,
	MessageBoxOK = EGET_MESSAGEBOX_OK,
	MessageBoxCancel = EGET_MESSAGEBOX_CANCEL,
	EditboxEnter = EGET_EDITBOX_ENTER,
	EditboxChanged = EGET_EDITBOX_CHANGED,
	EditboxMarkingChanged = EGET_EDITBOX_MARKING_CHANGED,
	TabChanged = EGET_TAB_CHANGED,
	MenuItemSelected = EGET_MENU_ITEM_SELECTED,
	ComboboxChanged = EGET_COMBO_BOX_CHANGED,
	SpinboxChanged = EGET_SPINBOX_CHANGED,
	TableChanged = EGET_TABLE_CHANGED,
	TableHeaderChanged = EGET_TABLE_HEADER_CHANGED,
	TableSelectedAgain = EGET_TABLE_SELECTED_AGAIN,
	TreeviewNodeDeselect = EGET_TREEVIEW_NODE_DESELECT,
	TreeviewNodeSelect = EGET_TREEVIEW_NODE_SELECT,
	TreeviewNodeExpand = EGET_TREEVIEW_NODE_EXPAND,
	TreeviewNodeCollaps = EGET_TREEVIEW_NODE_COLLAPS
};

} // end namespace GUI
} // end namespace IrrlichtLime