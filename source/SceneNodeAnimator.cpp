#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "CameraFPSSceneNodeAnimator.h"
#include "CameraMayaSceneNodeAnimator.h"
#include "CollisionResponseSceneNodeAnimator.h"
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

	switch (ref->getType())
	{
	case scene::ESNAT_COLLISION_RESPONSE:
		return gcnew CollisionResponseSceneNodeAnimator((scene::ISceneNodeAnimatorCollisionResponse*)ref);

	case scene::ESNAT_CAMERA_FPS:
		return gcnew CameraFPSSceneNodeAnimator((scene::ISceneNodeAnimatorCameraFPS*)ref);

	case scene::ESNAT_CAMERA_MAYA:
		return gcnew CameraMayaSceneNodeAnimator((scene::ISceneNodeAnimatorCameraMaya*)ref);

	case scene::ESNAT_FLY_CIRCLE:
	case scene::ESNAT_FLY_STRAIGHT:
	case scene::ESNAT_FOLLOW_SPLINE:
	case scene::ESNAT_ROTATION:
	case scene::ESNAT_TEXTURE:
	case scene::ESNAT_DELETION:
	default:
		return gcnew SceneNodeAnimator(ref);
	}
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