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

Mesh^ AnimatedMesh::GetMesh(int frame, int detailLevel, int startFrameLoop, int endFrameLoop)
{
	return LIME_SAFEWRAP(Mesh, m_AnimatedMesh->getMesh(frame, detailLevel, startFrameLoop, endFrameLoop));
}

Mesh^ AnimatedMesh::GetMesh(int frame, int detailLevel, int startFrameLoop)
{
	return LIME_SAFEWRAP(Mesh, m_AnimatedMesh->getMesh(frame, detailLevel, startFrameLoop));
}

Mesh^ AnimatedMesh::GetMesh(int frame, int detailLevel)
{
	return LIME_SAFEWRAP(Mesh, m_AnimatedMesh->getMesh(frame, detailLevel));
}

Mesh^ AnimatedMesh::GetMesh(int frame)
{
	return LIME_SAFEWRAP(Mesh, m_AnimatedMesh->getMesh(frame));
}

unsigned int AnimatedMesh::FrameCount::get()
{
	return m_AnimatedMesh->getFrameCount();
}

AnimatedMeshType AnimatedMesh::MeshType::get()
{
	return (AnimatedMeshType)m_AnimatedMesh->getMeshType();
}

} // end namespace Scene
} // end namespace IrrlichtLime