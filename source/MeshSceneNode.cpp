#include "stdafx.h"
#include "Mesh.h"
#include "MeshSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshSceneNode^ MeshSceneNode::Wrap(scene::IMeshSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew MeshSceneNode(ref);
}

MeshSceneNode::MeshSceneNode(scene::IMeshSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_MeshSceneNode = ref;
}

Scene::Mesh^ MeshSceneNode::Mesh::get()
{
	return Scene::Mesh::Wrap(m_MeshSceneNode->getMesh());
}

void MeshSceneNode::Mesh::set(Scene::Mesh^ value)
{
	m_MeshSceneNode->setMesh(LIME_SAFEREF(value, m_Mesh));
}

bool MeshSceneNode::ReadOnlyMeterials::get()
{
	return m_MeshSceneNode->isReadOnlyMaterials();
}

void MeshSceneNode::ReadOnlyMeterials::set(bool value)
{
	m_MeshSceneNode->setReadOnlyMaterials(value);
}

} // end namespace Scene
} // end namespace IrrlichtLime