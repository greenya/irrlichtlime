#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"
#include "BoneSceneNode.h"
#include "Mesh.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "ShadowVolumeSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

AnimatedMeshSceneNode^ AnimatedMeshSceneNode::Wrap(scene::IAnimatedMeshSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew AnimatedMeshSceneNode(ref);
}

AnimatedMeshSceneNode::AnimatedMeshSceneNode(scene::IAnimatedMeshSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_AnimatedMeshSceneNode = ref;
}

ShadowVolumeSceneNode^ AnimatedMeshSceneNode::AddShadowVolumeSceneNode(Scene::Mesh^ shadowMesh, int id, bool zfailmethod, float infinity)
{
	scene::IShadowVolumeSceneNode* n = m_AnimatedMeshSceneNode->addShadowVolumeSceneNode(
		LIME_SAFEREF(shadowMesh, m_Mesh),
		id,
		zfailmethod,
		infinity);

	return ShadowVolumeSceneNode::Wrap(n);
}

ShadowVolumeSceneNode^ AnimatedMeshSceneNode::AddShadowVolumeSceneNode(Scene::Mesh^ shadowMesh, int id, bool zfailmethod)
{
	scene::IShadowVolumeSceneNode* n = m_AnimatedMeshSceneNode->addShadowVolumeSceneNode(
		LIME_SAFEREF(shadowMesh, m_Mesh),
		id,
		zfailmethod);

	return ShadowVolumeSceneNode::Wrap(n);
}

ShadowVolumeSceneNode^ AnimatedMeshSceneNode::AddShadowVolumeSceneNode(Scene::Mesh^ shadowMesh, int id)
{
	scene::IShadowVolumeSceneNode* n = m_AnimatedMeshSceneNode->addShadowVolumeSceneNode(
		LIME_SAFEREF(shadowMesh, m_Mesh),
		id);

	return ShadowVolumeSceneNode::Wrap(n);
}

ShadowVolumeSceneNode^ AnimatedMeshSceneNode::AddShadowVolumeSceneNode(Scene::Mesh^ shadowMesh)
{
	scene::IShadowVolumeSceneNode* n = m_AnimatedMeshSceneNode->addShadowVolumeSceneNode(
		LIME_SAFEREF(shadowMesh, m_Mesh));

	return ShadowVolumeSceneNode::Wrap(n);
}

ShadowVolumeSceneNode^ AnimatedMeshSceneNode::AddShadowVolumeSceneNode()
{
	scene::IShadowVolumeSceneNode* n = m_AnimatedMeshSceneNode->addShadowVolumeSceneNode();
	return ShadowVolumeSceneNode::Wrap(n);
}

void AnimatedMeshSceneNode::AnimateJoints(bool calculateAbsolutePositions)
{
	m_AnimatedMeshSceneNode->animateJoints(calculateAbsolutePositions);
}

void AnimatedMeshSceneNode::AnimateJoints()
{
	m_AnimatedMeshSceneNode->animateJoints();
}

SceneNode^ AnimatedMeshSceneNode::Clone(SceneNode^ newParent, Scene::SceneManager^ newManager)
{
	scene::ISceneNode* n = m_AnimatedMeshSceneNode->clone(
		LIME_SAFEREF(newParent, m_SceneNode),
		LIME_SAFEREF(newManager, m_SceneManager));

	return SceneNode::Wrap(n);
}

SceneNode^ AnimatedMeshSceneNode::Clone(SceneNode^ newParent)
{
	scene::ISceneNode* n = m_AnimatedMeshSceneNode->clone(
		LIME_SAFEREF(newParent, m_SceneNode));

	return SceneNode::Wrap(n);
}

SceneNode^ AnimatedMeshSceneNode::Clone()
{
	scene::ISceneNode* n = m_AnimatedMeshSceneNode->clone();
	return SceneNode::Wrap(n);
}

BoneSceneNode^ AnimatedMeshSceneNode::GetJointNode(unsigned int jointIndex)
{
	LIME_ASSERT(jointIndex < JointCount);

	scene::IBoneSceneNode* n = m_AnimatedMeshSceneNode->getJointNode(jointIndex);
	return BoneSceneNode::Wrap(n);
}

BoneSceneNode^ AnimatedMeshSceneNode::GetJointNode(String^ jointName)
{
	scene::IBoneSceneNode* n = m_AnimatedMeshSceneNode->getJointNode(Lime::StringToStringC(jointName).c_str());
	return BoneSceneNode::Wrap(n);
}

bool AnimatedMeshSceneNode::SetFrameLoop(int begin, int end)
{
	return m_AnimatedMeshSceneNode->setFrameLoop(begin, end);
}

void AnimatedMeshSceneNode::SetJointMode(JointUpdateOnRender mode)
{
	m_AnimatedMeshSceneNode->setJointMode((scene::E_JOINT_UPDATE_ON_RENDER)mode);
}

void AnimatedMeshSceneNode::SetLoopMode(bool playAnimationLooped)
{
	m_AnimatedMeshSceneNode->setLoopMode(playAnimationLooped);
}

bool AnimatedMeshSceneNode::SetMD2Animation(AnimationTypeMD2 animationType)
{
	return m_AnimatedMeshSceneNode->setMD2Animation((scene::EMD2_ANIMATION_TYPE)animationType);
}

bool AnimatedMeshSceneNode::SetMD2Animation(String^ animationName)
{
	return m_AnimatedMeshSceneNode->setMD2Animation(Lime::StringToStringC(animationName).c_str());
}

void AnimatedMeshSceneNode::SetRenderFromIdentity(bool on)
{
	m_AnimatedMeshSceneNode->setRenderFromIdentity(on);
}

void AnimatedMeshSceneNode::SetTransitionTime(float timeInSeconds)
{
	m_AnimatedMeshSceneNode->setTransitionTime(timeInSeconds);
}

float AnimatedMeshSceneNode::AnimationSpeed::get()
{
	return m_AnimatedMeshSceneNode->getAnimationSpeed();
}

void AnimatedMeshSceneNode::AnimationSpeed::set(float value)
{
	m_AnimatedMeshSceneNode->setAnimationSpeed(value);
}

float AnimatedMeshSceneNode::CurrentFrame::get()
{
	return m_AnimatedMeshSceneNode->getFrameNr();
}

void AnimatedMeshSceneNode::CurrentFrame::set(float value)
{
	m_AnimatedMeshSceneNode->setCurrentFrame(value);
}

int AnimatedMeshSceneNode::EndFrame::get()
{
	return m_AnimatedMeshSceneNode->getEndFrame();
}

unsigned int AnimatedMeshSceneNode::JointCount::get()
{
	return m_AnimatedMeshSceneNode->getJointCount();
}

AnimatedMesh^ AnimatedMeshSceneNode::Mesh::get()
{
	scene::IAnimatedMesh* m = m_AnimatedMeshSceneNode->getMesh();
	return AnimatedMesh::Wrap(m);
}

void AnimatedMeshSceneNode::Mesh::set(AnimatedMesh^ value)
{
	m_AnimatedMeshSceneNode->setMesh(LIME_SAFEREF(value, m_AnimatedMesh));
}

int AnimatedMeshSceneNode::StartFrame::get()
{
	return m_AnimatedMeshSceneNode->getStartFrame();
}

bool AnimatedMeshSceneNode::ReadOnlyMaterials::get()
{
	return m_AnimatedMeshSceneNode->isReadOnlyMaterials();
}

void AnimatedMeshSceneNode::ReadOnlyMaterials::set(bool value)
{
	m_AnimatedMeshSceneNode->setReadOnlyMaterials(value);
}

} // end namespace Scene
} // end namespace IrrlichtLime