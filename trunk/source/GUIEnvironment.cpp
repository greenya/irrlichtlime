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

	return gcnew GUIStaticText(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent,
	Int32 id)
{
	return AddStaticText(text, rectangle, border, wordWrap, parent, id, false);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent)
{
	return AddStaticText(text, rectangle, border, wordWrap, parent, -1);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap)
{
	return AddStaticText(text, rectangle, border, wordWrap, nullptr);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border)
{
	return AddStaticText(text, rectangle, border, true);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle)
{
	return AddStaticText(text, rectangle, false);
}

GUIEnvironment::GUIEnvironment(gui::IGUIEnvironment* guiEnvironment)
{
	LIME_ASSERT(guiEnvironment != nullptr);
	m_GUIEnvironment = guiEnvironment;
}

} // end namespace GUI
} // end namespace IrrlichtLime