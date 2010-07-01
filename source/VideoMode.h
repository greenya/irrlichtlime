#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public value class VideoMode
{
public:
	int Depth;
	Dimension2Di^ Resolution;

	VideoMode(Dimension2Di^ resolution, int depth)
	{
		LIME_ASSERT(resolution->Width > 0);
		LIME_ASSERT(resolution->Height > 0);
		LIME_ASSERT(depth > 0);

		Resolution = resolution;
		Depth = depth;
	}

	VideoMode(int width, int height, int depth)
	{
		LIME_ASSERT(width > 0);
		LIME_ASSERT(height > 0);
		LIME_ASSERT(depth > 0);

		Resolution = gcnew Dimension2Di(width, height);
		Depth = depth;
	}

	virtual String^ ToString() override
	{
		return String::Format("{0} x {1} x {2}bpp", Resolution->Width, Resolution->Height, Depth);
	}

internal:

	VideoMode(const core::dimension2di& resolution, int depth)
		: Resolution(gcnew Dimension2Di(resolution))
		, Depth(depth) {}
};

} // end namespace Video
} // end namespace IrrlichtLime