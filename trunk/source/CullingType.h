#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

[Flags]
public enum class CullingType
{
	Off = EAC_OFF,
	Box = EAC_BOX,
	FrustumBox = EAC_FRUSTUM_BOX,
	FrustumSphere = EAC_FRUSTUM_SPHERE,
	OcclusionQuery = EAC_OCC_QUERY
};

} // end namespace Scene
} // end namespace IrrlichtLime