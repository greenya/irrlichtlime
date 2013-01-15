#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ComparisonFunc
{
	Disabled = ECFN_DISABLED,
	LessEqual = ECFN_LESSEQUAL,
	Equal = ECFN_EQUAL,
	Less = ECFN_LESS,
	NotEqual = ECFN_NOTEQUAL,
	GreaterEqual = ECFN_GREATEREQUAL,
	Greater = ECFN_GREATER,
	Always = ECFN_ALWAYS,
	Never = ECFN_NEVER
};

} // end namespace Video
} // end namespace IrrlichtLime