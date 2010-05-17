#pragma once

#include "stdafx.h"
#include "GUIElement.h"
#include "GUIEnvironment.h"
#include "GUIStaticText.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent,
	Int32 id, bool fillBackground)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject),
		border,
		wordWrap,
		parent == nullptr ? nullptr : parent->m_GUIElement,
		id,
		fillBackground);

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent,
	Int32 id)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject),
		border,
		wordWrap,
		parent == nullptr ? nullptr : parent->m_GUIElement,
		id);

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject),
		border,
		wordWrap,
		parent == nullptr ? nullptr : parent->m_GUIElement);

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject),
		border,
		wordWrap);

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject),
		border);

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle)
{
	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*((core::recti*)rectangle->m_NativeObject));

	return t == nullptr ? nullptr : gcnew GUIStaticText(t);
}

void GUIEnvironment::DrawAll()
{
	m_GUIEnvironment->drawAll();
}

GUIEnvironment::GUIEnvironment(gui::IGUIEnvironment* guiEnvironment)
{
	LIME_ASSERT(guiEnvironment != nullptr);
	m_GUIEnvironment = guiEnvironment;
}

} // end namespace GUI
} // end namespace IrrlichtLime