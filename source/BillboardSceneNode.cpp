#include "stdafx.h"
#include "BillboardSceneNode.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

BillboardSceneNode^ BillboardSceneNode::Wrap(scene::IBillboardSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew BillboardSceneNode(ref);
}

BillboardSceneNode::BillboardSceneNode(scene::IBillboardSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_BillboardSceneNode = ref;
}

void BillboardSceneNode::SetShape(float bottomWidth, float topWidth, float height)
{
	LIME_ASSERT(bottomWidth > 0.0f);
	LIME_ASSERT(topWidth > 0.0f);
	LIME_ASSERT(height > 0.0f);

	m_BillboardSceneNode->setSize(core::dimension2d<f32>(111, height)); // "111" can be anyhting else
	m_BillboardSceneNode->setWidths(bottomWidth, topWidth);
}

Video::Color^ BillboardSceneNode::BottomColor::get()
{
	video::SColor t, b;
	m_BillboardSceneNode->getColor(t, b);
	return gcnew Video::Color(b);
}

void BillboardSceneNode::BottomColor::set(Video::Color^ value)
{
	LIME_ASSERT(value != nullptr);

	video::SColor t, b;
	m_BillboardSceneNode->getColor(t, b);
	m_BillboardSceneNode->setColor(t, *value->m_NativeValue);
}

float BillboardSceneNode::BottomWidth::get()
{
	float s, e;
	m_BillboardSceneNode->getWidths(s, e);
	return s;
}

void BillboardSceneNode::BottomWidth::set(float value)
{
	LIME_ASSERT(value > 0.0f);

	float s, e;
	m_BillboardSceneNode->getWidths(s, e);
	m_BillboardSceneNode->setWidths(value, e);
}

float BillboardSceneNode::Height::get()
{
	return m_BillboardSceneNode->getSize().Height;
}

void BillboardSceneNode::Height::set(float value)
{
	LIME_ASSERT(value > 0.0f);

	float s, e;
	m_BillboardSceneNode->getWidths(s, e); // save widths
	m_BillboardSceneNode->setSize(core::dimension2d<f32>(111, value)); // "111" can be anyhting else
	m_BillboardSceneNode->setWidths(s, e); // restore widths
}

Video::Color^ BillboardSceneNode::TopColor::get()
{
	video::SColor t, b;
	m_BillboardSceneNode->getColor(t, b);
	return gcnew Video::Color(t);
}

void BillboardSceneNode::TopColor::set(Video::Color^ value)
{
	LIME_ASSERT(value != nullptr);

	video::SColor t, b;
	m_BillboardSceneNode->getColor(t, b);
	m_BillboardSceneNode->setColor(*value->m_NativeValue, b);
}

float BillboardSceneNode::TopWidth::get()
{
	float s, e;
	m_BillboardSceneNode->getWidths(s, e);
	return e;
}

void BillboardSceneNode::TopWidth::set(float value)
{
	LIME_ASSERT(value > 0.0f);

	float s, e;
	m_BillboardSceneNode->getWidths(s, e);
	m_BillboardSceneNode->setWidths(s, value);
}

} // end namespace Scene
} // end namespace IrrlichtLime