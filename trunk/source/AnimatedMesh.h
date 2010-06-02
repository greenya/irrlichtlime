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

	Mesh^ GetMesh(int frame, int detailLevel, int startFrameLoop, int endFrameLoop);
	Mesh^ GetMesh(int frame, int detailLevel, int startFrameLoop);
	Mesh^ GetMesh(int frame, int detailLevel);
	Mesh^ GetMesh(int frame);

	property unsigned int FrameCount { unsigned int get(); }
	property AnimatedMeshType MeshType { AnimatedMeshType get(); }

internal:

	static AnimatedMesh^ Wrap(scene::IAnimatedMesh* ref);
	AnimatedMesh(scene::IAnimatedMesh* ref);

	scene::IAnimatedMesh* m_AnimatedMesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime