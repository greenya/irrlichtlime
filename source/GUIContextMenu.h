#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public ref class GUIContextMenu : GUIElement
{
public:

	unsigned int AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked, bool autoChecking);
	unsigned int AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked);
	unsigned int AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu);
	unsigned int AddItem(String^ text, int commandID, bool enabled);
	unsigned int AddItem(String^ text, int commandID);
	unsigned int AddItem(String^ text);

	void AddSeparator();

	int FindItem(int commandID, unsigned int indexStartSearch);
	int FindItem(int commandID);

	bool GetItemAutoChecking(unsigned int index);
	bool GetItemChecked(unsigned int index);
	int GetItemCommandID(unsigned int index);
	bool GetItemEnabled(unsigned int index);
	String^ GetItemText(unsigned int index);
	GUIContextMenu^ GetSubMenu(unsigned int index);

	unsigned int InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked, bool autoChecking);
	unsigned int InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked);
	unsigned int InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu);
	unsigned int InsertItem(unsigned int index, String^ text, int commandID, bool enabled);
	unsigned int InsertItem(unsigned int index, String^ text, int commandID);
	unsigned int InsertItem(unsigned int index, String^ text);

	void RemoveAllItems();
	void RemoveItem(unsigned int index);

	void SetEventParent(GUIElement^ parent);

	void SetItemAutoChecking(unsigned int index, bool autoChecking);
	void SetItemChecked(unsigned int index, bool isChecked);
	void SetItemCommandID(unsigned int index, int commandID);
	void SetItemEnabled(unsigned int index, bool enabled);
	void SetItemText(unsigned int index, String^ text);

	property GUIContextMenuClose CloseHandling { GUIContextMenuClose get(); void set(GUIContextMenuClose value); }
	property unsigned int ItemCount { unsigned int get(); }
	property int SelectedIndex { int get(); }

internal:

	static GUIContextMenu^ Wrap(gui::IGUIContextMenu* ref);
	GUIContextMenu(gui::IGUIContextMenu* ref);

	gui::IGUIContextMenu* m_GUIContextMenu;
};

} // end namespace GUI
} // end namespace IrrlichtLime