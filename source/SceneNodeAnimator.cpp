#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "CameraFPSSceneNodeAnimator.h"
#include "CameraMayaSceneNodeAnimator.h"
#include "CollisionResponseSceneNodeAnimator.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "SceneNodeAnimatorInheritor.h"

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
		try {
			SceneNodeAnimatorInheritor * animator;
			animator = dynamic_cast<SceneNodeAnimatorInheritor*> (ref);
			if (animator != 0)
				return animator->m_userSceneNodeAnimator;
		} catch (...){}
		return gcnew SceneNodeAnimator(ref);
	}
}

SceneNodeAnimator::SceneNodeAnimator(scene::ISceneNodeAnimator* ref)
	: IO::AttributeExchangingObject(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SceneNodeAnimator = ref;
	m_Inherited = false;
}

SceneNodeAnimator::SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart, unsigned __int32 startTime)
	: IO::AttributeExchangingObject(nullptr)
{
	SceneNodeAnimatorInheritor* i = new SceneNodeAnimatorInheritor(
		enabled,
		pauseTimeSum,
		pauseTimeStart,
		startTime);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNodeAnimator = i; 
	m_Inherited = true;
}

SceneNodeAnimator::SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum, unsigned __int32 pauseTimeStart)
	: IO::AttributeExchangingObject(nullptr)
{
	SceneNodeAnimatorInheritor* i = new SceneNodeAnimatorInheritor(
		enabled,
		pauseTimeSum,
		pauseTimeStart);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNodeAnimator = i; 
	m_Inherited = true;
}

SceneNodeAnimator::SceneNodeAnimator(bool enabled, unsigned __int32 pauseTimeSum)
	: IO::AttributeExchangingObject(nullptr)
{
	SceneNodeAnimatorInheritor* i = new SceneNodeAnimatorInheritor(
		enabled,
		pauseTimeSum);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNodeAnimator = i; 
	m_Inherited = true;
}

SceneNodeAnimator::SceneNodeAnimator(bool enabled)
	: IO::AttributeExchangingObject(nullptr)
{
	SceneNodeAnimatorInheritor* i = new SceneNodeAnimatorInheritor(
		enabled);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNodeAnimator = i; 
	m_Inherited = true;
}

SceneNodeAnimator::SceneNodeAnimator()
	: IO::AttributeExchangingObject(nullptr)
{
	SceneNodeAnimatorInheritor* i = new SceneNodeAnimatorInheritor();

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNodeAnimator = i; 
	m_Inherited = true;
}


void SceneNodeAnimator::AnimateNode(SceneNode^ node, unsigned int timeMs)
{
	if (m_Inherited)
	{
		OnAnimateNode(node, timeMs);
		return;
	}
	m_SceneNodeAnimator->animateNode(LIME_SAFEREF(node, m_SceneNode), timeMs);
}

SceneNodeAnimator^ SceneNodeAnimator::CreateClone(SceneNode^ node, SceneManager^ newManager)
{
	scene::ISceneNodeAnimator* a = m_SceneNodeAnimator->createClone(
		LIME_SAFEREF(node, m_SceneNode),
		LIME_SAFEREF(newManager, m_SceneManager));

	return Wrap(a);
}

SceneNodeAnimator^ SceneNodeAnimator::CreateClone(SceneNode^ node)
{
	scene::ISceneNodeAnimator* a = m_SceneNodeAnimator->createClone(
		LIME_SAFEREF(node, m_SceneNode));

	return Wrap(a);
}

void SceneNodeAnimator::SetEnabled(bool enabled, unsigned __int32 timeNow)
{
	m_SceneNodeAnimator->setEnabled(enabled, timeNow);
}

void SceneNodeAnimator::SetStartTime(unsigned __int32 time, bool resetPauseTime)
{
	m_SceneNodeAnimator->setStartTime(time, resetPauseTime);
}

bool SceneNodeAnimator::EventReceiverEnabled::get()
{
	return m_SceneNodeAnimator->isEventReceiverEnabled();
}

bool SceneNodeAnimator::Finished::get()
{
	if (m_Inherited)
	{
		return OnGetFinished();
	}
	return m_SceneNodeAnimator->hasFinished();
}

SceneNodeAnimatorType SceneNodeAnimator::Type::get()
{
	return (SceneNodeAnimatorType)m_SceneNodeAnimator->getType();
}

bool SceneNodeAnimator::Enabled::get()
{
	return m_SceneNodeAnimator->isEnabled();
}

void SceneNodeAnimator::Enabled::set(bool value)
{
	m_SceneNodeAnimator->setEnabled(value);
}

unsigned __int32 SceneNodeAnimator::StartTime::get()
{
	return m_SceneNodeAnimator->getStartTime();
}

void SceneNodeAnimator::StartTime::set(unsigned __int32 value)
{
	m_SceneNodeAnimator->setStartTime(value);
}

String^ SceneNodeAnimator::ToString()
{
	return String::Format("SceneNodeAnimator: Type={0}", Type);
}

void SceneNodeAnimator::initInheritor(SceneNodeAnimatorInheritor* i)
{
	i->m_userSceneNodeAnimator = this;
}

} // end namespace Scene
} // end namespace IrrlichtLime