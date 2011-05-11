#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class TextureClamp
{
	Repeat = ETC_REPEAT,
	Clamp = ETC_CLAMP,
	ClampToEdge = ETC_CLAMP_TO_EDGE,
	ClampToBorder = ETC_CLAMP_TO_BORDER,
	Mirror = ETC_MIRROR,
	MirrorClamp = ETC_MIRROR_CLAMP,
	MirrorClampToEdge = ETC_MIRROR_CLAMP_TO_EDGE,
	MirrorClampToBorder = ETC_MIRROR_CLAMP_TO_BORDER
};

} // end namespace Video
} // end namespace IrrlichtLime