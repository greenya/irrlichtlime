#include "stdafx.h"
#include "GUIElement.h"
#include "GUIFont.h"
#include "GUIStaticText.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIStaticText^ GUIStaticText::Wrap(gui::IGUIStaticText* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIStaticText(ref);
}

GUIStaticText::GUIStaticText(gui::IGUIStaticText* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIStaticText = ref;
}

void GUIStaticText::SetBackgroundColor(Video::Color^ color)
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

Video::Color^ GUIStaticText::OverrideColor::get()
{
	return gcnew Video::Color(m_GUIStaticText->getOverrideColor());
}

void GUIStaticText::OverrideColor::set(Video::Color^ value)
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
	return GUIFont::Wrap(m_GUIStaticText->getOverrideFont());
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