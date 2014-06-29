#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Plane3Df : Lime::NativeValue<core::plane3df>
{
public:

	static bool operator == (Plane3Df^ v1, Plane3Df^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (Plane3Df^ v1, Plane3Df^ v2)
	{
		return !(v1 == v2);
	}

	Plane3Df()
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df();
	}

	Plane3Df(Plane3Df^ copy)
		: Lime::NativeValue<core::plane3df>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new core::plane3df(copy->m_NativeValue->Normal, copy->m_NativeValue->D);
	}

	Plane3Df(Vector3Df memberPoint, Vector3Df normal)
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df(memberPoint, normal);
	}

	Plane3Df(float pointX, float pointY, float pointZ, float normalX, float normalY, float normalZ)
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df(pointX, pointY, pointZ, normalX, normalY, normalZ);
	}

	Plane3Df(Vector3Df point1, Vector3Df point2, Vector3Df point3)
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df(point1, point2, point3);
	}

	Plane3Df(Vector3Df normal, float d)
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df(normal, d);
	}

	void Set(Vector3Df memberPoint, Vector3Df normal)
	{
		m_NativeValue->setPlane(memberPoint, normal);
	}

	void Set(Vector3Df point1, Vector3Df point2, Vector3Df point3)
	{
		m_NativeValue->setPlane(point1, point2, point3);
	}

	void Set(Vector3Df normal, float d)
	{
		m_NativeValue->setPlane(normal, d);
	}

	bool GetIntersectionWithLine(Vector3Df linePoint, Vector3Df lineVect, [Out] Vector3Df% intersection)
	{
		core::vector3df i;
		bool b = m_NativeValue->getIntersectionWithLine(
			linePoint,
			lineVect,
			i);

		if (b)
			intersection = Vector3Df(i);

		return b;
	}

	float GetKnownIntersectionWithLine(Vector3Df linePoint1, Vector3Df linePoint2)
	{
		return m_NativeValue->getKnownIntersectionWithLine(linePoint1, linePoint2);
	}

	bool GetIntersectionWithLimitedLine(Vector3Df linePoint1, Vector3Df linePoint2, [Out] Vector3Df% intersection)
	{
		core::vector3df i;
		bool b = m_NativeValue->getIntersectionWithLimitedLine(
			linePoint1,
			linePoint2,
			i);

		if (b)
			intersection = Vector3Df(i);

		return b;
	}

	bool GetIntersectionWithPlane(Plane3Df^ other, [Out] Vector3Df% intersectionLinePoint, [Out] Vector3Df% intersectionLineVector)
	{
		LIME_ASSERT(other != nullptr);

		core::vector3df p;
		core::vector3df v;
		bool b = m_NativeValue->getIntersectionWithPlane(
			*other->m_NativeValue,
			p, v);

		if (b)
		{
			intersectionLinePoint = Vector3Df(p);
			intersectionLineVector = Vector3Df(v);
		}

		return b;
	}

	bool GetIntersectionWithPlanes(Plane3Df^ other1, Plane3Df^ other2, [Out] Vector3Df% intersectionPoint)
	{
		LIME_ASSERT(other1 != nullptr);
		LIME_ASSERT(other2 != nullptr);

		core::vector3df p;
		bool b = m_NativeValue->getIntersectionWithPlanes(
			*other1->m_NativeValue,
			*other2->m_NativeValue,
			p);

		if (b)
			intersectionPoint = Vector3Df(p);

		return b;
	}

	bool IsFrontFacing(Vector3Df lookDirection)
	{
		return m_NativeValue->isFrontFacing(lookDirection);
	}

	float GetDistanceTo(Vector3Df point)
	{
		return m_NativeValue->getDistanceTo(point);
	}

	bool Intersects(Plane3Df^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->existsIntersection(*other->m_NativeValue);
	}

	property Vector3Df MemberPoint
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getMemberPoint()); }
		void set(Vector3Df value) { m_NativeValue->recalculateD(value); }
	}

	property Vector3Df Normal
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->Normal); }
		void set(Vector3Df value) { m_NativeValue->Normal = value; }
	}

	property float D
	{
		float get() { return m_NativeValue->D; }
		void set(float value) { m_NativeValue->D = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) D={1}", Normal, D);
	}

internal:

	Plane3Df(const core::plane3df& value)
		: Lime::NativeValue<core::plane3df>(true)
	{
		m_NativeValue = new core::plane3df(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime