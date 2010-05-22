#pragma once

#include "stdafx.h"
#include "Image.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

Image::Image(video::IImage* image)
{
	LIME_ASSERT(image != nullptr);
	m_Image = image;
}

void Image::Fill(Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	m_Image->fill(*color->m_NativeValue);
}

unsigned int Image::GetBitsPerPixelFromFormat(Video::ColorFormat format)
{
	return video::IImage::getBitsPerPixelFromFormat((ECOLOR_FORMAT)format);
}

Coloru^ Image::GetPixel(unsigned int x, unsigned int y)
{
	return gcnew Coloru(m_Image->getPixel(x, y));
}

bool Image::IsRenderTargetOnlyFormat(Video::ColorFormat format)
{
	return video::IImage::isRenderTargetOnlyFormat((ECOLOR_FORMAT)format);
}

void Image::SetPixel(unsigned int x, unsigned int y, Coloru^ color, bool blend)
{
	LIME_ASSERT(color != nullptr);
	m_Image->setPixel(x, y, *color->m_NativeValue, blend);
}

void Image::SetPixel(unsigned int x, unsigned int y, Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	m_Image->setPixel(x, y, *color->m_NativeValue);
}

unsigned int Image::BitsPerPixel::get()
{
	return m_Image->getBitsPerPixel();
}

unsigned int Image::BytesPerPixel::get()
{
	return m_Image->getBytesPerPixel();
}

Video::ColorFormat Image::ColorFormat::get()
{
	return (Video::ColorFormat)m_Image->getColorFormat();
}

Dimension2Du^ Image::Dimension::get()
{
	return gcnew Dimension2Du(m_Image->getDimension());
}

unsigned int Image::ImageDataSizeInBytes::get()
{
	return m_Image->getImageDataSizeInBytes();
}

unsigned int Image::ImageDataSizeInPixels::get()
{
	return m_Image->getImageDataSizeInPixels();
}

unsigned int Image::RedMask::get()
{
	return m_Image->getRedMask();
}

unsigned int Image::GreenMask::get()
{
	return m_Image->getGreenMask();
}

unsigned int Image::BlueMask::get()
{
	return m_Image->getBlueMask();
}

unsigned int Image::AlphaMask::get()
{
	return m_Image->getAlphaMask();
}

unsigned int Image::Pitch::get()
{
	return m_Image->getPitch();
}

} // end namespace Video
} // end namespace IrrlichtLime