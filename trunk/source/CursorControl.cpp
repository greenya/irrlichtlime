#pragma once

#include "stdafx.h"
#include "CursorControl.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

CursorControl::CursorControl(gui::ICursorControl* cursorControl)
{
	LIME_ASSERT(cursorControl != nullptr);
	m_CursorControl = cursorControl;
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

void CursorControl::ReferenceRect::set(Recti^ value)
{
	// we omit assert "value != nullprt" because it is valid value for setReferenceRect()
	m_CursorControl->setReferenceRect(LIME_SAFEREF(value, m_NativeValue));
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