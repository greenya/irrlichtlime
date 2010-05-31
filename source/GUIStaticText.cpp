#include "stdafx.h"
#include "GUIElement.h"
#include "GUIFont.h"
#include "GUIStaticText.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIStaticText::GUIStaticText(gui::IGUIStaticText* guiStaticText)
	: GUIElement(guiStaticText)
{
	LIME_ASSERT(guiStaticText != nullptr);
	m_GUIStaticText = guiStaticText;
}

void GUIStaticText::SetBackgroundColor(Video::Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	m_GUIStaticText->setBackgroundColor(*color->m_NativeValue);
}

void GUIStaticText::SetDrawBackground(bool draw)
{
	m_GUIStaticText->setDrawBackground(draw);
}

void GUIStaticText::SetDrawBorder(bool draw)
{
	m_GUIStaticText->setDrawBorder(draw);
}

void GUIStaticText::SetTextAlignment(GUIAlignment horizontal, GUIAlignment vertical)
{
	m_GUIStaticText->setTextAlignment((gui::EGUI_ALIGNMENT)horizontal, (gui::EGUI_ALIGNMENT)vertical);
}

Video::Coloru^ GUIStaticText::OverrideColor::get()
{
	return gcnew Video::Coloru(m_GUIStaticText->getOverrideColor());
}

void GUIStaticText::OverrideColor::set(Video::Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_GUIStaticText->setOverrideColor(*value->m_NativeValue);
}

bool GUIStaticText::OverrideColorEnabled::get()
{
	return m_GUIStaticText->isOverrideColorEnabled();
}

void GUIStaticText::OverrideColorEnabled::set(bool value)
{
	m_GUIStaticText->enableOverrideColor(value);
}

GUIFont^ GUIStaticText::OverrideFont::get()
{
	return LIME_SAFEWRAP(GUIFont, m_GUIStaticText->getOverrideFont());
}

void GUIStaticText::OverrideFont::set(GUIFont^ value)
{
	m_GUIStaticText->setOverrideFont(LIME_SAFEREF(value, m_GUIFont));
}

int GUIStaticText::TextHeight::get()
{
	return m_GUIStaticText->getTextHeight();
}

int GUIStaticText::TextWidth::get()
{
	return m_GUIStaticText->getTextWidth();
}

bool GUIStaticText::WordWrap::get()
{
	return m_GUIStaticText->isWordWrapEnabled();
}

void GUIStaticText::WordWrap::set(bool value)
{
	m_GUIStaticText->setWordWrap(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime