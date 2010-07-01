#include "stdafx.h"
#include "Image.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

int Image::GetBitsPerPixelFromFormat(Video::ColorFormat format)
{
	return video::IImage::getBitsPerPixelFromFormat((ECOLOR_FORMAT)format);
}

bool Image::IsRenderTargetOnlyFormat(Video::ColorFormat format)
{
	return video::IImage::isRenderTargetOnlyFormat((ECOLOR_FORMAT)format);
}

Image^ Image::Wrap(video::IImage* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew Image(ref);
}

Image::Image(video::IImage* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_Image = ref;
}

void Image::Fill(Color^ color)
{
	LIME_ASSERT(color != nullptr);
	m_Image->fill(*color->m_NativeValue);
}

Color^ Image::GetPixel(int x, int y)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);

	return gcnew Color(m_Image->getPixel(x, y));
}

void Image::SetPixel(int x, int y, Color^ color, bool blend)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);
	LIME_ASSERT(color != nullptr);

	m_Image->setPixel(x, y, *color->m_NativeValue, blend);
}

void Image::SetPixel(int x, int y, Color^ color)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);
	LIME_ASSERT(color != nullptr);

	m_Image->setPixel(x, y, *color->m_NativeValue);
}

int Image::BitsPerPixel::get()
{
	return m_Image->getBitsPerPixel();
}

int Image::BytesPerPixel::get()
{
	return m_Image->getBytesPerPixel();
}

Video::ColorFormat Image::ColorFormat::get()
{
	return (Video::ColorFormat)m_Image->getColorFormat();
}

Dimension2Di^ Image::Dimension::get()
{
	return gcnew Dimension2Di(m_Image->getDimension());
}

int Image::ImageDataSizeInBytes::get()
{
	return m_Image->getImageDataSizeInBytes();
}

int Image::ImageDataSizeInPixels::get()
{
	return m_Image->getImageDataSizeInPixels();
}

int Image::RedMask::get()
{
	return m_Image->getRedMask();
}

int Image::GreenMask::get()
{
	return m_Image->getGreenMask();
}

int Image::BlueMask::get()
{
	return m_Image->getBlueMask();
}

int Image::AlphaMask::get()
{
	return m_Image->getAlphaMask();
}

int Image::Pitch::get()
{
	return m_Image->getPitch();
}

String^ Image::ToString()
{
	return String::Format("Image: Dimension={0}; ColorFormat={1}", Dimension, ColorFormat);
}

} // end namespace Video
} // end namespace IrrlichtLime