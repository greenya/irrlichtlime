#include "stdafx.h"
#include "CursorControl.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

CursorControl^ CursorControl::Wrap(gui::ICursorControl* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew CursorControl(ref);
}

CursorControl::CursorControl(gui::ICursorControl* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_CursorControl = ref;
}

void CursorControl::SetReferenceRect(Nullable<Recti> rect_or_null)
{
	m_CursorControl->setReferenceRect(LIME_NULLABLE(rect_or_null));
}

CursorIcon CursorControl::ActiveIcon::get()
{
	return (CursorIcon)m_CursorControl->getActiveIcon();
}

void CursorControl::ActiveIcon::set(CursorIcon value)
{
	m_CursorControl->setActiveIcon((gui::ECURSOR_ICON)value);
}

CursorPlatformBehavior CursorControl::PlatformBehavior::get()
{
	return (CursorPlatformBehavior)m_CursorControl->getPlatformBehavior();
}

void CursorControl::PlatformBehavior::set(CursorPlatformBehavior value)
{
	m_CursorControl->setPlatformBehavior((gui::ECURSOR_PLATFORM_BEHAVIOR)value);
}

Vector2Di CursorControl::Position::get()
{
	return Vector2Di(m_CursorControl->getPosition());
}

void CursorControl::Position::set(Vector2Di value)
{
	m_CursorControl->setPosition(value);
}

Vector2Df CursorControl::RelativePosition::get()
{
	return Vector2Df(m_CursorControl->getRelativePosition());
}

Dimension2Di^ CursorControl::SupportedIconSize::get()
{
	return gcnew Dimension2Di(m_CursorControl->getSupportedIconSize());
}

bool CursorControl::Visible::get()
{
	return m_CursorControl->isVisible();
}

void CursorControl::Visible::set(bool value)
{
	m_CursorControl->setVisible(value);
}

String^ CursorControl::ToString()
{
	return String::Format("CursorControl: Position={{{0}}}; Visible={1}", Position, Visible);
}

} // end namespace GUI
} // end namespace IrrlichtLime