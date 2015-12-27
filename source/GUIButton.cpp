#include "stdafx.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIFont.h"
#include "GUISpriteBank.h"
#include "Texture.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIButton^ GUIButton::Wrap(gui::IGUIButton* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIButton(ref);
}

GUIButton::GUIButton(gui::IGUIButton* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIButton = ref;
}

void GUIButton::SetImage(GUIButtonImageState state, Video::Texture^ image, Recti sourceRect)
{
	m_GUIButton->setImage((EGUI_BUTTON_IMAGE_STATE)state, LIME_SAFEREF(image, m_Texture), sourceRect);
}

void GUIButton::SetImage(GUIButtonImageState state, Video::Texture^ image)
{
	m_GUIButton->setImage((EGUI_BUTTON_IMAGE_STATE)state, LIME_SAFEREF(image, m_Texture));
}

void GUIButton::SetImage(GUIButtonImageState state)
{
	m_GUIButton->setImage((EGUI_BUTTON_IMAGE_STATE)state);
}

void GUIButton::SetImage(Video::Texture^ image, Recti sourceRect)
{
	m_GUIButton->setImage(LIME_SAFEREF(image, m_Texture), sourceRect);
}

void GUIButton::SetImage(Video::Texture^ image)
{
	m_GUIButton->setImage(LIME_SAFEREF(image, m_Texture));
}

void GUIButton::SetImage()
{
	m_GUIButton->setImage();
}

void GUIButton::SetPressedImage(Video::Texture^ image, Recti sourceRect)
{
	m_GUIButton->setPressedImage(LIME_SAFEREF(image, m_Texture), sourceRect);
}

void GUIButton::SetPressedImage(Video::Texture^ image)
{
	m_GUIButton->setPressedImage(LIME_SAFEREF(image, m_Texture));
}

void GUIButton::SetPressedImage()
{
	m_GUIButton->setImage();
}

void GUIButton::SetSprite(GUIButtonState state, int index, Video::Color color, bool loop)
{
	m_GUIButton->setSprite((gui::EGUI_BUTTON_STATE)state, index, color, loop);
}

void GUIButton::SetSprite(GUIButtonState state, int index, Video::Color color)
{
	m_GUIButton->setSprite((gui::EGUI_BUTTON_STATE)state, index, color);
}

void GUIButton::SetSprite(GUIButtonState state, int index)
{
	m_GUIButton->setSprite((gui::EGUI_BUTTON_STATE)state, index);
}

void GUIButton::SetSpriteBank(GUISpriteBank^ bank)
{
	m_GUIButton->setSpriteBank(LIME_SAFEREF(bank, m_GUISpriteBank));
}

void GUIButton::SetSpriteBank()
{
	m_GUIButton->setSpriteBank();
}

GUIFont^ GUIButton::ActiveFont::get()
{
	gui::IGUIFont* f = m_GUIButton->getActiveFont();
	return GUIFont::Wrap(f);
}

bool GUIButton::AlphaChannel::get()
{
	return m_GUIButton->isAlphaChannelUsed();
}

void GUIButton::AlphaChannel::set(bool value)
{
	m_GUIButton->setUseAlphaChannel(value);
}

bool GUIButton::Border::get()
{
	return m_GUIButton->isDrawingBorder();
}

void GUIButton::Border::set(bool value)
{
	m_GUIButton->setDrawBorder(value);
}

GUIFont^ GUIButton::OverrideFont::get()
{
	gui::IGUIFont* f = m_GUIButton->getOverrideFont();
	return GUIFont::Wrap(f);
}

void GUIButton::OverrideFont::set(GUIFont^ value)
{
	m_GUIButton->setOverrideFont(LIME_SAFEREF(value, m_GUIFont));
}

bool GUIButton::Pressed::get()
{
	return m_GUIButton->isPressed();
}

void GUIButton::Pressed::set(bool value)
{
	m_GUIButton->setPressed(value);
}

bool GUIButton::PushButton::get()
{
	return m_GUIButton->isPushButton();
}

void GUIButton::PushButton::set(bool value)
{
	m_GUIButton->setIsPushButton(value);
}

bool GUIButton::ScaleImage::get()
{
	return m_GUIButton->isScalingImage();
}

void GUIButton::ScaleImage::set(bool value)
{
	m_GUIButton->setScaleImage(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime