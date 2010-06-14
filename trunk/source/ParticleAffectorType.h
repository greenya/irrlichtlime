#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class ParticleAffectorType
{
	None = EPAT_NONE,
	Attract = EPAT_ATTRACT,
	FadeOut = EPAT_FADE_OUT,
	Gravity = EPAT_GRAVITY,
	Rotate = EPAT_ROTATE,
	Scale = EPAT_SCALE
};

} // end namespace Scene
} // end namespace IrrlichtLime