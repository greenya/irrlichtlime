#include "stdafx.h"
#include "AnimatedMesh.h"
#include "SkinnedMesh.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

SkinnedMesh^ SkinnedMesh::Wrap(scene::ISkinnedMesh* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew SkinnedMesh(ref);
}

SkinnedMesh::SkinnedMesh(scene::ISkinnedMesh* ref)
	: AnimatedMesh(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SkinnedMesh = ref;
}

void SkinnedMesh::AnimateMesh(float frame, float blend)
{
	m_SkinnedMesh->animateMesh(frame, blend);
}

void SkinnedMesh::ConvertMeshToTangents()
{
	m_SkinnedMesh->convertMeshToTangents();
}

void SkinnedMesh::FinalizeMeshPopulation()
{
	m_SkinnedMesh->finalize();
}

String^ SkinnedMesh::GetJointName(int index)
{
	LIME_ASSERT(index >= 0 && index < JointCount);
	return gcnew String(m_SkinnedMesh->getJointName(index));
}

int SkinnedMesh::GetJointIndex(String^ name)
{
	LIME_ASSERT(name != nullptr);
	return m_SkinnedMesh->getJointNumber(LIME_SAFESTRINGTOSTRINGC_C_STR(name));
}

bool SkinnedMesh::SetHardwareSkinning(bool turnOn)
{
	return m_SkinnedMesh->setHardwareSkinning(turnOn);
}

void SkinnedMesh::SetInterpolationMode(InterpolationMode mode)
{
	m_SkinnedMesh->setInterpolationMode((scene::E_INTERPOLATION_MODE)mode);
}

void SkinnedMesh::SkinMesh()
{
	m_SkinnedMesh->skinMesh();
}

void SkinnedMesh::UpdateNormalsWhenAnimating(bool turnOn)
{
	m_SkinnedMesh->updateNormalsWhenAnimating(turnOn);
}

bool SkinnedMesh::UseAnimationFrom(SkinnedMesh^ mesh)
{
	LIME_ASSERT(mesh != nullptr);
	return m_SkinnedMesh->useAnimationFrom(LIME_SAFEREF(mesh, m_SkinnedMesh));
}

int SkinnedMesh::JointCount::get()
{
	return m_SkinnedMesh->getJointCount();
}

bool SkinnedMesh::Static::get()
{
	return m_SkinnedMesh->isStatic();
}

} // end namespace Scene
} // end namespace IrrlichtLime