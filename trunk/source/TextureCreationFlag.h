#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[Flags]
public enum class TextureCreationFlag : unsigned int
{
	Always16Bit = ETCF_ALWAYS_16_BIT,
	Always32Bit = ETCF_ALWAYS_32_BIT,
	OptimizedForQuality = ETCF_OPTIMIZED_FOR_QUALITY,
	OptimizedForSpeed = ETCF_OPTIMIZED_FOR_SPEED,
	CreateMipMaps = ETCF_CREATE_MIP_MAPS,
	NoAlphaChannel = ETCF_NO_ALPHA_CHANNEL,
	AllowNonPower2 = ETCF_ALLOW_NON_POWER_2
};

} // end namespace Video
} // end namespace IrrlichtLime