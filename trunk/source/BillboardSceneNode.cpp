#include "stdafx.h"
#include "BillboardSceneNode.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

BillboardSceneNode^ BillboardSceneNode::Wrap(scene::IBillboardSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew BillboardSceneNode(ref);
}

BillboardSceneNode::BillboardSceneNode(scene::IBillboardSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_BillboardSceneNode = ref;
}

Dimension2Df^ BillboardSceneNode::Size::get()
{
	return gcnew Dimension2Df(m_BillboardSceneNode->getSize());
}

void BillboardSceneNode::Size::set(Dimension2Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_BillboardSceneNode->setSize(*value->m_NativeValue);
}

} // end namespace Scene
} // end namespace IrrlichtLime