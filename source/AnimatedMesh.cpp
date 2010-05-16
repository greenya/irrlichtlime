#pragma once

#include "stdafx.h"
#include "AnimatedMesh.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

AnimatedMesh::AnimatedMesh(scene::IAnimatedMesh* animatedMesh)
	: Mesh(animatedMesh)
{
	LIME_ASSERT(animatedMesh != nullptr);
	m_AnimatedMesh = animatedMesh;
}

} // end namespace Scene
} // end namespace IrrlichtLime