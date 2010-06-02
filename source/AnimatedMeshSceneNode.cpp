#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"

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

bool AnimatedMeshSceneNode::SetFrameLoop(int begin, int end)
{
	return m_AnimatedMeshSceneNode->setFrameLoop(begin, end);
}

bool AnimatedMeshSceneNode::SetMD2Animation(AnimationTypeMD2 animationType)
{
	return m_AnimatedMeshSceneNode->setMD2Animation((scene::EMD2_ANIMATION_TYPE)animationType);
}

bool AnimatedMeshSceneNode::SetMD2Animation(String^ animationName)
{
	return m_AnimatedMeshSceneNode->setMD2Animation(Lime::StringToStringC(animationName).c_str());
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