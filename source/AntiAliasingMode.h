#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[Flags]
public enum class AntiAliasingMode
{
	Off = EAAM_OFF,
	Simple = EAAM_SIMPLE,
	Quality = EAAM_QUALITY,
	LineSmooth = EAAM_LINE_SMOOTH,
	PointSmooth = EAAM_POINT_SMOOTH,
	FullBasic = EAAM_FULL_BASIC,
	AlphaToCoverage = EAAM_ALPHA_TO_COVERAGE
};

} // end namespace Video
} // end namespace IrrlichtLime