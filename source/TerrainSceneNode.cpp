#include "stdafx.h"
#include "DynamicMeshBuffer.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "SceneNode.h"
#include "TerrainSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

TerrainSceneNode^ TerrainSceneNode::Wrap(scene::ITerrainSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew TerrainSceneNode(ref);
}

TerrainSceneNode::TerrainSceneNode(scene::ITerrainSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_TerrainSceneNode = ref;
}

AABBox3Df^ TerrainSceneNode::GetPatchBoundingBox(int patchX, int patchZ)
{
	LIME_ASSERT(patchX >= 0);
	LIME_ASSERT(patchZ >= 0);

	return gcnew AABBox3Df(m_TerrainSceneNode->getBoundingBox(patchX, patchZ));
}

List<int>^ TerrainSceneNode::GetCurrentLODOfPatches()
{
	List<int>^ l = gcnew List<int>();

	core::array<s32> a;
	int t = m_TerrainSceneNode->getCurrentLODOfPatches(a);
	LIME_ASSERT(t == a.size());

	for (int i = 0; i < t; i++)
		l->Add(a[i]);

	return l;
}

float TerrainSceneNode::GetHeight(float x, float z)
{
	return m_TerrainSceneNode->getHeight(x, z);
}

List<int>^ TerrainSceneNode::GetIndicesForPatch(int patchX, int patchZ, int lodLevel)
{
	LIME_ASSERT(patchX >= 0);
	LIME_ASSERT(patchZ >= 0);
	LIME_ASSERT(lodLevel >= -1);

	List<int>^ l = gcnew List<int>();

	core::array<u32> a;
	int t = m_TerrainSceneNode->getIndicesForPatch(a, patchX, patchZ, lodLevel);
	LIME_ASSERT(t == a.size());

	for (int i = 0; i < t; i++)
		l->Add(a[i]);

	return l;
}

List<int>^ TerrainSceneNode::GetIndicesForPatch(int patchX, int patchZ)
{
	LIME_ASSERT(patchX >= 0);
	LIME_ASSERT(patchZ >= 0);

	List<int>^ l = gcnew List<int>();

	core::array<u32> a;
	int t = m_TerrainSceneNode->getIndicesForPatch(a, patchX, patchZ);
	LIME_ASSERT(t == a.size());

	for (int i = 0; i < t; i++)
		l->Add(a[i]);

	return l;
}

DynamicMeshBuffer^ TerrainSceneNode::GetMeshBufferForLOD(int lodLevel)
{
	LIME_ASSERT(lodLevel >= 0);

	// !!! check for leak! (got from 12.TerrainRendering example)
	scene::CDynamicMeshBuffer* b = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
	m_TerrainSceneNode->getMeshBufferForLOD(*b, lodLevel);
	return DynamicMeshBuffer::Wrap(b);
}

DynamicMeshBuffer^ TerrainSceneNode::GetMeshBufferForLOD()
{
	scene::CDynamicMeshBuffer* b = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
	m_TerrainSceneNode->getMeshBufferForLOD(*b);
	return DynamicMeshBuffer::Wrap(b);
}

bool TerrainSceneNode::OverrideLODDistance(int lodLevel, double newDistance)
{
	LIME_ASSERT(lodLevel >= 0);
	return m_TerrainSceneNode->overrideLODDistance(lodLevel, newDistance);
}

void TerrainSceneNode::ScaleTexture(float scale, float scale2)
{
	m_TerrainSceneNode->scaleTexture(scale, scale2);
}

void TerrainSceneNode::ScaleTexture(float scale)
{
	m_TerrainSceneNode->scaleTexture(scale);
}

void TerrainSceneNode::SetCameraMovementDelta(float delta)
{
	m_TerrainSceneNode->setCameraMovementDelta(delta);
}

void TerrainSceneNode::SetCameraRotationDelta(float delta)
{
	m_TerrainSceneNode->setCameraRotationDelta(delta);
}

void TerrainSceneNode::SetDynamicSelectorUpdate(bool flag)
{
	m_TerrainSceneNode->setDynamicSelectorUpdate(flag);
}

void TerrainSceneNode::SetLODOfPatch(int patchX, int patchZ, int lodLevel)
{
	LIME_ASSERT(patchX >= 0);
	LIME_ASSERT(patchZ >= 0);
	LIME_ASSERT(lodLevel >= 0);

	m_TerrainSceneNode->setLODOfPatch(patchX, patchZ, lodLevel);
}

int TerrainSceneNode::IndexCount::get()
{
	return m_TerrainSceneNode->getIndexCount();
}

Scene::Mesh^ TerrainSceneNode::Mesh::get()
{
	scene::IMesh* m = m_TerrainSceneNode->getMesh();
	return Scene::Mesh::Wrap(m);
}

MeshBuffer^ TerrainSceneNode::RenderBuffer::get()
{
	scene::IMeshBuffer* m = m_TerrainSceneNode->getRenderBuffer();
	return MeshBuffer::Wrap(m);
}

Vector3Df^ TerrainSceneNode::TerrainCenter::get()
{
	return gcnew Vector3Df(m_TerrainSceneNode->getTerrainCenter());
}

} // end namespace Scene
} // end namespace IrrlichtLime