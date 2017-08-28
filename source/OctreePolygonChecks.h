#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;

namespace IrrlichtLime {
namespace Scene {

public enum class OctreePolygonChecks
{
	Box = EOPC_BOX,
	Frustum = EOPC_FRUSTUM
};

} // end namespace Scene
} // end namespace IrrlichtLime