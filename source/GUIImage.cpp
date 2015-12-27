#include "stdafx.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "Texture.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIImage^ GUIImage::Wrap(gui::IGUIImage* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIImage(ref);
}

GUIImage::GUIImage(gui::IGUIImage* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIImage = ref;
}

bool GUIImage::AlphaChannel::get()
{
	return m_GUIImage->isAlphaChannelUsed();
}

void GUIImage::AlphaChannel::set(bool value)
{
	m_GUIImage->setUseAlphaChannel(value);
}

Video::Color GUIImage::Color::get()
{
	return Video::Color(m_GUIImage->getColor());
}

void GUIImage::Color::set(Video::Color value)
{
	m_GUIImage->setColor(value);
}

Rectf GUIImage::DrawBounds::get()
{
	return Rectf(m_GUIImage->getDrawBounds());
}

void GUIImage::DrawBounds::set(Rectf value)
{
	m_GUIImage->setDrawBounds(value);
}

Video::Texture^ GUIImage::Image::get()
{
	video::ITexture* i = m_GUIImage->getImage();
	return Video::Texture::Wrap(i);
}

void GUIImage::Image::set(Video::Texture^ value)
{
	m_GUIImage->setImage(LIME_SAFEREF(value, m_Texture));
}

bool GUIImage::ScaleImage::get()
{
	return m_GUIImage->isImageScaled();
}

void GUIImage::ScaleImage::set(bool value)
{
	m_GUIImage->setScaleImage(value);
}

Recti GUIImage::SourceRect::get()
{
	return Recti(m_GUIImage->getSourceRect());
}

void GUIImage::SourceRect::set(Recti value)
{
	m_GUIImage->setSourceRect(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime