#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;

namespace IrrlichtLime {
namespace Scene {

public enum class OctreeVBO
{
	NoVBO = EOV_NO_VBO,
	UseVBO = EOV_USE_VBO,
	USeVBOWithVisibility = EOV_USE_VBO_WITH_VISIBITLY
};

} // end namespace Scene
} // end namespace IrrlichtLime