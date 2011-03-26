#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Triangle3Df : Lime::NativeValue<core::triangle3df>
{
public:

	static bool operator == (Triangle3Df^ v1, Triangle3Df^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (Triangle3Df^ v1, Triangle3Df^ v2)
	{
		return !(v1 == v2);
	}

	Triangle3Df()
		: Lime::NativeValue<core::triangle3df>(true)
	{
		m_NativeValue = new core::triangle3df();
	}

	Triangle3Df(Triangle3Df^ copy)
		: Lime::NativeValue<core::triangle3df>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new core::triangle3df(copy->m_NativeValue->pointA, copy->m_NativeValue->pointB, copy->m_NativeValue->pointC);
	}

	Triangle3Df(Vector3Df^ point1, Vector3Df^ point2, Vector3Df^ point3)
		: Lime::NativeValue<core::triangle3df>(true)
	{
		LIME_ASSERT(point1 != nullptr);
		LIME_ASSERT(point2 != nullptr);
		LIME_ASSERT(point3 != nullptr);

		m_NativeValue = new core::triangle3df(*point1->m_NativeValue, *point2->m_NativeValue, *point3->m_NativeValue);
	}

	void Set(Vector3Df^ point1, Vector3Df^ point2, Vector3Df^ point3)
	{
		LIME_ASSERT(point1 != nullptr);
		LIME_ASSERT(point2 != nullptr);
		LIME_ASSERT(point3 != nullptr);

		m_NativeValue->set(*point1->m_NativeValue, *point2->m_NativeValue, *point3->m_NativeValue);
	}

	Vector3Df^ GetClosestPointOnTriangle(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		return gcnew Vector3Df(m_NativeValue->closestPointOnTriangle(*point->m_NativeValue));
	}

	bool IsTotalInsideBox(AABBox^ box)
	{
		LIME_ASSERT(box != nullptr);
		return m_NativeValue->isTotalInsideBox(*box->m_NativeValue);
	}

	bool IsTotalOutsideBox(AABBox^ box)
	{
		LIME_ASSERT(box != nullptr);
		return m_NativeValue->isTotalOutsideBox(*box->m_NativeValue);
	}

	bool IsFrontFacing(Vector3Df^ lookDirection)
	{
		LIME_ASSERT(lookDirection != nullptr);
		return m_NativeValue->isFrontFacing(*lookDirection->m_NativeValue);
	}

	bool IsPointInside(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		return m_NativeValue->isPointInside(*point->m_NativeValue);
	}

	bool IsPointInsideFast(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		return m_NativeValue->isPointInsideFast(*point->m_NativeValue);
	}

	bool GetIntersectionWithLine(Vector3Df^ linePoint, Vector3Df^ lineVect, [Out] Vector3Df^% intersection)
	{
		LIME_ASSERT(linePoint != nullptr);
		LIME_ASSERT(lineVect != nullptr);

		core::vector3df i;
		bool b = m_NativeValue->getIntersectionWithLine(
			*linePoint->m_NativeValue,
			*lineVect->m_NativeValue,
			i);

		if (b)
			intersection = gcnew Vector3Df(i);

		return b;
	}

	bool GetIntersectionWithLimitedLine(Line3Df^ line, [Out] Vector3Df^% intersection)
	{
		LIME_ASSERT(line != nullptr);

		core::vector3df i;
		bool b = m_NativeValue->getIntersectionWithLimitedLine(
			*line->m_NativeValue,
			i);

		if (b)
			intersection = gcnew Vector3Df(i);

		return b;
	}

	bool GetIntersectionOfPlaneWithLine(Vector3Df^ linePoint, Vector3Df^ lineVect, [Out] Vector3Df^% intersection)
	{
		LIME_ASSERT(linePoint != nullptr);
		LIME_ASSERT(lineVect != nullptr);

		core::vector3df i;
		bool b = m_NativeValue->getIntersectionOfPlaneWithLine(
			*linePoint->m_NativeValue,
			*lineVect->m_NativeValue,
			i);

		if (b)
			intersection = gcnew Vector3Df(i);

		return b;
	}

	property Plane3Df^ Plane
	{
		Plane3Df^ get() { return gcnew Plane3Df(m_NativeValue->getPlane()); }
	}

	property float Area
	{
		float get() { return m_NativeValue->getArea(); }
	}

	property Vector3Df^ Normal
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getNormal()); }
	}

	property Vector3Df^ A
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->pointA); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->pointA = *value->m_NativeValue; }
	}

	property Vector3Df^ B
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->pointB); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->pointB = *value->m_NativeValue; }
	}

	property Vector3Df^ C
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->pointC); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->pointC = *value->m_NativeValue; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) - ({1}) - ({2})", A, B, C);
	}

internal:

	Triangle3Df(const core::triangle3df& value)
		: Lime::NativeValue<core::triangle3df>(true)
	{
		m_NativeValue = new core::triangle3df(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime