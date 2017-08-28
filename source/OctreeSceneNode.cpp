#include "stdafx.h"
#include "OctreeSceneNode.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

OctreeSceneNode^ OctreeSceneNode::Wrap(scene::IOctreeSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew OctreeSceneNode(ref);
}

OctreeSceneNode::OctreeSceneNode(scene::IOctreeSceneNode* ref)
	: MeshSceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_OctreeSceneNode = ref;
}

OctreePolygonChecks OctreeSceneNode::PolygonChecks::get()
{
	return (OctreePolygonChecks)m_OctreeSceneNode->getPolygonChecks();
}

void OctreeSceneNode::PolygonChecks::set(OctreePolygonChecks value)
{
	m_OctreeSceneNode->setPolygonChecks((EOCTREE_POLYGON_CHECKS)value);
}

OctreeVBO OctreeSceneNode::UseVBO::get()
{
	return (OctreeVBO)m_OctreeSceneNode->getUseVBO();
}

void OctreeSceneNode::UseVBO::set(OctreeVBO value)
{
	m_OctreeSceneNode->setUseVBO((EOCTREENODE_VBO)value);
}

} // end namespace Scene
} // end namespace IrrlichtLime