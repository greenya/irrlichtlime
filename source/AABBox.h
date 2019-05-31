#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class AABBox : Lime::NativeValue<core::aabbox3df>
{
public:

	static bool operator == (AABBox^ v1, AABBox^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (AABBox^ v1, AABBox^ v2)
	{
		return !(v1 == v2);
	}

	AABBox()
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		m_NativeValue = new core::aabbox3df();
	}

	AABBox(AABBox^ copy)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		LIME_ASSERT(copy != nullptr);

		m_NativeValue = new core::aabbox3df();
		m_NativeValue->reset(*copy->m_NativeValue);
	}

	AABBox(float minx, float miny, float minz, float maxx, float maxy, float maxz)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		m_NativeValue = new core::aabbox3df(minx, miny, minz, maxx, maxy, maxz);
	}

	AABBox(float x, float y, float z)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		m_NativeValue = new core::aabbox3df(x, y, z, x, y, z);
	}

	AABBox(Vector3Df^ min, Vector3Df^ max)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		LIME_ASSERT(min != nullptr);
		LIME_ASSERT(max != nullptr);

		m_NativeValue = new core::aabbox3df(*min->m_NativeValue, *max->m_NativeValue);
	}

	AABBox(Vector3Df^ point)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		LIME_ASSERT(point != nullptr);
		m_NativeValue = new core::aabbox3df(*point->m_NativeValue);
	}

	void Set(float minx, float miny, float minz, float maxx, float maxy, float maxz)
	{
		m_NativeValue->MinEdge.set(minx, miny, minz);
		m_NativeValue->MaxEdge.set(maxx, maxy, maxz);
	}

	void Set(float x, float y, float z)
	{
		m_NativeValue->reset(x, y, z);
	}

	void Set(Vector3Df^ min, Vector3Df^ max)
	{
		LIME_ASSERT(min != nullptr);
		LIME_ASSERT(max != nullptr);

		m_NativeValue->MinEdge = *min->m_NativeValue;
		m_NativeValue->MaxEdge = *max->m_NativeValue;
	}

	void Set(Vector3Df^ newPoint)
	{
		LIME_ASSERT(newPoint != nullptr);
		m_NativeValue->reset(*newPoint->m_NativeValue);
	}

	void Set(AABBox^ newBox)
	{
		LIME_ASSERT(newBox != nullptr);
		m_NativeValue->reset(*newBox->m_NativeValue);
	}

	void AddInternalPoint(float x, float y, float z)
	{
		m_NativeValue->addInternalPoint(x, y, z);
	}

	void AddInternalPoint(Vector3Df^ p)
	{
		LIME_ASSERT(p != nullptr);
		m_NativeValue->addInternalPoint(*p->m_NativeValue);
	}

	void AddInternalBox(AABBox^ b)
	{
		LIME_ASSERT(b != nullptr);
		m_NativeValue->addInternalBox(*b->m_NativeValue);
	}

	bool IsInside(Vector3Df^ p)
	{
		LIME_ASSERT(p != nullptr);
		return m_NativeValue->isPointInside(*p->m_NativeValue);
	}

	bool IsInsideFully(Vector3Df^ p)
	{
		LIME_ASSERT(p != nullptr);
		return m_NativeValue->isPointTotalInside(*p->m_NativeValue);
	}

	bool IsInside(AABBox^ b)
	{
		LIME_ASSERT(b != nullptr);
		return m_NativeValue->isFullInside(*b->m_NativeValue);
	}

	void Repair()
	{
		m_NativeValue->repair();
	}

	property float Area
	{
		float get() { return m_NativeValue->getArea(); }
	}

	property Vector3Df^ Center
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getCenter()); }
	}

	property array<Vector3Df^>^ Edges
	{
		array<Vector3Df^>^ get()
		{
			core::vector3df v[8];
			m_NativeValue->getEdges(v);

			array<Vector3Df^>^ a = gcnew array<Vector3Df^>(8);
			for (int i = 0; i < 8; i++)
				a[i] = gcnew Vector3Df(v[i]);
			
			return a;
		}
	}

	property bool Empty
	{
		bool get() { return m_NativeValue->isEmpty(); }
	}

	property Vector3Df^ Extent
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getExtent()); }
	}

	property Vector3Df^ MaxEdge
	{
		Vector3Df^ get()
		{
			return gcnew Vector3Df(m_NativeValue->MaxEdge);
		}
		void set(Vector3Df^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->MaxEdge = *value->m_NativeValue;
		}
	}

	property Vector3Df^ MinEdge
	{
		Vector3Df^ get()
		{
			return gcnew Vector3Df(m_NativeValue->MinEdge);
		}
		void set(Vector3Df^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->MinEdge = *value->m_NativeValue;
		}
	}

	property float Radius
	{
		float get() { return m_NativeValue->getRadius(); }
	}

	property float Volume
	{
		float get() { return m_NativeValue->getVolume(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("MinEdge={0}; MaxEdge={1}", MinEdge, MaxEdge);
	}

internal:

	AABBox(const core::aabbox3df& other)
		: Lime::NativeValue<core::aabbox3df>(true)
	{
		m_NativeValue = new core::aabbox3df(other);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime