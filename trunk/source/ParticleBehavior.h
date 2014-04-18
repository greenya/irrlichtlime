#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

[Flags]
public enum class ParticleBehavior
{
	InvisibleEmitting = EPB_INVISIBLE_EMITTING,
	InvisibleAffecting = EPB_INVISIBLE_AFFECTING,
	InvisibleAnimating = EPB_INVISIBLE_ANIMATING,
	ClearOnInvisible = EPB_CLEAR_ON_INVISIBLE,
	EmitterVectorIgnoreRotation = EPB_EMITTER_VECTOR_IGNORE_ROTATION,
	EmitterFrameInterpolation = EPB_EMITTER_FRAME_INTERPOLATION
};

} // end namespace Scene
} // end namespace IrrlichtLime