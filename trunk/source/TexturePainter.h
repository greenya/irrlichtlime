#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class Texture;

public ref class TexturePainter
{
public:

	Color^ GetPixel(int x, int y);
	
	bool Lock(bool readOnly, int mipmapLevel);
	bool Lock(bool readOnly);
	bool Lock();

	void SetPixel(int x, int y, Color^ color);

	void Unlock(bool alsoRegenerateMipMapLevels);
	void Unlock();

	property bool Locked { bool get(); }
	property int MipMapLevel { int get(); }
	property int MipMapLevelCount { int get(); }
	property int MipMapLevelHeight { int get(); }
	property int MipMapLevelWidth { int get(); }
	property bool ReadOnly { bool get(); }
	property Video::Texture^ Texture { Video::Texture^ get(); }

	virtual String^ ToString() override;

internal:

	TexturePainter(Video::Texture^ texture);

private:

	Video::Texture^ m_texture;
	bool m_readOnly;
	void* m_pointer;
	video::ECOLOR_FORMAT m_format;
	int m_rowSize;
	int m_pixelSize;
	int m_mipmapLevel;
	int m_mipmapLevelCount;
	int m_mipmapLevelWidth;
	int m_mipmapLevelHeight;
};

} // end namespace Video
} // end namespace IrrlichtLime