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

	Color GetPixel(int x, int y);
	
	bool Lock(TextureLockMode lockMode, int layer);
	bool Lock(TextureLockMode lockMode);
	bool Lock();

	void SetLine(int x1, int y1, int x2, int y2, Color color);
	void SetPixel(int x, int y, Color color);

	void Unlock(bool alsoRegenerateMipMapLevels);
	void Unlock();

	property bool Locked { bool get(); }
	property TextureLockMode LockMode { TextureLockMode get(); }
	property int LockLayer { int get(); }
	property System::IntPtr Pointer { System::IntPtr get(); }	
	property Video::Texture^ Texture { Video::Texture^ get(); }


	//Obsolete:
	[Obsolete("Does not have an actual use anymore, as MipMap layers can't be locked anymore.", false)]
	property int MipMapLevelCount { int get(); }
	[Obsolete("MipMap layers can't be locked anymore. Use Texture.Size.Height instead.", false)]
	property int MipMapLevelHeight { int get(); }
	[Obsolete("MipMap layers can't be locked anymore. Use Texture.Size.Width instead.", false)]
	property int MipMapLevelWidth { int get(); }
	[Obsolete("MipMap layers can't be locked anymore. Use TexturePainter.Pointer instead.", false)]
	property System::IntPtr MipMapLevelData { System::IntPtr get() { return Pointer; } }

	virtual String^ ToString() override;

internal:

	TexturePainter(Video::Texture^ texture);

private:

	Video::Texture^ m_texture;
	TextureLockMode m_lockMode;
	void* m_pointer;
	video::ECOLOR_FORMAT m_format;
	int m_rowSize;
	int m_pixelSize;
	int m_lockLayer;
	int m_mipmapLevelCount;
};

} // end namespace Video
} // end namespace IrrlichtLime