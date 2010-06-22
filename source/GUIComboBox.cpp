#include "stdafx.h"
#include "GUIComboBox.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIComboBox^ GUIComboBox::Wrap(gui::IGUIComboBox* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIComboBox(ref);
}

GUIComboBox::GUIComboBox(gui::IGUIComboBox* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIComboBox = ref;
}

unsigned int GUIComboBox::AddItem(String^ text, unsigned int data)
{
	return m_GUIComboBox->addItem(Lime::StringToStringW(text).c_str(), data);
}

unsigned int GUIComboBox::AddItem(String^ text)
{
	return m_GUIComboBox->addItem(Lime::StringToStringW(text).c_str());
}

void GUIComboBox::Clear()
{
	m_GUIComboBox->clear();
}

int GUIComboBox::GetIndexForItemData(unsigned int data)
{
	return m_GUIComboBox->getIndexForItemData(data);
}

String^ GUIComboBox::GetItem(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return gcnew String(m_GUIComboBox->getItem(index));
}

unsigned int GUIComboBox::GetItemData(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return m_GUIComboBox->getItemData(index);
}

void GUIComboBox::RemoveItem(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIComboBox->removeItem(index);
}

void GUIComboBox::SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical)
{
	m_GUIComboBox->setTextAlignment((EGUI_ALIGNMENT)horizontal, (EGUI_ALIGNMENT)vertical);
}

unsigned int GUIComboBox::ItemCount::get()
{
	return m_GUIComboBox->getItemCount();
}

int GUIComboBox::SelectedIndex::get()
{
	return m_GUIComboBox->getSelected();
}

void GUIComboBox::SelectedIndex::set(int value)
{
	LIME_ASSERT(value >= -1); // -1 is valid value here
	m_GUIComboBox->setSelected(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime