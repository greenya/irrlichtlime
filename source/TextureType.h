#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class TextureType
{
	Flat = ETT_2D,	//2D does not compile, _2D looks horrible and TwoD is hard to understand. And in Blender it's also called flat.
	Cubemap = ETT_CUBEMAP
};

} // end namespace Video
} // end namespace IrrlichtLime