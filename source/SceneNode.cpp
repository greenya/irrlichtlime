#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "Material.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TriangleSelector.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

SceneNode^ SceneNode::Wrap(scene::ISceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew SceneNode(ref);
}

SceneNode::SceneNode(scene::ISceneNode* ref)
	: IO::AttributeExchangingObject(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SceneNode = ref;
	m_Inherited = false;
}

SceneNode::SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
	: IO::AttributeExchangingObject(0)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);
	LIME_ASSERT(scale != nullptr);

	SceneNodeInheritor* i = new SceneNodeInheritor(
		LIME_SAFEREF(parent, m_SceneNode),
		LIME_SAFEREF(manager, m_SceneManager),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNode = i;
	m_Inherited = true;
}

SceneNode::SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position, Vector3Df^ rotation)
	: IO::AttributeExchangingObject(0)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);

	SceneNodeInheritor* i = new SceneNodeInheritor(
		LIME_SAFEREF(parent, m_SceneNode),
		LIME_SAFEREF(manager, m_SceneManager),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNode = i;
	m_Inherited = true;
}

SceneNode::SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position)
	: IO::AttributeExchangingObject(0)
{
	LIME_ASSERT(position != nullptr);

	SceneNodeInheritor* i = new SceneNodeInheritor(
		LIME_SAFEREF(parent, m_SceneNode),
		LIME_SAFEREF(manager, m_SceneManager),
		id,
		*position->m_NativeValue);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNode = i;
	m_Inherited = true;
}

SceneNode::SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id)
	: IO::AttributeExchangingObject(0)
{
	SceneNodeInheritor* i = new SceneNodeInheritor(
		LIME_SAFEREF(parent, m_SceneNode),
		LIME_SAFEREF(manager, m_SceneManager),
		id);

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNode = i;
	m_Inherited = true;
}

SceneNode::SceneNode(SceneNode^ parent, Scene::SceneManager^ manager)
	: IO::AttributeExchangingObject(0)
{
	SceneNodeInheritor* i = new SceneNodeInheritor(
		LIME_SAFEREF(parent, m_SceneNode),
		LIME_SAFEREF(manager, m_SceneManager));

	initInheritor(i);
	setAttributeExchangingObject(i);
	m_SceneNode = i;
	m_Inherited = true;
}

void SceneNode::AddAnimator(SceneNodeAnimator^ animator)
{
	m_SceneNode->addAnimator(LIME_SAFEREF(animator, m_SceneNodeAnimator));
}

void SceneNode::AddChild(SceneNode^ child)
{
	m_SceneNode->addChild(LIME_SAFEREF(child, m_SceneNode));
}

Video::Material^ SceneNode::GetMaterial(unsigned int num)
{
	if (m_Inherited)
	{
		Video::Material^ m = OnGetMaterial(num);
		LIME_ASSERT2(m != nullptr, "If you inherit SceneNode, you must handle OnGetMaterial event and return valid Material value.");
		return m;
	}

	LIME_ASSERT(num >= 0 && num < MaterialCount);
	return Video::Material::Wrap(&m_SceneNode->getMaterial(num));
}

void SceneNode::RegisterSceneNode()
{
	if (m_Inherited)
	{
		OnRegisterSceneNode();
		return;
	}
	
	m_SceneNode->OnRegisterSceneNode();
}

void SceneNode::Remove()
{
	m_SceneNode->remove();
}

void SceneNode::RemoveAll()
{
	m_SceneNode->removeAll();
}

void SceneNode::RemoveAnimator(SceneNodeAnimator^ animator)
{
	m_SceneNode->removeAnimator(LIME_SAFEREF(animator, m_SceneNodeAnimator));
}

void SceneNode::RemoveAnimators()
{
	m_SceneNode->removeAnimators();
}

bool SceneNode::RemoveChild(SceneNode^ child)
{
	return m_SceneNode->removeChild(LIME_SAFEREF(child, m_SceneNode));
}

void SceneNode::Render()
{
	if (m_Inherited)
	{
		OnRender();
		return;
	}

	m_SceneNode->render();
}

void SceneNode::SetMaterialFlag(Video::MaterialFlag flag, bool value)
{
	m_SceneNode->setMaterialFlag((video::E_MATERIAL_FLAG)flag, value);
}

void SceneNode::SetMaterialTexture(unsigned int textureLayer, Video::Texture^ texture)
{
	m_SceneNode->setMaterialTexture(textureLayer, LIME_SAFEREF(texture, m_Texture));
}

void SceneNode::SetMaterialType(Video::MaterialType newType)
{
	m_SceneNode->setMaterialType((video::E_MATERIAL_TYPE)newType);
}

void SceneNode::UpdateAbsolutePosition()
{
	m_SceneNode->updateAbsolutePosition();
}

Vector3Df^ SceneNode::AbsolutePosition::get()
{
	return gcnew Vector3Df(m_SceneNode->getAbsolutePosition());
}

Matrix4f^ SceneNode::AbsoluteTransformation::get()
{
	return gcnew Matrix4f(m_SceneNode->getAbsoluteTransformation());
}

void SceneNode::AbsoluteTransformation::set(Matrix4f^ value)
{
	LIME_ASSERT(m_Inherited == true);
	LIME_ASSERT(value != nullptr);

	SceneNodeInheritor* i = (SceneNodeInheritor*)m_SceneNode;
	i->AbsoluteTransformation_set(*value->m_NativeValue);
}

List<SceneNodeAnimator^>^ SceneNode::AnimatorList::get()
{
	List<SceneNodeAnimator^>^ l = gcnew List<SceneNodeAnimator^>();

	core::list<scene::ISceneNodeAnimator*> a = m_SceneNode->getAnimators();
	for (core::list<scene::ISceneNodeAnimator*>::ConstIterator i = a.begin(); i != a.end(); ++i)
	{
		SceneNodeAnimator^ n = SceneNodeAnimator::Wrap(*i);
		if (n != nullptr)
			l->Add(n);
	}

	return l;
}

unsigned int SceneNode::AutomaticCulling::get()
{
	return m_SceneNode->getAutomaticCulling();
}

void SceneNode::AutomaticCulling::set(unsigned int value)
{
	m_SceneNode->setAutomaticCulling(value);
}

AABBox3Df^ SceneNode::BoundingBox::get()
{
	if (m_Inherited)
	{
		AABBox3Df^ b = OnGetBoundingBox();
		LIME_ASSERT2(b != nullptr, "If you inherit SceneNode, you must handle OnGetBoundingBox event and return valid AABBox3Df value.");
		return b;
	}
	
#if _DEBUG
	if (m_SceneNode == m_SceneNode->getSceneManager()->getRootSceneNode())
		return gcnew AABBox3Df();
#endif

	return gcnew AABBox3Df(m_SceneNode->getBoundingBox());
}

AABBox3Df^ SceneNode::BoundingBoxTransformed::get()
{
#if _DEBUG
	if (m_SceneNode == m_SceneNode->getSceneManager()->getRootSceneNode())
		return gcnew AABBox3Df();
#endif

	return gcnew AABBox3Df(m_SceneNode->getTransformedBoundingBox());
}

List<SceneNode^>^ SceneNode::ChildList::get()
{
	List<SceneNode^>^ l = gcnew List<SceneNode^>();

	core::list<scene::ISceneNode*> a = m_SceneNode->getChildren();
	for (core::list<scene::ISceneNode*>::ConstIterator i = a.begin(); i != a.end(); ++i)
	{
		SceneNode^ n = Wrap(*i);
		if (n != nullptr)
			l->Add(n);
	}

	return l;
}

DebugSceneType SceneNode::DebugDataVisible::get()
{
	return (DebugSceneType)m_SceneNode->isDebugDataVisible();
}

void SceneNode::DebugDataVisible::set(DebugSceneType value)
{
	m_SceneNode->setDebugDataVisible((scene::E_DEBUG_SCENE_TYPE)value);
}

bool SceneNode::DebugObject::get()
{
	return m_SceneNode->isDebugObject();
}

void SceneNode::DebugObject::set(bool value)
{
	m_SceneNode->setIsDebugObject(value);
}

int SceneNode::ID::get()
{
	return m_SceneNode->getID();
}

void SceneNode::ID::set(int value)
{
	m_SceneNode->setID(value);
}

unsigned int SceneNode::MaterialCount::get()
{
	if (m_Inherited)
		return OnGetMaterialCount();

	return m_SceneNode->getMaterialCount();
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
	return SceneNode::Wrap(n);
}

void SceneNode::Parent::set(SceneNode^ value)
{
	m_SceneNode->setParent(value->m_SceneNode);
}

Vector3Df^ SceneNode::Position::get()
{
	return gcnew Vector3Df(m_SceneNode->getPosition());
}

void SceneNode::Position::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setPosition(*value->m_NativeValue);
}

Matrix4f^ SceneNode::RelativeTransformation::get()
{
	return gcnew Matrix4f(m_SceneNode->getRelativeTransformation());
}

Vector3Df^ SceneNode::Rotation::get()
{
	return gcnew Vector3Df(m_SceneNode->getRotation());
}

void SceneNode::Rotation::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setRotation(*value->m_NativeValue);
}

Vector3Df^ SceneNode::Scale::get()
{
	return gcnew Vector3Df(m_SceneNode->getScale());
}

void SceneNode::Scale::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneNode->setScale(*value->m_NativeValue);
}

Scene::SceneManager^ SceneNode::SceneManager::get()
{
	return Scene::SceneManager::Wrap(m_SceneNode->getSceneManager());
}

void SceneNode::SceneManager::set(Scene::SceneManager^ value)
{
	LIME_ASSERT(m_Inherited == true);

	SceneNodeInheritor* i = (SceneNodeInheritor*)m_SceneNode;
	i->SceneManager_set(LIME_SAFEREF(value, m_SceneManager));
}

Scene::TriangleSelector^ SceneNode::TriangleSelector::get()
{
	return Scene::TriangleSelector::Wrap(m_SceneNode->getTriangleSelector());
}

void SceneNode::TriangleSelector::set(Scene::TriangleSelector^ value)
{
	m_SceneNode->setTriangleSelector(LIME_SAFEREF(value, m_TriangleSelector));
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
	return String::Format("SceneNode: Type={0}; ID={1}; Name={2}", Type, ID, Name);
}

void SceneNode::initInheritor(SceneNodeInheritor* i)
{
	i->m_renderHandler = gcnew RenderEventHandler(this, &SceneNode::Render);
	i->m_OnRegisterSceneNodeHandler = gcnew RegisterSceneNodeEventHandler(this, &SceneNode::RegisterSceneNode);
	i->m_getBoundingBoxHandler = gcnew GetBoundingBoxEventHandler(this, &SceneNode::BoundingBox::get);
	i->m_getMaterialCountHandler = gcnew GetMaterialCountEventHandler(this, &SceneNode::MaterialCount::get);
	i->m_getMaterialHandler = gcnew GetMaterialEventHandler(this, &SceneNode::GetMaterial);
}

} // end namespace Scene
} // end namespace IrrlichtLime