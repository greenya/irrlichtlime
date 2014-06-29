#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Line3Df : Lime::NativeValue<core::line3df>
{
public:

	static bool operator == (Line3Df^ v1, Line3Df^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (Line3Df^ v1, Line3Df^ v2)
	{
		return !(v1 == v2);
	}

	Line3Df()
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df();
	}

	Line3Df(Line3Df^ copy)
		: Lime::NativeValue<core::line3df>(true)
	{
		LIME_ASSERT(copy != nullptr);

		m_NativeValue = new core::line3df();
		m_NativeValue->setLine(*copy->m_NativeValue);
	}

	Line3Df(float startX, float startY, float startZ, float endX, float endY, float endZ)
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df(startX, startY, startZ, endX, endY, endZ);
	}

	Line3Df(Vector3Df start, Vector3Df end)
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df(start, end);
	}

	void Set(float newStartX, float newStartY, float newStartZ, float newEndX, float newEndY, float newEndZ)
	{
		m_NativeValue->setLine(newStartX, newStartY, newStartZ, newEndX, newEndY, newEndZ);
	}

	void Set(Vector3Df newStart, Vector3Df newEnd)
	{
		m_NativeValue->setLine(newStart, newEnd);
	}

	void Set(Line3Df^ newLine)
	{
		LIME_ASSERT(newLine != nullptr);
		m_NativeValue->setLine(*newLine->m_NativeValue);
	}

	bool IsPointBetweenStartAndEnd(Vector3Df point)
	{
		return m_NativeValue->isPointBetweenStartAndEnd(point);
	}

	Vector3Df GetClosestPoint(Vector3Df point)
	{
		return Vector3Df(m_NativeValue->getClosestPoint(point));
	}

	bool GetIntersectionWithSphere(Vector3Df sphereOrigin, float sphereRadius, [Out] double% distance)
	{
		f64 d = 0.0f;
		bool b = m_NativeValue->getIntersectionWithSphere(
			sphereOrigin,
			sphereRadius,
			d);

		if (b)
			distance = d;

		return b;
	}

	property float Length
	{
		float get() { return m_NativeValue->getLength(); }
	}

	property float LengthSQ
	{
		float get() { return m_NativeValue->getLengthSQ(); }
	}

	property Vector3Df Middle
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getMiddle()); }
	}

	property Vector3Df Vector
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getVector()); }
	}

	property Vector3Df Start
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->start); }
		void set(Vector3Df value) { m_NativeValue->start = value; }
	}

	property Vector3Df End
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->end); }
		void set(Vector3Df value) { m_NativeValue->end = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) - ({1})", Start, End);
	}

internal:

	Line3Df(const core::line3df& value)
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime