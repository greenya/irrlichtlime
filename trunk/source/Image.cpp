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

bool Image::IsCompressedFormat(Video::ColorFormat format)
{
	return video::IImage::isCompressedFormat((ECOLOR_FORMAT)format);
}

bool Image::IsDepthFormat(Video::ColorFormat format)
{
	return video::IImage::isDepthFormat((ECOLOR_FORMAT)format);
}

bool Image::IsRenderTargetOnlyFormat(Video::ColorFormat format)
{
	return video::IImage::isRenderTargetOnlyFormat((ECOLOR_FORMAT)format);
}

System::Drawing::Imaging::PixelFormat Image::GetPixelFormat(Video::ColorFormat format)
{
	switch ((ECOLOR_FORMAT)format)
	{
	case ECF_A1R5G5B5:
		return System::Drawing::Imaging::PixelFormat::Format16bppArgb1555;

	case ECF_R5G6B5:
		return System::Drawing::Imaging::PixelFormat::Format16bppRgb565;

	case ECF_R8G8B8:
		return System::Drawing::Imaging::PixelFormat::Format24bppRgb;

	case ECF_A8R8G8B8:
		return System::Drawing::Imaging::PixelFormat::Format32bppArgb;

	case ECF_A16B16G16R16F:
		return System::Drawing::Imaging::PixelFormat::Format64bppArgb;

	case ECF_R16F:
	case ECF_G16R16F:
	case ECF_R32F:
	case ECF_G32R32F:
	case ECF_A32B32G32R32F:
	default:
		return System::Drawing::Imaging::PixelFormat::Undefined;
	}
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

void Image::CopyTo(Image^ target, Vector2Di targetPos, Recti sourceRect, Nullable<Recti> clipRect)
{
	LIME_ASSERT(target != nullptr);

	m_Image->copyTo(
		target->m_Image,
		targetPos,
		sourceRect,
		LIME_NULLABLE(clipRect));
}

void Image::CopyTo(Image^ target, Vector2Di targetPos, Recti sourceRect)
{
	LIME_ASSERT(target != nullptr);

	m_Image->copyTo(
		target->m_Image,
		targetPos,
		sourceRect);
}

void Image::CopyTo(Image^ target, Vector2Di targetPos)
{
	LIME_ASSERT(target != nullptr);

	m_Image->copyTo(
		target->m_Image,
		targetPos);
}

void Image::CopyTo(Image^ target)
{
	LIME_ASSERT(target != nullptr);
	m_Image->copyTo(target->m_Image);
}

array<unsigned char>^ Image::CopyTo()
{
	int s = m_Image->getImageDataSizeInBytes();
	array<unsigned char>^ r = gcnew array<unsigned char>(s);

	unsigned char* a = (unsigned char*)m_Image->getData();
	Marshal::Copy(IntPtr(a), r, 0, s);
	
	return r;
}

void Image::copyRBGFlip(void* source, void* dest, int count)
{
	const int blockLength = 12;	//how many bytes we process per loop

    int countRest = (count % blockLength) * blockLength;	//how many bytes we cannot process in the fast loop
    int countFast = count - countRest;	//how many bytes we can process in the fast loop

	//fast loop, read 3 * 4 bytes

	unsigned int* sourceUint = (unsigned int*)source;
	unsigned int* destUint = (unsigned int*)dest;

    for (int i = 0; i < countFast; i += blockLength)
    {
        int index = i/4;
        unsigned int sourceA = sourceUint[index];
        unsigned int sourceB = sourceUint[index + 1];
        unsigned int sourceC = sourceUint[index + 2];

        destUint[index] =
            (sourceA & 0x000000FFU) << 16 | (sourceA & 0x0000FF00U) |
            (sourceA & 0x00FF0000U) >> 16 | (sourceB & 0x0000FF00U) << 16;
        destUint[index + 1] =
            (sourceB & 0x000000FFU) |       (sourceA & 0xFF000000U) >> 16 |
            (sourceC & 0x000000FFU) << 16 | (sourceB & 0xFF000000U);
        destUint[index + 2] =
            (sourceB & 0x00FF0000U) >> 16 | (sourceC & 0xFF000000U) >> 16 |
            (sourceC & 0x00FF0000U) |       (sourceC & 0x0000FF00U) << 16;
    }

	//slow loop, to process the rest (if it does not

	unsigned char* sourceB = (unsigned char*)source;
    unsigned char* destB = (unsigned char*)dest;

    const int unitLength = 3;
    for (int i = countFast; i < count; i += unitLength)
    {
        for (int j = 0; j < unitLength; j++)
        {
            destB[i + j] = sourceB[i + (unitLength - 1) - j];
        }
    }
}

System::Drawing::Bitmap^ Image::CopyToBitmap()
{	
	/*if (GetPixelFormat(ColorFormat) == System::Drawing::Imaging::PixelFormat::Undefined)	//return null, if the format is not supported
		return nullptr;*/
	if (ColorFormat != Video::ColorFormat::R8G8B8 && ColorFormat != Video::ColorFormat::A8R8G8B8)	//only 24bit RGB and 32bit ARGB are supported
		return nullptr;

	System::Drawing::Imaging::PixelFormat pixelFormat;
	if (ColorFormat == Video::ColorFormat::R8G8B8)
		pixelFormat = System::Drawing::Imaging::PixelFormat::Format24bppRgb;
	else
		pixelFormat = System::Drawing::Imaging::PixelFormat::Format32bppArgb;

	System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(
		m_Image->getDimension().Width,
		m_Image->getDimension().Height,
		pixelFormat);

	System::Drawing::Imaging::BitmapData^ d = b->LockBits(
		System::Drawing::Rectangle(0, 0, b->Width, b->Height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		b->PixelFormat);

	if (ColorFormat == Video::ColorFormat::A8R8G8B8)
		memcpy(d->Scan0.ToPointer(), m_Image->getData(), d->Height * d->Stride);
	else //R8G8B8: we have to flip...
		copyRBGFlip(m_Image->getData(), d->Scan0.ToPointer(), d->Height * d->Stride);

	b->UnlockBits(d);
	return b;
}

void Image::CopyToScaling(Image^ target)
{
	LIME_ASSERT(target != nullptr);
	m_Image->copyToScaling(target->m_Image);
}

array<unsigned char>^ Image::CopyToScaling(int width, int height, Video::ColorFormat format, int pitch)
{
	LIME_ASSERT(width > 0);
	LIME_ASSERT(height > 0);
	LIME_ASSERT(pitch >= 0);

	int s = width * height * (video::IImage::getBitsPerPixelFromFormat((video::ECOLOR_FORMAT)format) / 8) + pitch * height;
	unsigned char* a = new unsigned char[s];

	m_Image->copyToScaling(
		a,
		width,
		height,
		(video::ECOLOR_FORMAT)format,
		pitch);

	array<unsigned char>^ r = gcnew array<unsigned char>(s);
	Marshal::Copy(IntPtr(a), r, 0, s);

	delete[] a;
	return r;
}

array<unsigned char>^ Image::CopyToScaling(int width, int height, Video::ColorFormat format)
{
	LIME_ASSERT(width > 0);
	LIME_ASSERT(height > 0);

	int s = width * height * (video::IImage::getBitsPerPixelFromFormat((video::ECOLOR_FORMAT)format) / 8);
	unsigned char* a = new unsigned char[s];

	m_Image->copyToScaling(
		a,
		width,
		height,
		(video::ECOLOR_FORMAT)format);

	array<unsigned char>^ r = gcnew array<unsigned char>(s);
	Marshal::Copy(IntPtr(a), r, 0, s);

	delete[] a;
	return r;
}

array<unsigned char>^ Image::CopyToScaling(int width, int height)
{
	LIME_ASSERT(width > 0);
	LIME_ASSERT(height > 0);

	int s = width * height * (video::IImage::getBitsPerPixelFromFormat(video::ECF_A8R8G8B8) / 8);
	unsigned char* a = new unsigned char[s];

	m_Image->copyToScaling(
		a,
		width,
		height);

	array<unsigned char>^ r = gcnew array<unsigned char>(s);
	Marshal::Copy(IntPtr(a), r, 0, s);

	delete[] a;
	return r;
}

void Image::CopyToScalingBoxFilter(Image^ target, int bias, bool blend)
{
	LIME_ASSERT(target != nullptr);
	m_Image->copyToScalingBoxFilter(target->m_Image, bias, blend);
}

void Image::CopyToScalingBoxFilter(Image^ target, int bias)
{
	LIME_ASSERT(target != nullptr);
	m_Image->copyToScalingBoxFilter(target->m_Image, bias);
}

void Image::CopyToScalingBoxFilter(Image^ target)
{
	LIME_ASSERT(target != nullptr);
	m_Image->copyToScalingBoxFilter(target->m_Image);
}

void Image::CopyToWithAlpha(Image^ target, Vector2Di targetPos, Recti sourceRect, Color color, Nullable<Recti> clipRect)
{
	LIME_ASSERT(target != nullptr);

	m_Image->copyToWithAlpha(
		target->m_Image,
		targetPos,
		sourceRect,
		color,
		LIME_NULLABLE(clipRect));
}

void Image::CopyToWithAlpha(Image^ target, Vector2Di targetPos, Recti sourceRect, Color color)
{
	LIME_ASSERT(target != nullptr);

	m_Image->copyToWithAlpha(
		target->m_Image,
		targetPos,
		sourceRect,
		color);
}

void Image::Fill(Color color)
{
	m_Image->fill(color);
}

Color Image::GetPixel(int x, int y)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);

	return Color(m_Image->getPixel(x, y));
}

IntPtr Image::GetData()
{
	return IntPtr(m_Image->getData());
}


void Image::SetPixel(int x, int y, Color color, bool blend)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);

	m_Image->setPixel(x, y, color, blend);
}

void Image::SetPixel(int x, int y, Color color)
{
	LIME_ASSERT(x >= 0 && x < Dimension->Width);
	LIME_ASSERT(y >= 0 && y < Dimension->Height);

	m_Image->setPixel(x, y, color);
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

bool Image::Compressed::get()
{
	return m_Image->isCompressed();
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

bool Image::MipMaps::get()
{
	return m_Image->hasMipMaps();
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