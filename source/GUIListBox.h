#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

ref class GUISpriteBank;

public ref class GUIListBox : GUIElement
{
public:

	unsigned int AddItem(String^ text, int icon);
	unsigned int AddItem(String^ text);
	void ClearItemColor(unsigned int index, GUIListBoxColor colorType);
	void ClearItemColors(unsigned int index);
	void ClearItems();
	String^ GetItem(unsigned int index);
	Video::Coloru^ GetItemDefaultColor(GUIListBoxColor colorType);
	Video::Coloru^ GetItemColor(unsigned int index, GUIListBoxColor colorType);
	int GetItemIcon(unsigned int index);
	int InsertItem(unsigned int index, String^ text, int icon);
	int InsertItem(unsigned int index, String^ text);
	bool ItemColorOverrided(unsigned int index, GUIListBoxColor colorType);
	void RemoveItem (unsigned int index);
	void SetDrawBackground(bool draw);
	void SetItem(unsigned int index, String^ text, int icon);
	void SetItem(unsigned int index, String^ text);
	void SetItemColor(unsigned int index, GUIListBoxColor colorType, Video::Coloru^ color);
	void SetItemHeight(int height);
	void SetSpriteBank(GUISpriteBank^ bank);
	void SwapItems(unsigned int index1, unsigned int index2);

	property bool AutoScroll { bool get(); void set(bool value); }
	property unsigned int ItemCount { unsigned int get(); }
	property int SelectedIndex { int get(); void set(int value); }
	property String^ SelectedItem { String^ get(); void set(String^ value); }

internal:

	static GUIListBox^ Wrap(gui::IGUIListBox* ref);
	GUIListBox(gui::IGUIListBox* ref);

	gui::IGUIListBox* m_GUIListBox;
};

} // end namespace GUI
} // end namespace IrrlichtLime