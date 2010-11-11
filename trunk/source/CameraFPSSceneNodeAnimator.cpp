#include "stdafx.h"
#include "CameraFPSSceneNodeAnimator.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

CameraFPSSceneNodeAnimator^ CameraFPSSceneNodeAnimator::Wrap(scene::ISceneNodeAnimatorCameraFPS* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew CameraFPSSceneNodeAnimator(ref);
}

CameraFPSSceneNodeAnimator::CameraFPSSceneNodeAnimator(scene::ISceneNodeAnimatorCameraFPS* ref)
	: SceneNodeAnimator(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_CameraFPSSceneNodeAnimator = ref;
}

void CameraFPSSceneNodeAnimator::SetInvertMouse(bool invert)
{
	m_CameraFPSSceneNodeAnimator->setInvertMouse(invert);
}

void CameraFPSSceneNodeAnimator::SetKeyMap(KeyMap^ keyMap)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;

	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	m_CameraFPSSceneNodeAnimator->setKeyMap(keyMapArray, keyMapSize);

	if (keyMapArray != 0)
		delete keyMapArray;
}

void CameraFPSSceneNodeAnimator::SetVerticalMovement(bool allow)
{
	m_CameraFPSSceneNodeAnimator->setVerticalMovement(allow);
}

float CameraFPSSceneNodeAnimator::MoveSpeed::get()
{
	return m_CameraFPSSceneNodeAnimator->getMoveSpeed();
}

void CameraFPSSceneNodeAnimator::MoveSpeed::set(float value)
{
	m_CameraFPSSceneNodeAnimator->setMoveSpeed(value);
}

float CameraFPSSceneNodeAnimator::RotateSpeed::get()
{
	return m_CameraFPSSceneNodeAnimator->getRotateSpeed();
}

void CameraFPSSceneNodeAnimator::RotateSpeed::set(float value)
{
	m_CameraFPSSceneNodeAnimator->setRotateSpeed(value);
}

} // end namespace Scene
} // end namespace IrrlichtLime