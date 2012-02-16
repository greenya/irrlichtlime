#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class GPUShadingLanguage
{
	Default = EGSL_DEFAULT,
	Cg = EGSL_CG
};

} // end namespace Video
} // end namespace IrrlichtLime