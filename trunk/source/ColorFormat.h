#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ColorFormat
{
	A1R5G5B5 = ECF_A1R5G5B5,
	R5G6B5 = ECF_R5G6B5,
	R8G8B8 = ECF_R8G8B8,
	A8R8G8B8 = ECF_A8R8G8B8,
	R16F = ECF_R16F,
	G16R16F = ECF_G16R16F,
	A16B16G16R16F = ECF_A16B16G16R16F,
	R32F = ECF_R32F,
	G32R32F = ECF_G32R32F,
	A32B32G32R32F = ECF_A32B32G32R32F,
	Unknown = ECF_UNKNOWN
};

} // end namespace Video
} // end namespace IrrlichtLime