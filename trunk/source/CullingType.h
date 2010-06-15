#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class CullingType
{
	Off = EAC_OFF,
	Box = EAC_BOX,
	FrustumBox = EAC_FRUSTUM_BOX,
	FrustumSphere = EAC_FRUSTUM_SPHERE
};

} // end namespace Scene
} // end namespace IrrlichtLime