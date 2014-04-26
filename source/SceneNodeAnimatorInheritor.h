#pragma once

#include "Event.h"
#include <vcclr.h> // for gcroot
#include "stdafx.h"
#include "Material.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"
#include "SceneManager.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

class SceneNodeAnimatorInheritor : public scene::ISceneNodeAnimator
{
public:

	SceneNodeAnimatorInheritor(bool isEnabled = true,
		u32 pauseTimeSum = 0,
		u32 pauseTimeStart = 0, 
		u32 startTime = 0)
		: ISceneNodeAnimator()
	{
		IsEnabled = isEnabled;
		PauseTimeSum = pauseTimeSum;
		PauseTimeStart = pauseTimeStart;
		StartTime = startTime;
	}

	gcroot<SceneNodeAnimator^> m_userSceneNodeAnimator;
	virtual void animateNode(ISceneNode* node, u32 timeMs)
	{
		//ISceneNodeAnimator::animateNode(node, timeMs);
		m_userSceneNodeAnimator->AnimateNode(SceneNode::Wrap(node), timeMs);
	}

	virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0)
	{
		SceneNodeAnimator^ clone = m_userSceneNodeAnimator->CreateClone(SceneNode::Wrap(node), SceneManager::Wrap(newManager));
		SceneNodeAnimatorInheritor* nativeClone = static_cast<SceneNodeAnimatorInheritor*>(clone->m_SceneNodeAnimator);
		nativeClone->cloneMembers(this);
		return nativeClone;
	}

	virtual bool isEventReceiverEnabled() const
	{
		return m_userSceneNodeAnimator->EventReceiverEnabled;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		return m_userSceneNodeAnimator->PostEvent(gcnew Event(event));
	}

	virtual bool hasFinished(void) const
	{
		return m_userSceneNodeAnimator->Finished;
	}

	unsigned __int32 getPauseTimeSum()
	{
		return PauseTimeSum;
	}

	void setPauseTimeSum(unsigned __int32 value)
	{
		PauseTimeSum = value;
	}

	unsigned __int32 getPauseTimeStart()
	{
		return PauseTimeStart;
	}

	void setPauseTimeStart(unsigned __int32 value)
	{
		PauseTimeStart = value;
	}
};

} // end namespace Scene
} // end namespace IrrlichtLime