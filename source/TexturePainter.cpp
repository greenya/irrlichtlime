#include "stdafx.h"
#include "Image.h"
#include "Texture.h"
#include "TexturePainter.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

TexturePainter::TexturePainter(Video::Texture^ texture)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(Image::GetBitsPerPixelFromFormat(texture->ColorFormat) / 8 > 0);

	m_texture = texture;
	m_format = texture->m_Texture->getColorFormat();
	m_rowSize = texture->m_Texture->getPitch();
	m_pixelSize = video::IImage::getBitsPerPixelFromFormat(texture->m_Texture->getColorFormat()) / 8;

	core::dimension2du d = texture->m_Texture->getSize();
	int m = d.Width < d.Height ? d.Width : d.Height;
	m_mipmapLevelCount = (int)ceil(log((float)m) / log(2.0f)) + 1;
	m_lockLayer = -1;
}

Color TexturePainter::GetPixel(int x, int y)
{
	LIME_ASSERT(Locked);
	LIME_ASSERT(LockMode == TextureLockMode::ReadWrite || LockMode == TextureLockMode::ReadOnly);
	LIME_ASSERT(x >= 0 && x < (int)m_texture->m_Texture->getSize().Width);
	LIME_ASSERT(y >= 0 && y < (int)m_texture->m_Texture->getSize().Height);

	Color c = Color();
	c.SetData(
		(unsigned char*)m_pointer + y * m_rowSize + x * m_pixelSize,
		(ColorFormat)m_format);

	return c;
}

bool TexturePainter::Lock(TextureLockMode lockMode, int layer)
{
	LIME_ASSERT(layer >= 0 && layer < m_mipmapLevelCount);

	m_pointer = m_texture->m_Texture->lock((video::E_TEXTURE_LOCK_MODE)lockMode, layer);
	if (m_pointer == nullptr)
		return false;

	m_lockMode = lockMode;
	m_lockLayer = layer;

	return true;
}

bool TexturePainter::Lock(TextureLockMode lockMode)
{
	m_pointer = m_texture->m_Texture->lock((video::E_TEXTURE_LOCK_MODE)lockMode);
	if (m_pointer == nullptr)
		return false;

	m_lockMode = lockMode;
	m_lockLayer = 0;

	return true;
}

bool TexturePainter::Lock()
{
	m_pointer = m_texture->m_Texture->lock();
	if (m_pointer == nullptr)
		return false;

	m_lockMode = TextureLockMode::ReadWrite;
	m_lockLayer = 0;

	return true;
}

void TexturePainter::SetLine(int x1, int y1, int x2, int y2, Color color)
{
	LIME_ASSERT(Locked);
	LIME_ASSERT(LockMode == TextureLockMode::ReadWrite || LockMode == TextureLockMode::WriteOnly);
	LIME_ASSERT(x1 >= 0 && x1 < (int)m_texture->m_Texture->getSize().Width);
	LIME_ASSERT(y1 >= 0 && y1 < (int)m_texture->m_Texture->getSize().Height);
	LIME_ASSERT(x2 >= 0 && x2 < (int)m_texture->m_Texture->getSize().Width);
	LIME_ASSERT(y2 >= 0 && y2 < (int)m_texture->m_Texture->getSize().Height);

	bool t = abs(y2 - y1) > abs(x2 - x1);

	if (t)
	{
		x1 ^= y1; y1 ^= x1; x1 ^= y1; // swap x1, y1
		x2 ^= y2; y2 ^= x2; x2 ^= y2; // swap x2, y2
	}

	if (x1 > x2)
	{
		x1 ^= x2; x2 ^= x1; x1 ^= x2; // swap x1, x2
		y1 ^= y2; y2 ^= y1; y1 ^= y2; // swap y1, y2
	}

	int dx = x2 - x1;
	int dy = abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int e = dx / 2;
	int y = y1;

	for (int x = x1; x <= x2; x++)
	{
		if (t)
			color.GetData(
				(unsigned char*)m_pointer + x * m_rowSize + y * m_pixelSize, // set pixel to y,x
				(ColorFormat)m_format);
		else
			color.GetData(
				(unsigned char*)m_pointer + y * m_rowSize + x * m_pixelSize, // set pixel to x,y
				(ColorFormat)m_format);

		e -= dy;
		if (e < 0)
		{
			y += sy;
			e += dx;
		}
	}
}

void TexturePainter::SetPixel(int x, int y, Color color)
{
	LIME_ASSERT(Locked);
	LIME_ASSERT(LockMode == TextureLockMode::ReadWrite || LockMode == TextureLockMode::WriteOnly);
	LIME_ASSERT(x >= 0 && x < (int)m_texture->m_Texture->getSize().Width);
	LIME_ASSERT(y >= 0 && y < (int)m_texture->m_Texture->getSize().Height);

	color.GetData(
		(unsigned char*)m_pointer + y * m_rowSize + x * m_pixelSize,
		(ColorFormat)m_format);
}

void TexturePainter::Unlock(bool alsoRegenerateMipMapLevels)
{
	LIME_ASSERT(Locked);

	m_texture->m_Texture->unlock();

	if (alsoRegenerateMipMapLevels)
		m_texture->m_Texture->regenerateMipMapLevels();

	m_lockLayer = -1;
	m_pointer = nullptr;
}

void TexturePainter::Unlock()
{
	LIME_ASSERT(Locked);

	m_texture->m_Texture->unlock();
	m_lockLayer = -1;
	m_pointer = nullptr;
}

bool TexturePainter::Locked::get()
{
	return m_lockLayer != -1;
}

TextureLockMode TexturePainter::LockMode::get()
{
	LIME_ASSERT(Locked);
	return m_lockMode;
}

int TexturePainter::LockLayer::get()
{
	LIME_ASSERT(Locked);
	return m_lockLayer;
}

int TexturePainter::MipMapLevelCount::get()
{
	return m_mipmapLevelCount;
}

int TexturePainter::MipMapLevelHeight::get()
{
	LIME_ASSERT(Locked);
	return m_texture->m_Texture->getSize().Height;
}

System::IntPtr TexturePainter::Pointer::get()
{
	LIME_ASSERT(Locked);
	return System::IntPtr(m_pointer);
}

int TexturePainter::MipMapLevelWidth::get()
{
	LIME_ASSERT(Locked);
	return m_texture->m_Texture->getSize().Width;
}

Video::Texture^ TexturePainter::Texture::get()
{
	return m_texture;
}

String^ TexturePainter::ToString()
{
	if (Locked)
	{
		return String::Format("TexturePainter: [Locked] <{0}> Layer#{1}: {2}x{3}",
			m_lockMode,
			m_lockLayer,
			m_texture->m_Texture->getSize().Width,
			m_texture->m_Texture->getSize().Height);
	}
	else
	{
		return String::Format("TexturePainter: [Unlocked]");
	}
}

} // end namespace Video
} // end namespace IrrlichtLime