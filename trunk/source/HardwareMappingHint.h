#pragma once

#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class HardwareMappingHint
{
	Never = EHM_NEVER,
	Static = EHM_STATIC,
	Dynamic = EHM_DYNAMIC,
	Stream = EHM_STREAM
};

} // end namespace Scene
} // end namespace IrrlichtLime