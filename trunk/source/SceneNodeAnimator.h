#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ref class SceneManager;
ref class SceneNode;
class SceneNodeAnimatorInheritor;

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

	delegate void AnimateNodeEventHandler(SceneNode^ node, unsigned __int32 time);
	delegate bool GetFinishedEventHandler();

protected:

	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart, unsigned __int32 startTime);
	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart);
	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum);
	SceneNodeAnimator(bool enabled);
	SceneNodeAnimator();

	event AnimateNodeEventHandler^ OnAnimateNode;	 
	event GetFinishedEventHandler^ OnGetFinished;

internal:

	static SceneNodeAnimator^ Wrap(scene::ISceneNodeAnimator* ref);
	SceneNodeAnimator(scene::ISceneNodeAnimator* ref);

	scene::ISceneNodeAnimator* m_SceneNodeAnimator;
	bool m_Inherited;

private:

	void initInheritor(SceneNodeAnimatorInheritor* i);
};

} // end namespace Scene
} // end namespace IrrlichtLime