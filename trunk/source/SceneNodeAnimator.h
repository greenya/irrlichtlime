#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class SceneNode;

public ref class SceneNodeAnimator : IO::AttributeExchangingObject
{
public:

	void AnimateNode(SceneNode^ node, unsigned int timeMs);

	property bool EventReceiverEnabled { bool get(); }
	property bool Finished { bool get(); }
	property SceneNodeAnimatorType Type { SceneNodeAnimatorType get(); }

	virtual String^ ToString() override;

internal:

	static SceneNodeAnimator^ Wrap(scene::ISceneNodeAnimator* ref);
	SceneNodeAnimator(scene::ISceneNodeAnimator* ref);

	scene::ISceneNodeAnimator* m_SceneNodeAnimator;
};

} // end namespace Scene
} // end namespace IrrlichtLime