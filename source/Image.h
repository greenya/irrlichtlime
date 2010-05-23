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

	static unsigned int GetBitsPerPixelFromFormat(Video::ColorFormat format);
	static bool IsRenderTargetOnlyFormat(Video::ColorFormat format);

	void Fill(Coloru^ color);
	Coloru^ GetPixel(unsigned int x, unsigned int y);
	void SetPixel(unsigned int x, unsigned int y, Coloru^ color, bool blend);
	void SetPixel(unsigned int x, unsigned int y, Coloru^ color);

	property unsigned int BitsPerPixel { unsigned int get(); }
	property unsigned int BytesPerPixel { unsigned int get(); }
	property Video::ColorFormat ColorFormat { Video::ColorFormat get(); }
	property Dimension2Du^ Dimension { Dimension2Du^ get(); }
	property unsigned int ImageDataSizeInBytes { unsigned int get(); }
	property unsigned int ImageDataSizeInPixels { unsigned int get(); }

	property unsigned int RedMask { unsigned int get(); }
	property unsigned int GreenMask { unsigned int get(); }
	property unsigned int BlueMask { unsigned int get(); }
	property unsigned int AlphaMask { unsigned int get(); }
	property unsigned int Pitch { unsigned int get(); }

internal:

	Image(video::IImage* image);

	video::IImage* m_Image;
};

} // end namespace Video
} // end namespace IrrlichtLime