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
	Dimension2Du^ Resolution;

	VideoMode(Dimension2Du^ resolution, int depth) : Resolution(resolution), Depth(depth) {}
	VideoMode(int width, int height, int depth) : Resolution(gcnew Dimension2Du(width, height)), Depth(depth) {}

	virtual String^ ToString() override
	{
		return String::Format("{0}x{1}x{2}", Resolution->Width, Resolution->Height, Depth);
	}

internal:

	VideoMode(const core::dimension2du& resolution, int depth) : Resolution(gcnew Dimension2Du(resolution)), Depth(depth) {}
};

} // end namespace Video
} // end namespace IrrlichtLime