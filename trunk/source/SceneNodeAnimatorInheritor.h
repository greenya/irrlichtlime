#pragma once

#include <vcclr.h> // for gcroot
#include "stdafx.h"
#include "Material.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"

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
		//Not implemented
		return 0;
	}

	//Not implemented yet
	/*virtual bool isEventReceiverEnabled() const
	{
		return false;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		return false;
	}*/

	virtual bool hasFinished(void) const
	{
		return m_userSceneNodeAnimator->Finished;
	}
};

} // end namespace Scene
} // end namespace IrrlichtLime