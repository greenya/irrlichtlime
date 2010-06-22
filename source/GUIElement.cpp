#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "GUIButton.h"
#include "GUIComboBox.h"
#include "GUIContextMenu.h"
#include "GUIEditBox.h"
#include "GUIElement.h"
#include "GUIFileOpenDialog.h"
#include "GUIImage.h"
#include "GUIListBox.h"
#include "GUIScrollBar.h"
#include "GUIStaticText.h"
#include "GUIToolBar.h"
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
	case gui::EGUIET_COMBO_BOX: return gcnew GUIComboBox((gui::IGUIComboBox*)ref);
	case gui::EGUIET_CONTEXT_MENU: return gcnew GUIContextMenu((gui::IGUIContextMenu*)ref);
	case gui::EGUIET_MENU: return gcnew GUIContextMenu((gui::IGUIContextMenu*)ref);
	case gui::EGUIET_EDIT_BOX: return gcnew GUIEditBox((gui::IGUIEditBox*)ref);
	case gui::EGUIET_FILE_OPEN_DIALOG: return gcnew GUIFileOpenDialog((gui::IGUIFileOpenDialog*)ref);
	//case gui::EGUIET_COLOR_SELECT_DIALOG: return ...
	//case gui::EGUIET_IN_OUT_FADER: return ...
	case gui::EGUIET_IMAGE: return gcnew GUIImage((gui::IGUIImage*)ref);
	case gui::EGUIET_LIST_BOX: return gcnew GUIListBox((gui::IGUIListBox*)ref);
	//case gui::EGUIET_MESH_VIEWER: return ...
	case gui::EGUIET_MESSAGE_BOX: return gcnew GUIWindow((gui::IGUIWindow*)ref);
	//case gui::EGUIET_MODAL_SCREEN: return ...
	case gui::EGUIET_SCROLL_BAR: return gcnew GUIScrollBar((gui::IGUIScrollBar*)ref);
	//case gui::EGUIET_SPIN_BOX: return ...
	case gui::EGUIET_STATIC_TEXT: return gcnew GUIStaticText((gui::IGUIStaticText*)ref);
	//case gui::EGUIET_TAB: return ...
	//case gui::EGUIET_TAB_CONTROL: return ...
	//case gui::EGUIET_TABLE: return ...
	case gui::EGUIET_TOOL_BAR: return gcnew GUIToolBar((gui::IGUIToolBar*)ref);
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

void GUIElement::AddChild(GUIElement^ child)
{
	m_GUIElement->addChild(LIME_SAFEREF(child, m_GUIElement));
}

bool GUIElement::BringToFront(GUIElement^ child)
{
	return m_GUIElement->bringToFront(LIME_SAFEREF(child, m_GUIElement));
}

void GUIElement::Draw()
{
	m_GUIElement->draw();
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

bool GUIElement::GetNextElement(int startOrder, bool reverse, bool group, [Out] GUIElement^% first, [Out] GUIElement^% closest, bool includeInvisible)
{
	gui::IGUIElement* f;
	gui::IGUIElement* c;

	bool b = m_GUIElement->getNextElement(startOrder, reverse, group, f, c, includeInvisible);

	if (b)
	{
		first = GUIElement::Wrap(f);
		closest = GUIElement::Wrap(c);
	}

	return b;
}

bool GUIElement::GetNextElement(int startOrder, bool reverse, bool group, [Out] GUIElement^% first, [Out] GUIElement^% closest)
{
	gui::IGUIElement* f;
	gui::IGUIElement* c;

	bool b = m_GUIElement->getNextElement(startOrder, reverse, group, f, c);

	if (b)
	{
		first = GUIElement::Wrap(f);
		closest = GUIElement::Wrap(c);
	}

	return b;
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

void GUIElement::Move(Vector2Di^ absoluteMovement)
{
	LIME_ASSERT(absoluteMovement != nullptr);
	m_GUIElement->move(*absoluteMovement->m_NativeValue);
}

void GUIElement::Remove()
{
	m_GUIElement->remove();
}

void GUIElement::RemoveChild(GUIElement^ child)
{
	m_GUIElement->removeChild(LIME_SAFEREF(child, m_GUIElement));
}

void GUIElement::SetAlignment(GUIAlignment left, GUIAlignment right, GUIAlignment top, GUIAlignment bottom)
{
	m_GUIElement->setAlignment(
		(gui::EGUI_ALIGNMENT)left,
		(gui::EGUI_ALIGNMENT)right,
		(gui::EGUI_ALIGNMENT)top,
		(gui::EGUI_ALIGNMENT)bottom);
}

void GUIElement::SetMaxSize(Dimension2Du^ size)
{
	LIME_ASSERT(size != nullptr);
	m_GUIElement->setMaxSize(*size->m_NativeValue);
}

void GUIElement::SetMinSize(Dimension2Du^ size)
{
	LIME_ASSERT(size != nullptr);
	m_GUIElement->setMinSize(*size->m_NativeValue);
}

void GUIElement::SetRelativePositionProportional(Rectf^ relativePosition)
{
	LIME_ASSERT(relativePosition != nullptr);
	m_GUIElement->setRelativePositionProportional(*relativePosition->m_NativeValue);
}

void GUIElement::UpdateAbsolutePosition()
{
	m_GUIElement->updateAbsolutePosition();
}

Recti^ GUIElement::AbsoluteClippingRect::get()
{
	return gcnew Recti(m_GUIElement->getAbsoluteClippingRect());
}

Recti^ GUIElement::AbsolutePosition::get()
{
	return gcnew Recti(m_GUIElement->getAbsolutePosition());
}

List<GUIElement^>^ GUIElement::ChildList::get()
{
	List<GUIElement^>^ l = gcnew List<GUIElement^>();

	core::list<IGUIElement*> u = m_GUIElement->getChildren();
	for (core::list<gui::IGUIElement*>::ConstIterator i = u.begin(); i != u.end(); ++i)
	{
		GUIElement^ e = GUIElement::Wrap(*i);
		if (e != nullptr)
			l->Add(e);
	}

	return l;
}

bool GUIElement::Clipped::get()
{
	return !m_GUIElement->isNotClipped();
}

void GUIElement::Clipped::set(bool value)
{
	m_GUIElement->setNotClipped(!value);
}

bool GUIElement::Enabled::get()
{
	return m_GUIElement->isEnabled();
}

void GUIElement::Enabled::set(bool value)
{
	m_GUIElement->setEnabled(value);
}

int GUIElement::ID::get()
{
	return m_GUIElement->getID();
}

void GUIElement::ID::set(int value)
{
	m_GUIElement->setID(value);
}

GUIElement^ GUIElement::Parent::get()
{
	gui::IGUIElement* e = m_GUIElement->getParent();
	return GUIElement::Wrap(e);
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

bool GUIElement::SubElement::get()
{
	return m_GUIElement->isSubElement();
}

void GUIElement::SubElement::set(bool value)
{
	m_GUIElement->setSubElement(value);
}

bool GUIElement::TabGroup::get()
{
	return m_GUIElement->isTabGroup();
}

void GUIElement::TabGroup::set(bool value)
{
	m_GUIElement->setTabGroup(value);
}

GUIElement^ GUIElement::TabGroupElement::get()
{
	gui::IGUIElement* e = m_GUIElement->getTabGroup();
	return GUIElement::Wrap(e);
}

int GUIElement::TabOrder::get()
{
	return m_GUIElement->getTabOrder();
}

void GUIElement::TabOrder::set(int value)
{
	m_GUIElement->setTabOrder(value);
}

bool GUIElement::TabStop::get()
{
	return m_GUIElement->isTabStop();
}

void GUIElement::TabStop::set(bool value)
{
	m_GUIElement->setTabStop(value);
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

GUIElementType GUIElement::Type::get()
{
	return (GUIElementType)m_GUIElement->getType();
}

String^ GUIElement::TypeName::get()
{
	return gcnew String(m_GUIElement->getTypeName());
}

bool GUIElement::Visible::get()
{
	return m_GUIElement->isVisible();
}

void GUIElement::Visible::set(bool value)
{
	m_GUIElement->setVisible(value);
}

String^ GUIElement::ToString()
{
	return String::Format("GUIElement: Type={0}; ID={1}; Text={2}", Type, ID, Text);
}

} // end namespace GUI
} // end namespace IrrlichtLime