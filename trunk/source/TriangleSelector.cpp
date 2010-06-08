#include "stdafx.h"
#include "SceneNode.h"
#include "TriangleSelector.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

TriangleSelector^ TriangleSelector::Wrap(scene::ITriangleSelector* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew TriangleSelector(ref);
}

TriangleSelector::TriangleSelector(scene::ITriangleSelector* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_TriangleSelector = ref;
}

SceneNode^ TriangleSelector::GetSceneNodeForTriangle(unsigned int triangleIndex)
{
	LIME_ASSERT(triangleIndex < TriangleCount);

	scene::ISceneNode* n = (scene::ISceneNode*)m_TriangleSelector->getSceneNodeForTriangle(triangleIndex); // !!! cast to non-const pointer
	return SceneNode::Wrap(n);
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(AABBox3Df^ box, unsigned int maxTriangleCount, Matrix4f^ transform)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);
	LIME_ASSERT(transform != nullptr);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue, transform->m_NativeValue);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(AABBox3Df^ box, unsigned int maxTriangleCount)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(Line3Df^ line, unsigned int maxTriangleCount, Matrix4f^ transform)
{
	LIME_ASSERT(line != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);
	LIME_ASSERT(transform != nullptr);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *line->m_NativeValue, transform->m_NativeValue);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(Line3Df^ line, unsigned int maxTriangleCount)
{
	LIME_ASSERT(line != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *line->m_NativeValue);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(unsigned int maxTriangleCount, Matrix4f^ transform)
{
	LIME_ASSERT(maxTriangleCount > 0);
	LIME_ASSERT(transform != nullptr);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, transform->m_NativeValue);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

List<Triangle3Df^>^ TriangleSelector::GetTriangles(unsigned int maxTriangleCount)
{
	LIME_ASSERT(maxTriangleCount > 0);

	List<Triangle3Df^>^ l = gcnew List<Triangle3Df^>();
	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c);
	for (int i = 0; i < c; i++)
		l->Add(gcnew Triangle3Df(t[i]));

	delete t;
	return l;
}

unsigned int TriangleSelector::TriangleCount::get()
{
	return (unsigned int)m_TriangleSelector->getTriangleCount();
}

} // end namespace Scene
} // end namespace IrrlichtLime