#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ComparisonFunc
{
	Never = ECFN_NEVER,
	LessEqual = ECFN_LESSEQUAL,
	Equal = ECFN_EQUAL,
	Less = ECFN_LESS,
	NotEqual = ECFN_NOTEQUAL,
	GreaterEqual = ECFN_GREATEREQUAL,
	Greater = ECFN_GREATER,
	Always = ECFN_ALWAYS
};

} // end namespace Video
} // end namespace IrrlichtLime