#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class SceneNodeAnimatorType
{
	FlyCircle = ESNAT_FLY_CIRCLE,
	FlyStraight = ESNAT_FLY_STRAIGHT,
	FollowSpline = ESNAT_FOLLOW_SPLINE,
	Rotation = ESNAT_ROTATION,
	Texture = ESNAT_TEXTURE,
	Deletion = ESNAT_DELETION,
	CollisionResponse = ESNAT_COLLISION_RESPONSE,
	CameraFPS = ESNAT_CAMERA_FPS,
	CameraMaya = ESNAT_CAMERA_MAYA,
	Unknown = ESNAT_UNKNOWN
};

} // end namespace Scene
} // end namespace IrrlichtLime