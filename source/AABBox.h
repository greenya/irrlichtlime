#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class AABBox3Df : Lime::NativeValue<core::aabbox3df>
{
public:

	AABBox3Df(float minx, float miny, float minz, float maxx, float maxy, float maxz)
	{
		m_NativeValue = new core::aabbox3df(minx, miny, minz, maxx, maxy, maxz);
	}

	AABBox3Df(Vector3Df^ min, Vector3Df^ max)
	{
		LIME_ASSERT(min != nullptr);
		LIME_ASSERT(max != nullptr);
		m_NativeValue = new core::aabbox3df(*min->m_NativeValue, *max->m_NativeValue);
	}

	AABBox3Df(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		m_NativeValue = new core::aabbox3df(*point->m_NativeValue);
	}

	AABBox3Df()
	{
		m_NativeValue = new core::aabbox3df();
	}

	void Reset(float x, float y, float z)
	{
		m_NativeValue->reset(x, y, z);
	}

	void Reset(AABBox3Df^ initValue)
	{
		LIME_ASSERT(initValue != nullptr);
		m_NativeValue->reset(*initValue->m_NativeValue);
	}

	void Reset(Vector3Df^ initValue)
	{
		LIME_ASSERT(initValue != nullptr);
		m_NativeValue->reset(*initValue->m_NativeValue);
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

	void AddInternalBox(AABBox3Df^ b)
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

	bool IsInside(AABBox3Df^ b)
	{
		LIME_ASSERT(b != nullptr);
		return m_NativeValue->isFullInside(*b->m_NativeValue);
	}

	void Repair()
	{
		m_NativeValue->repair();
	}

	property Vector3Df^ Center
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getCenter()); }
	}

	property Vector3Df^ Extent
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getExtent()); }
	}

	property bool Empty
	{
		bool get() { return m_NativeValue->isEmpty(); }
	}

	property float Volume
	{
		float get() { return m_NativeValue->getVolume(); }
	}

	property float Area
	{
		float get() { return m_NativeValue->getArea(); }
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

	virtual String^ ToString() override
	{
		return String::Format("MinEdge={0}; MaxEdge={1}", MinEdge, MaxEdge);
	}

internal:

	AABBox3Df(const core::aabbox3df& other)
	{
		m_NativeValue = new core::aabbox3df(other);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime