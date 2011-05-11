#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class BlendOperation
{
	None = EBO_NONE,
	Add = EBO_ADD,
	Subtract = EBO_SUBTRACT,
	RevSubtract = EBO_REVSUBTRACT,
	Min = EBO_MIN,
	Max = EBO_MAX,
	MinFactor = EBO_MIN_FACTOR,
	MaxFactor = EBO_MAX_FACTOR,
	MinAlpha = EBO_MIN_ALPHA,
	MaxAlpha = EBO_MAX_ALPHA
};

} // end namespace Video
} // end namespace IrrlichtLime