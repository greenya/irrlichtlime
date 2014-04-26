#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

ref class Event;

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

	bool PostEvent(Event^ e);

	void SetEnabled(bool enabled, unsigned __int32 timeNow);
	void SetStartTime(unsigned __int32 time, bool resetPauseTime);

	property bool Enabled{ bool get(); void set(bool value); }
	property bool EventReceiverEnabled { bool get(); }
	property bool Finished { bool get(); }
	property SceneNodeAnimatorType Type { SceneNodeAnimatorType get(); }
	property unsigned __int32 StartTime { unsigned __int32 get(); void set(unsigned __int32); }

	virtual String^ ToString() override;

	delegate void AnimateNodeEventHandler(SceneNode^ node, unsigned __int32 time);
	delegate SceneNodeAnimator^ CreateCloneEventHandler(SceneNode^ node, SceneManager^ newManager);
	delegate bool EventHandler(IrrlichtLime::Event^ e);
	delegate bool GetFinishedEventHandler();
	delegate bool IsEventReceiverEnabledEventHandler();

protected:

	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart, unsigned __int32 startTime);
	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart);
	SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum);
	SceneNodeAnimator(bool enabled);
	SceneNodeAnimator();

	property unsigned __int32 PauseTimeSum { unsigned __int32 get(); void set(unsigned __int32 value); }
	property unsigned __int32 PauseTimeStart { unsigned __int32 get(); void set(unsigned __int32 value); }

	event AnimateNodeEventHandler^ OnAnimateNode;
	event CreateCloneEventHandler^ OnCreateClone;
	event EventHandler^ OnEvent;
	event GetFinishedEventHandler^ OnGetFinished;
	event IsEventReceiverEnabledEventHandler^ OnIsEventReceiverEnabled;

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