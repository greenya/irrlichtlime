#pragma once

#include "stdafx.h"
#include "AnimatedMeshSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

bool AnimatedMeshSceneNode::SetMD2Animation(AnimationTypeMD2 animationType)
{
	return m_AnimatedMeshSceneNode->setMD2Animation((scene::EMD2_ANIMATION_TYPE)animationType);
}

bool AnimatedMeshSceneNode::SetMD2Animation(String^ animationName)
{
	return m_AnimatedMeshSceneNode->setMD2Animation(Lime::StringToStringC(animationName).c_str());
}

AnimatedMeshSceneNode::AnimatedMeshSceneNode(scene::IAnimatedMeshSceneNode* animatedMeshSceneNode)
	: SceneNode(animatedMeshSceneNode)
{
	LIME_ASSERT(animatedMeshSceneNode != nullptr);
	m_AnimatedMeshSceneNode = animatedMeshSceneNode;
}

} // end namespace Scene
} // end namespace IrrlichtLime