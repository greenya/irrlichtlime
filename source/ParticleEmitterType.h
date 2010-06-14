#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class ParticleEmitterType
{
	Point = EPET_POINT,
	AnimatedMesh = EPET_ANIMATED_MESH,
	Box = EPET_BOX,
	Cylinder = EPET_CYLINDER,
	Mesh = EPET_MESH,
	Ring = EPET_RING,
	Sphere = EPET_SPHERE
};

} // end namespace Scene
} // end namespace IrrlichtLime