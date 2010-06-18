#include "stdafx.h"
#include "VolumeLightSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

VolumeLightSceneNode^ VolumeLightSceneNode::Wrap(scene::IVolumeLightSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew VolumeLightSceneNode(ref);
}

VolumeLightSceneNode::VolumeLightSceneNode(scene::IVolumeLightSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_VolumeLightSceneNode = ref;
}

Video::Coloru^ VolumeLightSceneNode::FootColor::get()
{
	return gcnew Video::Coloru(m_VolumeLightSceneNode->getFootColor());
}

void VolumeLightSceneNode::FootColor::set(Video::Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_VolumeLightSceneNode->setFootColor(*value->m_NativeValue);
}

unsigned int VolumeLightSceneNode::SubDivideU::get()
{
	return m_VolumeLightSceneNode->getSubDivideU();
}

void VolumeLightSceneNode::SubDivideU::set(unsigned int value)
{
	m_VolumeLightSceneNode->setSubDivideU(value);
}

unsigned int VolumeLightSceneNode::SubDivideV::get()
{
	return m_VolumeLightSceneNode->getSubDivideV();
}

void VolumeLightSceneNode::SubDivideV::set(unsigned int value)
{
	m_VolumeLightSceneNode->setSubDivideV(value);
}

Video::Coloru^ VolumeLightSceneNode::TailColor::get()
{
	return gcnew Video::Coloru(m_VolumeLightSceneNode->getTailColor());
}

void VolumeLightSceneNode::TailColor::set(Video::Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_VolumeLightSceneNode->setTailColor(*value->m_NativeValue);
}

} // end namespace Scene
} // end namespace IrrlichtLime