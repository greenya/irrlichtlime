#include "stdafx.h"
#include "Mesh.h"
#include "MeshSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshSceneNode::MeshSceneNode(scene::IMeshSceneNode* meshSceneNode)
	: SceneNode(meshSceneNode)
{
	LIME_ASSERT(meshSceneNode != nullptr);
	m_MeshSceneNode = meshSceneNode;
}

Scene::Mesh^ MeshSceneNode::Mesh::get()
{
	return LIME_SAFEWRAP(Scene::Mesh, m_MeshSceneNode->getMesh());
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