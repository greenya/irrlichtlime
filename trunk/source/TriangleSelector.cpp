#include "stdafx.h"
#include "SceneNode.h"
#include "ReferenceCounted.h"
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

SceneNode^ TriangleSelector::GetSceneNodeForTriangle(int triangleIndex)
{
	LIME_ASSERT(triangleIndex >= 0 && triangleIndex < TriangleCount);

	scene::ISceneNode* n = m_TriangleSelector->getSceneNodeForTriangle(triangleIndex);
	return SceneNode::Wrap(n);
}

TriangleSelector^ TriangleSelector::GetSelector(int selectorIndex)
{
	LIME_ASSERT(selectorIndex >= 0 && selectorIndex < SelectorCount);

	scene::ITriangleSelector* s = m_TriangleSelector->getSelector(selectorIndex);
	return TriangleSelector::Wrap(s);
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(AABBox^ box, int maxTriangleCount, Matrix^ transform, bool useNodeTransform, List<CollisionTriangleRange>^ outTriangleInfo)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;
	if (outTriangleInfo != nullptr)
	{
		core::array<scene::SCollisionTriangleRange> triangleInfoNative;
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform, &triangleInfoNative);

		outTriangleInfo->Clear();		
		for (unsigned int i = 0; i < triangleInfoNative.size(); i++)
			outTriangleInfo->Add(CollisionTriangleRange(triangleInfoNative[i]));
	}
	else
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);

	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(AABBox^ box, int maxTriangleCount, Matrix^ transform, bool useNodeTransform)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(AABBox^ box, int maxTriangleCount, Matrix^ transform)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue, LIME_SAFEREF(transform, m_NativeValue));
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(AABBox^ box, int maxTriangleCount)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, *box->m_NativeValue);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(Line3Df line, int maxTriangleCount, Matrix^ transform, bool useNodeTransform, List<CollisionTriangleRange>^ outTriangleInfo)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;
	if (outTriangleInfo != nullptr)
	{
		core::array<scene::SCollisionTriangleRange> triangleInfoNative;
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, line, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform, &triangleInfoNative);

		outTriangleInfo->Clear();		
		for (unsigned int i = 0; i < triangleInfoNative.size(); i++)
			outTriangleInfo->Add(CollisionTriangleRange(triangleInfoNative[i]));
	}
	else
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, line, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);

	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(Line3Df line, int maxTriangleCount, Matrix^ transform, bool useNodeTransform)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, line, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(Line3Df line, int maxTriangleCount, Matrix^ transform)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, line, LIME_SAFEREF(transform, m_NativeValue));
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(Line3Df line, int maxTriangleCount)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, line);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(int maxTriangleCount, Matrix^ transform, bool useNodeTransform, List<CollisionTriangleRange>^ outTriangleInfo)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;
	if (outTriangleInfo != nullptr)
	{
		core::array<scene::SCollisionTriangleRange> triangleInfoNative;
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform, &triangleInfoNative);

		outTriangleInfo->Clear();		
		for (unsigned int i = 0; i < triangleInfoNative.size(); i++)
			outTriangleInfo->Add(CollisionTriangleRange(triangleInfoNative[i]));
	}
	else
		m_TriangleSelector->getTriangles(t, maxTriangleCount, c, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);

	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(int maxTriangleCount, Matrix^ transform, bool useNodeTransform)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, LIME_SAFEREF(transform, m_NativeValue), useNodeTransform);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(int maxTriangleCount, Matrix^ transform)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c, LIME_SAFEREF(transform, m_NativeValue));
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

List<Triangle3Df>^ TriangleSelector::GetTriangles(int maxTriangleCount)
{
	LIME_ASSERT(maxTriangleCount > 0);

	core::triangle3df* t = new core::triangle3df[maxTriangleCount];
	int c;

	m_TriangleSelector->getTriangles(t, maxTriangleCount, c);
	List<Triangle3Df>^ l = gcnew List<Triangle3Df>(c);
	for (int i = 0; i < c; i++)
		l->Add(Triangle3Df(t[i]));

	delete[] t;
	return l;
}

int TriangleSelector::SelectorCount::get()
{
	return m_TriangleSelector->getSelectorCount();
}

int TriangleSelector::TriangleCount::get()
{
	return m_TriangleSelector->getTriangleCount();
}

String^ TriangleSelector::ToString()
{
	return String::Format("TriangleSelector: {0} triangle(s) in {1} selector(s)", TriangleCount, SelectorCount);
}

} // end namespace Scene
} // end namespace IrrlichtLime