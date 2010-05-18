#pragma once

#include "stdafx.h"
#include "SceneNode.h"
#include "SceneManager.h"
#include "Texture.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

SceneNode::SceneNode(scene::ISceneNode* sceneNode)
{
	LIME_ASSERT(sceneNode != nullptr);
	m_SceneNode = sceneNode;
}

void SceneNode::AddChild(SceneNode^ child)
{
	m_SceneNode->addChild(LIME_SAFEREF(child, m_SceneNode));
}

void SceneNode::Remove()
{
	m_SceneNode->remove();
}

void SceneNode::RemoveAll()
{
	m_SceneNode->removeAll();
}

bool SceneNode::RemoveChild(SceneNode^ child)
{
	return m_SceneNode->removeChild(LIME_SAFEREF(child, m_SceneNode));
}

void SceneNode::Render()
{
	m_SceneNode->render();
}

void SceneNode::SetMaterialFlag(Video::MaterialFlag flag, bool value)
{
	m_SceneNode->setMaterialFlag((video::E_MATERIAL_FLAG)flag, value);
}

void SceneNode::SetMaterialTexture(UInt32 textureLayer, Video::Texture^ texture)
{
	m_SceneNode->setMaterialTexture(textureLayer, LIME_SAFEREF(texture, m_Texture));
}

void SceneNode::UpdateAbsolutePosition()
{
	m_SceneNode->updateAbsolutePosition();
}

Vector3Df^ SceneNode::AbsolutePosition::get()
{
	core::vector3df v = m_SceneNode->getAbsolutePosition();
	return gcnew Vector3Df(v.X, v.Y, v.Z);
}

UInt32 SceneNode::AutomaticCulling::get()
{
	return m_SceneNode->getAutomaticCulling();
}

void SceneNode::AutomaticCulling::set(UInt32 value)
{
	m_SceneNode->setAutomaticCulling(value);
}

bool SceneNode::DebugObject::get()
{
	return m_SceneNode->isDebugObject();
}

void SceneNode::DebugObject::set(bool value)
{
	m_SceneNode->setIsDebugObject(value);
}

Int32 SceneNode::ID::get()
{
	return m_SceneNode->getID();
}

void SceneNode::ID::set(Int32 value)
{
	m_SceneNode->setID(value);
}

String^ SceneNode::Name::get()
{
	return gcnew String(m_SceneNode->getName());
}

void SceneNode::Name::set(String^ value)
{
	m_SceneNode->setName(Lime::StringToStringC(value));
}

SceneNode^ SceneNode::Parent::get()
{
	scene::ISceneNode* n = m_SceneNode->getParent();
	return LIME_SAFEWRAP(SceneNode, n);
}

void SceneNode::Parent::set(SceneNode^ value)
{
	m_SceneNode->setParent(value->m_SceneNode);
}

Vector3Df^ SceneNode::Position::get()
{
	core::vector3df v = m_SceneNode->getPosition();
	return gcnew Vector3Df(v.X, v.Y, v.Z);
}

void SceneNode::Position::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setPosition(*value->m_NativeValue);
}

Vector3Df^ SceneNode::Rotation::get()
{
	core::vector3df v = m_SceneNode->getRotation();
	return gcnew Vector3Df(v.X, v.Y, v.Z);
}

void SceneNode::Rotation::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setRotation(*value->m_NativeValue);
}

Vector3Df^ SceneNode::Scale::get()
{
	core::vector3df v = m_SceneNode->getScale();
	return gcnew Vector3Df(v.X, v.Y, v.Z);
}

void SceneNode::Scale::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setScale(*value->m_NativeValue);
}

Scene::SceneManager^ SceneNode::SceneManager::get()
{
	return LIME_SAFEWRAP(Scene::SceneManager, m_SceneNode->getSceneManager());
}

bool SceneNode::TrulyVisible::get()
{
	return m_SceneNode->isTrulyVisible();
}

SceneNodeType SceneNode::Type::get()
{
	return (SceneNodeType)m_SceneNode->getType();
}

bool SceneNode::Visible::get()
{
	return m_SceneNode->isVisible();
}

void SceneNode::Visible::set(bool value)
{
	m_SceneNode->setVisible(value);
}

String^ SceneNode::ToString()
{
	return String::Format("Name={0}", Name);
}

} // end namespace Scene
} // end namespace IrrlichtLime