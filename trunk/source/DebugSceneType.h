#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

[Flags]
public enum class DebugSceneType
{
	Off = EDS_OFF,
	BBox = EDS_BBOX,
	Normals = EDS_NORMALS,
	Skeleton = EDS_SKELETON,
	MeshWireOverlay = EDS_MESH_WIRE_OVERLAY,
	HalfTransparency = EDS_HALF_TRANSPARENCY,
	BBoxBuffers = EDS_BBOX_BUFFERS,
	BBoxAll = EDS_BBOX_ALL,
	Full = EDS_FULL
};

} // end namespace Scene
} // end namespace IrrlichtLime