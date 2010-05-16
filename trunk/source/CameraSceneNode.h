#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

public ref class CameraSceneNode : SceneNode
{
public:

internal:

	CameraSceneNode(scene::ICameraSceneNode* cameraSceneNode);

	scene::ICameraSceneNode* m_CameraSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime