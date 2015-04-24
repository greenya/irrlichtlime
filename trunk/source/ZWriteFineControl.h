#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ZWriteFineControl
{
	OnlyNonTransparent = EZI_ONLY_NON_TRANSPARENT,
	ZBufferFlag = EZI_ZBUFFER_FLAG
};

} // end namespace Video
} // end namespace IrrlichtLime