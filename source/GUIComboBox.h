#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public ref class GUIComboBox : GUIElement
{
public:

	unsigned int AddItem(String^ text, unsigned int data);
	unsigned int AddItem(String^ text);

	void Clear();

	int GetIndexForItemData(unsigned int data);
	String^ GetItem(unsigned int index);
	unsigned int GetItemData(unsigned int index);

	void RemoveItem(unsigned int index);

	void SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical);

	property unsigned int ItemCount { unsigned int get(); }
	property int SelectedIndex { int get(); void set(int value); }

internal:

	static GUIComboBox^ Wrap(gui::IGUIComboBox* ref);
	GUIComboBox(gui::IGUIComboBox* ref);

	gui::IGUIComboBox* m_GUIComboBox;
};

} // end namespace GUI
} // end namespace IrrlichtLime