#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public enum class KeyAction
{
	MoveForward = EKA_MOVE_FORWARD,
	MoveBackward = EKA_MOVE_BACKWARD,
	StrafeLeft = EKA_STRAFE_LEFT,
	StrafeRight = EKA_STRAFE_RIGHT,
	Jump = EKA_JUMP_UP,
	Crouch = EKA_CROUCH
};

} // end namespace IrrlichtLime