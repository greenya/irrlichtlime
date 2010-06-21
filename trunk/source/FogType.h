#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class FogType
{
	Exp = EFT_FOG_EXP,
	Linear = EFT_FOG_LINEAR,
	Exp2 = EFT_FOG_EXP2
};

} // end namespace Video
} // end namespace IrrlichtLime