#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

SceneNodeAnimator^ SceneNodeAnimator::Wrap(scene::ISceneNodeAnimator* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew SceneNodeAnimator(ref);
}

SceneNodeAnimator::SceneNodeAnimator(scene::ISceneNodeAnimator* ref)
	: IO::AttributeExchangingObject(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SceneNodeAnimator = ref;
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
	return String::Format("SceneNodeAnimator: Type={0}", Type);
}

} // end namespace Scene
} // end namespace IrrlichtLime