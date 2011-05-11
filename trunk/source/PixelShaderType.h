#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class PixelShaderType
{
	PS_1_1 = EPST_PS_1_1,
	PS_1_2 = EPST_PS_1_2,
	PS_1_3 = EPST_PS_1_3,
	PS_1_4 = EPST_PS_1_4,
	PS_2_0 = EPST_PS_2_0,
	PS_2_a = EPST_PS_2_a,
	PS_2_b = EPST_PS_2_b,
	PS_3_0 = EPST_PS_3_0,
	PS_4_0 = EPST_PS_4_0,
	PS_4_1 = EPST_PS_4_1,
	PS_5_0 = EPST_PS_5_0
};

} // end namespace Video
} // end namespace IrrlichtLime