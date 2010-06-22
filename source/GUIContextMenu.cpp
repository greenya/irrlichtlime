#include "stdafx.h"
#include "GUIContextMenu.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIContextMenu^ GUIContextMenu::Wrap(gui::IGUIContextMenu* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIContextMenu(ref);
}

GUIContextMenu::GUIContextMenu(gui::IGUIContextMenu* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIContextMenu = ref;
}

unsigned int GUIContextMenu::AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked, bool autoChecking)
{
	return m_GUIContextMenu->addItem(
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu,
		isChecked,
		autoChecking);
}

unsigned int GUIContextMenu::AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked)
{
	return m_GUIContextMenu->addItem(
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu,
		isChecked);
}

unsigned int GUIContextMenu::AddItem(String^ text, int commandID, bool enabled, bool hasSubMenu)
{
	return m_GUIContextMenu->addItem(
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu);
}

unsigned int GUIContextMenu::AddItem(String^ text, int commandID, bool enabled)
{
	return m_GUIContextMenu->addItem(
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled);
}

unsigned int GUIContextMenu::AddItem(String^ text, int commandID)
{
	return m_GUIContextMenu->addItem(
		Lime::StringToStringW(text).c_str(),
		commandID);
}

unsigned int GUIContextMenu::AddItem(String^ text)
{
	return m_GUIContextMenu->addItem(Lime::StringToStringW(text).c_str());
}

void GUIContextMenu::AddSeparator()
{
	m_GUIContextMenu->addSeparator();
}

int GUIContextMenu::FindItem(int commandID, unsigned int indexStartSearch)
{
	LIME_ASSERT(indexStartSearch < ItemCount);
	return m_GUIContextMenu->findItemWithCommandId(commandID, indexStartSearch);
}

int GUIContextMenu::FindItem(int commandID)
{
	return m_GUIContextMenu->findItemWithCommandId(commandID);
}

bool GUIContextMenu::GetItemAutoChecking(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return m_GUIContextMenu->getItemAutoChecking(index);
}

bool GUIContextMenu::GetItemChecked(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return m_GUIContextMenu->isItemChecked(index);
}

int GUIContextMenu::GetItemCommandID(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return m_GUIContextMenu->getItemCommandId(index);
}

bool GUIContextMenu::GetItemEnabled(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return m_GUIContextMenu->isItemEnabled(index);
}

String^ GUIContextMenu::GetItemText(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	return gcnew String(m_GUIContextMenu->getItemText(index));
}

GUIContextMenu^ GUIContextMenu::GetSubMenu(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);

	gui::IGUIContextMenu* m = m_GUIContextMenu->getSubMenu(index);
	return GUIContextMenu::Wrap(m);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked, bool autoChecking)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu,
		isChecked,
		autoChecking);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu, bool isChecked)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu,
		isChecked);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text, int commandID, bool enabled, bool hasSubMenu)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled,
		hasSubMenu);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text, int commandID, bool enabled)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str(),
		commandID,
		enabled);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text, int commandID)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str(),
		commandID);
}

unsigned int GUIContextMenu::InsertItem(unsigned int index, String^ text)
{
	return m_GUIContextMenu->insertItem(
		index,
		Lime::StringToStringW(text).c_str());
}

void GUIContextMenu::RemoveAllItems()
{
	m_GUIContextMenu->removeAllItems();
}

void GUIContextMenu::RemoveItem(unsigned int index)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->removeItem(index);
}

void GUIContextMenu::SetEventParent(GUIElement^ parent)
{
	m_GUIContextMenu->setEventParent(LIME_SAFEREF(parent, m_GUIElement));
}

void GUIContextMenu::SetItemAutoChecking(unsigned int index, bool autoChecking)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->setItemAutoChecking(index, autoChecking);
}

void GUIContextMenu::SetItemChecked(unsigned int index, bool isChecked)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->setItemChecked(index, isChecked);
}

void GUIContextMenu::SetItemCommandID(unsigned int index, int commandID)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->setItemCommandId(index, commandID);
}

void GUIContextMenu::SetItemEnabled(unsigned int index, bool enabled)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->setItemEnabled(index, enabled);
}

void GUIContextMenu::SetItemText(unsigned int index, String^ text)
{
	LIME_ASSERT(index < ItemCount);
	m_GUIContextMenu->setItemText(index, Lime::StringToStringW(text).c_str());
}

GUIContextMenuClose GUIContextMenu::CloseHandling::get()
{
	return (GUIContextMenuClose)m_GUIContextMenu->getCloseHandling();
}

void GUIContextMenu::CloseHandling::set(GUIContextMenuClose value)
{
	m_GUIContextMenu->setCloseHandling((gui::ECONTEXT_MENU_CLOSE)value);
}

unsigned int GUIContextMenu::ItemCount::get()
{
	return m_GUIContextMenu->getItemCount();
}

int GUIContextMenu::SelectedIndex::get()
{
	return m_GUIContextMenu->getSelectedItem();
}

} // end namespace GUI
} // end namespace IrrlichtLime