#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

SceneNodeAnimator::SceneNodeAnimator(scene::ISceneNodeAnimator* sceneNodeAnimator)
	: IO::AttributeExchangingObject(sceneNodeAnimator)
{
	LIME_ASSERT(sceneNodeAnimator != nullptr);
	m_SceneNodeAnimator = sceneNodeAnimator;
}

void SceneNodeAnimator::AnimateNode(SceneNode^ node, unsigned int timeMs)
{
	m_SceneNodeAnimator->animateNode(LIME_SAFEREF(node, m_SceneNode), timeMs);
}

bool SceneNodeAnimator::EventReceiverEnabled::get()
{
	return m_SceneNodeAnimator->isEventReceiverEnabled();
}

bool SceneNodeAnimator::Finished::get()
{
	return m_SceneNodeAnimator->hasFinished();
}

SceneNodeAnimatorType SceneNodeAnimator::Type::get()
{
	return (SceneNodeAnimatorType)m_SceneNodeAnimator->getType();
}

String^ SceneNodeAnimator::ToString()
{
	return String::Format("Type={0}", Type);
}

} // end namespace Scene
} // end namespace IrrlichtLime