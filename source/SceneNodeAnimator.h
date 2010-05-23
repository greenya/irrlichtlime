#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class SceneNode;

public ref class SceneNodeAnimator
{
public:

	void AnimateNode(SceneNode^ node, unsigned int timeMs);

	void Drop();

	property bool EventReceiverEnabled { bool get(); }
	property bool Finished { bool get(); }
	property SceneNodeAnimatorType Type { SceneNodeAnimatorType get(); }

	virtual String^ ToString() override;

internal:

	SceneNodeAnimator(scene::ISceneNodeAnimator* sceneNodeAnimator);

	scene::ISceneNodeAnimator* m_SceneNodeAnimator;
};

} // end namespace Scene
} // end namespace IrrlichtLime