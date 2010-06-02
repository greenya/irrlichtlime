#include "stdafx.h"
#include "GUIElement.h"
#include "GUIListBox.h"
#include "GUISpriteBank.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIListBox^ GUIListBox::Wrap(gui::IGUIListBox* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIListBox(ref);
}

GUIListBox::GUIListBox(gui::IGUIListBox* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIListBox = ref;
}

unsigned int GUIListBox::AddItem(String^ text, int icon)
{
	return m_GUIListBox->addItem(Lime::StringToStringW(text).c_str(), icon);
}

unsigned int GUIListBox::AddItem(String^ text)
{
	return m_GUIListBox->addItem(Lime::StringToStringW(text).c_str());
}

void GUIListBox::ClearItemColor(unsigned int index, GUIListBoxColor colorType)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	m_GUIListBox->clearItemOverrideColor(index, (gui::EGUI_LISTBOX_COLOR)colorType);
}

void GUIListBox::ClearItemColors(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	m_GUIListBox->clearItemOverrideColor(index);
}

void GUIListBox::ClearItems()
{
	m_GUIListBox->clear();
}

String^ GUIListBox::GetItem(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	return gcnew String(m_GUIListBox->getListItem(index));
}

Video::Coloru^ GUIListBox::GetItemDefaultColor(GUIListBoxColor colorType)
{
	return gcnew Video::Coloru(m_GUIListBox->getItemDefaultColor((gui::EGUI_LISTBOX_COLOR)colorType));
}

Video::Coloru^ GUIListBox::GetItemColor(unsigned int index, GUIListBoxColor colorType)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	return gcnew Video::Coloru(m_GUIListBox->getItemOverrideColor(index, (gui::EGUI_LISTBOX_COLOR)colorType));
}

int GUIListBox::GetItemIcon(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	return m_GUIListBox->getIcon(index);
}

int GUIListBox::InsertItem(unsigned int index, String^ text, int icon)
{
	return m_GUIListBox->insertItem(index, Lime::StringToStringW(text).c_str(), icon);
}

int GUIListBox::InsertItem(unsigned int index, String^ text)
{
	return m_GUIListBox->insertItem(index, Lime::StringToStringW(text).c_str(), -1);
}

bool GUIListBox::ItemColorOverrided(unsigned int index, GUIListBoxColor colorType)
{
	return m_GUIListBox->hasItemOverrideColor(index, (gui::EGUI_LISTBOX_COLOR)colorType);
}

void GUIListBox::RemoveItem (unsigned int index)
{
	m_GUIListBox->removeItem(index);
}

void GUIListBox::SetDrawBackground(bool draw)
{
	m_GUIListBox->setDrawBackground(draw);
}

void GUIListBox::SetItem(unsigned int index, String^ text, int icon)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	m_GUIListBox->setItem(index, Lime::StringToStringW(text).c_str(), icon);
}

void GUIListBox::SetItem(unsigned int index, String^ text)
{
	LIME_ASSERT(index >= 0 && index < ItemCount);
	m_GUIListBox->setItem(index, Lime::StringToStringW(text).c_str(), -1);
}

void GUIListBox::SetItemColor(unsigned int index, GUIListBoxColor colorType, Video::Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(index >= 0 && index < ItemCount);
	m_GUIListBox->setItemOverrideColor(index, (gui::EGUI_LISTBOX_COLOR)colorType, *color->m_NativeValue);
}

void GUIListBox::SetItemHeight(int height)
{
	m_GUIListBox->setItemHeight(height);
}

void GUIListBox::SetSpriteBank(GUISpriteBank^ bank)
{
	m_GUIListBox->setSpriteBank(LIME_SAFEREF(bank, m_GUISpriteBank));
}

void GUIListBox::SwapItems(unsigned int index1, unsigned int index2)
{
	LIME_ASSERT(index1 != index2);
	LIME_ASSERT(index1 >= 0 && index1 < ItemCount);
	LIME_ASSERT(index2 >= 0 && index2 < ItemCount);
	m_GUIListBox->swapItems(index1, index2);
}

bool GUIListBox::AutoScroll::get()
{
	return m_GUIListBox->isAutoScrollEnabled();
}

void GUIListBox::AutoScroll::set(bool value)
{
	m_GUIListBox->setAutoScrollEnabled(value);
}

unsigned int GUIListBox::ItemCount::get()
{
	return m_GUIListBox->getItemCount();
}

int GUIListBox::SelectedIndex::get()
{
	return m_GUIListBox->getSelected();
}

void GUIListBox::SelectedIndex::set(int value)
{
	m_GUIListBox->setSelected(value);
}

String^ GUIListBox::SelectedItem::get()
{
	int i = m_GUIListBox->getSelected();

	if (i == -1)
		return nullptr;

	return gcnew String(m_GUIListBox->getListItem(i));
}

void GUIListBox::SelectedItem::set(String^ value)
{
	if (value == nullptr)
		m_GUIListBox->setSelected(nullptr);

	m_GUIListBox->setSelected(Lime::StringToStringW(value).c_str());
}

} // end namespace GUI
} // end namespace IrrlichtLime