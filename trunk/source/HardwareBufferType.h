#pragma once

#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class HardwareBufferType
{
	None = EBT_NONE,
	Vertex = EBT_VERTEX,
	Index = EBT_INDEX,
	VertexAndIndex = EBT_VERTEX_AND_INDEX
};

} // end namespace Scene
} // end namespace IrrlichtLime