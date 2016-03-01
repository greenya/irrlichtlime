#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[Flags]
public enum class ClearBufferFlag
{
	None = ECBF_NONE,
	Color = ECBF_COLOR,
	Depth = ECBF_DEPTH,
	Stencil = ECBF_STENCIL,
	All = ECBF_ALL
};

} // end namespace Video
} // end namespace IrrlichtLime