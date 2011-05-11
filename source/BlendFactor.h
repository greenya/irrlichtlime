#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class BlendFactor
{
	Zero = EBF_ZERO,
	One = EBF_ONE,
	DstColor = EBF_DST_COLOR,
	OneMinusDstColor = EBF_ONE_MINUS_DST_COLOR,
	SrcColor = EBF_SRC_COLOR,
	OneMinusSrcColor = EBF_ONE_MINUS_SRC_COLOR,
	SrcAlpha = EBF_SRC_ALPHA,
	OneMinusSrcAlpha = EBF_ONE_MINUS_SRC_ALPHA,
	DstAlpha = EBF_DST_ALPHA,
	OneMinusDstAlpha = EBF_ONE_MINUS_DST_ALPHA,
	SrcAlphaSaturate = EBF_SRC_ALPHA_SATURATE
};

} // end namespace Video
} // end namespace IrrlichtLime