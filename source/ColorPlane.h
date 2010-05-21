#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[Flags]
public enum class ColorPlane
{
	None = ECP_NONE,
	Alpha = ECP_ALPHA,
	Red = ECP_RED,
	Green = ECP_GREEN,
	Blue = ECP_BLUE,
	RGB = ECP_RGB,
	All = ECP_ALL
};

} // end namespace Video
} // end namespace IrrlichtLime