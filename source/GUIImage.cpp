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

void GUIImage::SetColor(Video::Color^ color)
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