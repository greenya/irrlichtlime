#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class LightType
{
	Point = ELT_POINT,
	Spot = ELT_SPOT,
	Directional = ELT_DIRECTIONAL
};

} // end namespace Video
} // end namespace IrrlichtLime