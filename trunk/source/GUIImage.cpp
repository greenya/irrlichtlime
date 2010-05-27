#include "stdafx.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "Texture.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIImage::GUIImage(gui::IGUIImage* guiImage)
	: GUIElement(guiImage)
{
	LIME_ASSERT(guiImage != nullptr);
	m_GUIImage = guiImage;
}

void GUIImage::SetColor(Video::Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	m_GUIImage->setColor(*color->m_NativeValue);
}

void GUIImage::SetImage(Video::Texture^ image)
{
	m_GUIImage->setImage(LIME_SAFEREF(image, m_Texture));
}

bool GUIImage::AlphaChannel::get()
{
	return m_GUIImage->isAlphaChannelUsed();
}

void GUIImage::AlphaChannel::set(bool value)
{
	m_GUIImage->setUseAlphaChannel(value);
}

bool GUIImage::ScaleImage::get()
{
	return m_GUIImage->isImageScaled();
}

void GUIImage::ScaleImage::set(bool value)
{
	m_GUIImage->setScaleImage(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime