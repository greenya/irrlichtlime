#pragma once

#include "stdafx.h"
#include "Mesh.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class AnimatedMesh : Mesh
{
public:

	Mesh^ GetMesh(Int32 frame, Int32 detailLevel, Int32 startFrameLoop, Int32 endFrameLoop);
	Mesh^ GetMesh(Int32 frame, Int32 detailLevel, Int32 startFrameLoop);
	Mesh^ GetMesh(Int32 frame, Int32 detailLevel);
	Mesh^ GetMesh(Int32 frame);

	property UInt32 FrameCount { UInt32 get(); }
	property AnimatedMeshType MeshType { AnimatedMeshType get(); }

internal:

	AnimatedMesh(scene::IAnimatedMesh* animatedMesh);

	scene::IAnimatedMesh* m_AnimatedMesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime