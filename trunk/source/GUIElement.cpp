#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIElement::GUIElement(gui::IGUIElement* guiElement)
	: IO::AttributeExchangingObject(guiElement)
{
	LIME_ASSERT(guiElement != nullptr);
	m_GUIElement = guiElement;
}

GUIElement^ GUIElement::GetElementFromID(int id, bool searchchildren)
{
	gui::IGUIElement *e = m_GUIElement->getElementFromId(id, searchchildren);
	return LIME_SAFEWRAP(GUIElement, e);
}

GUIElement^ GUIElement::GetElementFromID(int id)
{
	gui::IGUIElement *e = m_GUIElement->getElementFromId(id);
	return LIME_SAFEWRAP(GUIElement, e);
}

GUIElement^ GUIElement::GetElementFromPoint(Vector2Di^ point)
{
	LIME_ASSERT(point != nullptr);
	gui::IGUIElement *e = m_GUIElement->getElementFromPoint(*point->m_NativeValue);
	return LIME_SAFEWRAP(GUIElement, e);
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
	return String::Format("Type={0}; Text={1}", Type, Text);
}

} // end namespace GUI
} // end namespace IrrlichtLime