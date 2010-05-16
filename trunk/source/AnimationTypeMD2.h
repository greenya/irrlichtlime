#pragma once

#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class AnimationTypeMD2
{
	Stand = EMAT_STAND,
	Run = EMAT_RUN,
	Attack = EMAT_ATTACK,
	Pain_A = EMAT_PAIN_A,
	Pain_B = EMAT_PAIN_B,
	Pain_C = EMAT_PAIN_C,
	Jump = EMAT_JUMP,
	Flip = EMAT_FLIP,
	Salute = EMAT_SALUTE,
	Fallback = EMAT_FALLBACK,
	Wave = EMAT_WAVE,
	Point = EMAT_POINT,
	Crouch_Stand = EMAT_CROUCH_STAND,
	Crouch_Walk = EMAT_CROUCH_WALK,
	Crouch_Attack = EMAT_CROUCH_ATTACK,
	Crouch_Pain = EMAT_CROUCH_PAIN,
	Crouch_Death = EMAT_CROUCH_DEATH,
	Death_Fall_Back = EMAT_DEATH_FALLBACK,
	Death_Fall_Forward = EMAT_DEATH_FALLFORWARD,
	Death_Fall_Back_Slow = EMAT_DEATH_FALLBACKSLOW,
	Boom = EMAT_BOOM
};

} // end namespace Scene
} // end namespace IrrlichtLime