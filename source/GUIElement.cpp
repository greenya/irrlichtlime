#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIFileOpenDialog.h"
#include "GUIImage.h"
#include "GUIScrollBar.h"
#include "GUIStaticText.h"
#include "GUIWindow.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIElement^ GUIElement::Wrap(gui::IGUIElement* ref)
{
	if (ref == nullptr)
		return nullptr;

	switch (ref->getType())
	{
	case gui::EGUIET_BUTTON: return gcnew GUIButton((gui::IGUIButton*)ref);
	//case gui::EGUIET_CHECK_BOX: return ...
	//case gui::EGUIET_COMBO_BOX: return ...
	//case gui::EGUIET_CONTEXT_MENU: return ...
	//case gui::EGUIET_MENU: return ...
	//case gui::EGUIET_EDIT_BOX: return ...
	case gui::EGUIET_FILE_OPEN_DIALOG: return gcnew GUIFileOpenDialog((gui::IGUIFileOpenDialog*)ref);
	//case gui::EGUIET_COLOR_SELECT_DIALOG: return ...
	//case gui::EGUIET_IN_OUT_FADER: return ...
	case gui::EGUIET_IMAGE: return gcnew GUIImage((gui::IGUIImage*)ref);
	//case gui::EGUIET_LIST_BOX: return ...
	//case gui::EGUIET_MESH_VIEWER: return ...
	//case gui::EGUIET_MESSAGE_BOX: return ...
	//case gui::EGUIET_MODAL_SCREEN: return ...
	case gui::EGUIET_SCROLL_BAR: return gcnew GUIScrollBar((gui::IGUIScrollBar*)ref);
	//case gui::EGUIET_SPIN_BOX: return ...
	case gui::EGUIET_STATIC_TEXT: return gcnew GUIStaticText((gui::IGUIStaticText*)ref);
	//case gui::EGUIET_TAB: return ...
	//case gui::EGUIET_TAB_CONTROL: return ...
	//case gui::EGUIET_TABLE: return ...
	//case gui::EGUIET_TOOL_BAR: return ...
	//case gui::EGUIET_TREE_VIEW: return ...
	case gui::EGUIET_WINDOW: return gcnew GUIWindow((gui::IGUIWindow*)ref);
	}

	return gcnew GUIElement(ref); // gui::EGUIET_ELEMENT and anything other
}

GUIElement::GUIElement(gui::IGUIElement* ref)
	: IO::AttributeExchangingObject(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIElement = ref;
}

GUIElement^ GUIElement::GetElementFromID(int id, bool searchchildren)
{
	gui::IGUIElement *e = m_GUIElement->getElementFromId(id, searchchildren);
	return Wrap(e);
}

GUIElement^ GUIElement::GetElementFromID(int id)
{
	gui::IGUIElement *e = m_GUIElement->getElementFromId(id);
	return Wrap(e);
}

GUIElement^ GUIElement::GetElementFromPoint(Vector2Di^ point)
{
	LIME_ASSERT(point != nullptr);
	gui::IGUIElement *e = m_GUIElement->getElementFromPoint(*point->m_NativeValue);
	return Wrap(e);
}

bool GUIElement::IsMyChild(GUIElement^ child)
{
	return m_GUIElement->isMyChild(LIME_SAFEREF(child, m_GUIElement));
}

bool GUIElement::IsPointInside(Vector2Di^ point)
{
	LIME_ASSERT(point != nullptr);
	return m_GUIElement->isPointInside(*point->m_NativeValue);
}

GUIElementType GUIElement::Type::get()
{
	return (GUIElementType)m_GUIElement->getType();
}

int GUIElement::ID::get()
{
	return m_GUIElement->getID();
}

void GUIElement::ID::set(int value)
{
	m_GUIElement->setID(value);
}

bool GUIElement::Visible::get()
{
	return m_GUIElement->isVisible();
}

void GUIElement::Visible::set(bool value)
{
	m_GUIElement->setVisible(value);
}

bool GUIElement::Enabled::get()
{
	return m_GUIElement->isEnabled();
}

void GUIElement::Enabled::set(bool value)
{
	m_GUIElement->setEnabled(value);
}

bool GUIElement::TabStop::get()
{
	return m_GUIElement->isTabStop();
}

void GUIElement::TabStop::set(bool value)
{
	m_GUIElement->setTabStop(value);
}

int GUIElement::TabOrder::get()
{
	return m_GUIElement->getTabOrder();
}

void GUIElement::TabOrder::set(int value)
{
	m_GUIElement->setTabOrder(value);
}

Recti^ GUIElement::RelativePosition::get()
{
	return gcnew Recti(m_GUIElement->getRelativePosition());
}

void GUIElement::RelativePosition::set(Recti^ value)
{
	LIME_ASSERT(value != nullptr);
	m_GUIElement->setRelativePosition(*value->m_NativeValue);
}

Recti^ GUIElement::AbsolutePosition::get()
{
	return gcnew Recti(m_GUIElement->getAbsolutePosition());
}

bool GUIElement::NotClipped::get()
{
	return m_GUIElement->isNotClipped();
}

void GUIElement::NotClipped::set(bool value)
{
	m_GUIElement->setNotClipped(value);
}

Recti^ GUIElement::AbsoluteClippingRect::get()
{
	return gcnew Recti(m_GUIElement->getAbsoluteClippingRect());
}

String^ GUIElement::Text::get()
{
	return gcnew String(m_GUIElement->getText());
}

void GUIElement::Text::set(String^ value)
{
	m_GUIElement->setText(Lime::StringToStringW(value).c_str());
}

String^ GUIElement::ToolTipText::get()
{
	return gcnew String(m_GUIElement->getToolTipText().c_str());
}

void GUIElement::ToolTipText::set(String^ value)
{
	m_GUIElement->setToolTipText(Lime::StringToStringW(value).c_str());
}

String^ GUIElement::ToString()
{
	return String::Format("GUIElement: Type={0}; ID={1}; Text={2}", Type, ID, Text);
}

} // end namespace GUI
} // end namespace IrrlichtLime