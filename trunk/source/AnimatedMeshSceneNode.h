#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Scene
{
	public ref class AnimatedMeshSceneNode : SceneNode
	{
	public:

	internal:

		scene::IAnimatedMeshSceneNode* m_AnimatedMeshSceneNode;

		AnimatedMeshSceneNode(scene::IAnimatedMeshSceneNode* animatedMeshSceneNode)
			: SceneNode(animatedMeshSceneNode)
		{
			m_AnimatedMeshSceneNode = animatedMeshSceneNode;
		}
	};
}
}