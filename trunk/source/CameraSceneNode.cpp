#include "stdafx.h"
#include "CameraSceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

CameraSceneNode::CameraSceneNode(scene::ICameraSceneNode* cameraSceneNode)
	: SceneNode(cameraSceneNode)
{
	LIME_ASSERT(cameraSceneNode != nullptr);
	m_CameraSceneNode = cameraSceneNode;
}

} // end namespace Scene
} // end namespace IrrlichtLime