#include "stdafx.h"
#include "CameraSceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

CameraSceneNode^ CameraSceneNode::Wrap(scene::ICameraSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew CameraSceneNode(ref);
}

CameraSceneNode::CameraSceneNode(scene::ICameraSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_CameraSceneNode = ref;
}

} // end namespace Scene
} // end namespace IrrlichtLime