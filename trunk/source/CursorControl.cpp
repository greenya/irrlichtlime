#include "stdafx.h"
#include "CursorControl.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

CursorControl::CursorControl(gui::ICursorControl* cursorControl)
	: ReferenceCounted(cursorControl)
{
	LIME_ASSERT(cursorControl != nullptr);
	m_CursorControl = cursorControl;
}

void CursorControl::SetReferenceRect(Recti^ rect_or_null)
{
	m_CursorControl->setReferenceRect(LIME_SAFEREF(rect_or_null, m_NativeValue));
}

Vector2Di^ CursorControl::Position::get()
{
	return gcnew Vector2Di(m_CursorControl->getPosition());
}

void CursorControl::Position::set(Vector2Di^ value)
{
	LIME_ASSERT(value != nullptr);
	m_CursorControl->setPosition(*value->m_NativeValue);
}

Vector2Df^ CursorControl::RelativePosition::get()
{
	return gcnew Vector2Df(m_CursorControl->getRelativePosition());
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
	return String::Format("{0}; Visible={1}", Position, Visible);
}

} // end namespace GUI
} // end namespace IrrlichtLime