#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

[Flags]
public enum class SceneNodeRenderPass
{
	None = ESNRP_NONE,
	Camera = ESNRP_CAMERA,
	Light = ESNRP_LIGHT,
	SkyBox = ESNRP_SKY_BOX,
	Automatic = ESNRP_AUTOMATIC,
	Solid = ESNRP_SOLID,
	Transparent = ESNRP_TRANSPARENT,
	TransparentEffect = ESNRP_TRANSPARENT_EFFECT,
	Shadow = ESNRP_SHADOW
};

} // end namespace Scene
} // end namespace IrrlichtLime