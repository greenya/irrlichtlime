#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class VertexShaderType
{
	VS_1_1 = EVST_VS_1_1,
	VS_2_0 = EVST_VS_2_0,
	VS_2_a = EVST_VS_2_a,
	VS_3_0 = EVST_VS_3_0,
	VS_4_0 = EVST_VS_4_0,
	VS_4_1 = EVST_VS_4_1,
	VS_5_0 = EVST_VS_5_0
};

} // end namespace Video
} // end namespace IrrlichtLime