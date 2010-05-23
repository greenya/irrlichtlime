#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class PrimitiveType
{
	Points = EPT_POINTS,
	LineStrip = EPT_LINE_STRIP,
	LineLoop = EPT_LINE_LOOP,
	Lines = EPT_LINES,
	TriangleStrip = EPT_TRIANGLE_STRIP,
	TriangleFan = EPT_TRIANGLE_FAN,
	Triangles = EPT_TRIANGLES,
	QuadStrip = EPT_QUAD_STRIP,
	Quads = EPT_QUADS,
	Polygon = EPT_POLYGON,
	PointSprites = EPT_POINT_SPRITES
};

} // end namespace Scene
} // end namespace IrrlichtLime