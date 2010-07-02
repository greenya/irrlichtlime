#include "stdafx.h"
#include "GUIEditBox.h"
#include "GUIElement.h"
#include "GUIFont.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIEditBox^ GUIEditBox::Wrap(gui::IGUIEditBox* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIEditBox(ref);
}

GUIEditBox::GUIEditBox(gui::IGUIEditBox* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIEditBox = ref;
}

void GUIEditBox::SetDrawBorder(bool draw)
{
	m_GUIEditBox->setDrawBorder(draw);
}

void GUIEditBox::SetOverrideColor(bool enable, Video::Color^ color)
{
	LIME_ASSERT(color != nullptr);

	m_GUIEditBox->enableOverrideColor(enable);
	m_GUIEditBox->setOverrideColor(*color->m_NativeValue);
}

void GUIEditBox::SetOverrideColor(bool enable)
{
	m_GUIEditBox->enableOverrideColor(enable);
}

void GUIEditBox::SetOverrideFont(GUIFont^ font)
{
	m_GUIEditBox->setOverrideFont(LIME_SAFEREF(font, m_GUIFont));
}

void GUIEditBox::SetPasswordChar(Char x)
{
	m_GUIEditBox->setPasswordBox(m_GUIEditBox->isPasswordBox(), x);
}

void GUIEditBox::SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical)
{
	m_GUIEditBox->setTextAlignment((gui::EGUI_ALIGNMENT)horizontal, (gui::EGUI_ALIGNMENT)vertical);
}

bool GUIEditBox::AutoScroll::get()
{
	return m_GUIEditBox->isAutoScrollEnabled();
}

void GUIEditBox::AutoScroll::set(bool value)
{
	m_GUIEditBox->setAutoScroll(value);
}

int GUIEditBox::MaxLength::get()
{
	return m_GUIEditBox->getMax();
}

void GUIEditBox::MaxLength::set(int value)
{
	LIME_ASSERT(value >= 0);
	m_GUIEditBox->setMax(value);
}

bool GUIEditBox::MultiLine::get()
{
	return m_GUIEditBox->isMultiLineEnabled();
}

void GUIEditBox::MultiLine::set(bool value)
{
	m_GUIEditBox->setMultiLine(value);
}

bool GUIEditBox::PasswordBox::get()
{
	return m_GUIEditBox->isPasswordBox();
}

void GUIEditBox::PasswordBox::set(bool value)
{
	m_GUIEditBox->setPasswordBox(value);
}

Dimension2Di^ GUIEditBox::TextDimension::get()
{
	return gcnew Dimension2Di(m_GUIEditBox->getTextDimension());
}

bool GUIEditBox::WordWrap::get()
{
	return m_GUIEditBox->isWordWrapEnabled();
}

void GUIEditBox::WordWrap::set(bool value)
{
	m_GUIEditBox->setWordWrap(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime