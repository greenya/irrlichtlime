#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class SceneManager;
ref class SceneNode;

public ref class SceneNodeAnimator : IO::AttributeExchangingObject
{
public:

	void AnimateNode(SceneNode^ node, unsigned int timeMs);

	SceneNodeAnimator^ CreateClone(SceneNode^ node, SceneManager^ newManager);
	SceneNodeAnimator^ CreateClone(SceneNode^ node);

	void SetEnabled(bool enabled, unsigned __int32 timeNow);
	void SetStartTime(unsigned __int32 time, bool resetPauseTime);

	property bool Enabled{ bool get(); void set(bool value); }
	property bool EventReceiverEnabled { bool get(); }
	property bool Finished { bool get(); }
	property SceneNodeAnimatorType Type { SceneNodeAnimatorType get(); }
	property unsigned __int32 StartTime { unsigned __int32 get(); void set(unsigned __int32); }

	virtual String^ ToString() override;

internal:

	static SceneNodeAnimator^ Wrap(scene::ISceneNodeAnimator* ref);
	SceneNodeAnimator(scene::ISceneNodeAnimator* ref);

	scene::ISceneNodeAnimator* m_SceneNodeAnimator;
};

} // end namespace Scene
} // end namespace IrrlichtLime