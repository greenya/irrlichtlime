#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class AnimatedMesh;

public ref class AnimatedMeshSceneNode : SceneNode
{
public:

	bool SetFrameLoop(int begin, int end);

	bool SetMD2Animation(AnimationTypeMD2 animationType);
	bool SetMD2Animation(String^ animationName);

	property float AnimationSpeed { float get(); void set(float value); }
	property float CurrentFrame { float get(); void set(float value); }
	property int EndFrame { int get(); }
	property AnimatedMesh^ Mesh { AnimatedMesh^ get(); void set(AnimatedMesh^ value); }
	property int StartFrame { int get(); }
	property bool ReadOnlyMaterials { bool get(); void set(bool value); }

internal:

	AnimatedMeshSceneNode(scene::IAnimatedMeshSceneNode* animatedMeshSceneNode);

	scene::IAnimatedMeshSceneNode* m_AnimatedMeshSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime