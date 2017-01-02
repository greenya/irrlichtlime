#include "stdafx.h"
#include "CollisionHit.h"
#include "MeshBuffer.h"
#include "SceneNode.h"
#include "TriangleSelector.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

CollisionHit::CollisionHit()
	: Lime::NativeValue<scene::SCollisionHit>(true)
{
	m_NativeValue = new scene::SCollisionHit();
}

CollisionHit::CollisionHit(CollisionHit^ copy)
	: Lime::NativeValue<scene::SCollisionHit>(true)
{
	LIME_ASSERT(copy != nullptr);

	m_NativeValue = new scene::SCollisionHit(*copy->m_NativeValue);
}

Vector3Df CollisionHit::Intersection::get()
{
	return Vector3Df(m_NativeValue->Intersection);
}

void CollisionHit::Intersection::set(Vector3Df value)
{
	m_NativeValue->Intersection = value;
}

unsigned int CollisionHit::MaterialIndex::get()
{
	return m_NativeValue->MaterialIndex;
}

void CollisionHit::MaterialIndex::set(unsigned int value)
{
	m_NativeValue->MaterialIndex = value;
}

MeshBuffer^ CollisionHit::MeshBuffer::get()
{
	return Scene::MeshBuffer::Wrap(const_cast<scene::IMeshBuffer*>(m_NativeValue->MeshBuffer));
}

void CollisionHit::MeshBuffer::set(Scene::MeshBuffer^ value)
{
	m_NativeValue->MeshBuffer = LIME_SAFEREF(value, m_MeshBuffer);
}

SceneNode^ CollisionHit::Node::get()
{
	return SceneNode::Wrap(m_NativeValue->Node);
}

void CollisionHit::Node::set(SceneNode^ value)
{
	m_NativeValue->Node = LIME_SAFEREF(value, m_SceneNode);
}

Triangle3Df CollisionHit::Triangle::get()
{
	return Triangle3Df(m_NativeValue->Triangle);
}

void CollisionHit::Triangle::set(Triangle3Df value)
{
	m_NativeValue->Triangle = value;
}

TriangleSelector^ CollisionHit::TriangleSelector::get()
{
	return Scene::TriangleSelector::Wrap(m_NativeValue->TriangleSelector);
}

void CollisionHit::TriangleSelector::set(Scene::TriangleSelector^ value)
{
	m_NativeValue->TriangleSelector = LIME_SAFEREF(value, m_TriangleSelector);
}

} // end namespace Scene
} // end namespace IrrlichtLime