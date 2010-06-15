#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class BoneAnimationMode
{
	Automatic = EBAM_AUTOMATIC,
	Animated = EBAM_ANIMATED,
	NotAnimated = EBAM_UNANIMATED
};

} // end namespace Scene
} // end namespace IrrlichtLime