#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class Image : ReferenceCounted
{
public:

	static int GetBitsPerPixelFromFormat(Video::ColorFormat format);
	static bool IsRenderTargetOnlyFormat(Video::ColorFormat format);

	void Fill(Color^ color);
	Color^ GetPixel(int x, int y);
	void SetPixel(int x, int y, Color^ color, bool blend);
	void SetPixel(int x, int y, Color^ color);

	property int BitsPerPixel { int get(); }
	property int BytesPerPixel { int get(); }
	property Video::ColorFormat ColorFormat { Video::ColorFormat get(); }
	property Dimension2Di^ Dimension { Dimension2Di^ get(); }
	property int ImageDataSizeInBytes { int get(); }
	property int ImageDataSizeInPixels { int get(); }

	property int RedMask { int get(); }
	property int GreenMask { int get(); }
	property int BlueMask { int get(); }
	property int AlphaMask { int get(); }
	property int Pitch { int get(); }

	virtual String^ ToString() override;

internal:

	static Image^ Wrap(video::IImage* ref);
	Image(video::IImage* ref);

	video::IImage* m_Image;
};

} // end namespace Video
} // end namespace IrrlichtLime