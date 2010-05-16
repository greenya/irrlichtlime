#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class AnimatedMeshSceneNode : SceneNode
{
public:

	bool SetMD2Animation(AnimationTypeMD2 animationType);
	bool SetMD2Animation(String^ animationName);

internal:

	AnimatedMeshSceneNode(scene::IAnimatedMeshSceneNode* animatedMeshSceneNode);

	scene::IAnimatedMeshSceneNode* m_AnimatedMeshSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime