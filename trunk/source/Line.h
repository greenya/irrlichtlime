#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::Runtime::InteropServices; // for OutAttribute

namespace IrrlichtLime {
namespace Core {

public ref class Line3Df : Lime::NativeValue<core::line3df>
{
public:

	Line3Df()
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df();
	}

	Line3Df(Vector3Df^ start, Vector3Df^ end)
		: Lime::NativeValue<core::line3df>(true)
	{
		LIME_ASSERT(start != nullptr);
		LIME_ASSERT(end != nullptr);

		m_NativeValue = new core::line3df(*start->m_NativeValue, *end->m_NativeValue);
	}

	Line3Df(float startX, float startY, float startZ, float endX, float endY, float endZ)
		: Lime::NativeValue<core::line3df>(true)
	{
		m_NativeValue = new core::line3df(startX, startY, startZ, endX, endY, endZ);
	}

	void Set(Line3Df^ newLine)
	{
		LIME_ASSERT(newLine != nullptr);
		m_NativeValue->setLine(*newLine->m_NativeValue);
	}

	void Set(Vector3Df^ newStart, Vector3Df^ newEnd)
	{
		LIME_ASSERT(newStart != nullptr);
		LIME_ASSERT(newEnd != nullptr);

		m_NativeValue->setLine(*newStart->m_NativeValue, *newEnd->m_NativeValue);
	}

	void Set(float newStartX, float newStartY, float newStartZ, float newEndX, float newEndY, float newEndZ)
	{
		m_NativeValue->setLine(newStartX, newStartY, newStartZ, newEndX, newEndY, newEndZ);
	}

	bool IsPointBetweenStartAndEnd(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		return m_NativeValue->isPointBetweenStartAndEnd(*point->m_NativeValue);
	}

	Vector3Df^ GetClosestPoint(Vector3Df^ point)
	{
		LIME_ASSERT(point != nullptr);
		return gcnew Vector3Df(m_NativeValue->getClosestPoint(*point->m_NativeValue));
	}

	bool GetIntersectionWithSphere(Vector3Df^ sphereOrigin, float sphereRadius, [Out] double% distance)
	{
		LIME_ASSERT(sphereOrigin != nullptr);

		f64 d = 0.0f;
		bool b = m_NativeValue->getIntersectionWithSphere(
			*sphereOrigin->m_NativeValue,
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

	property Vector3Df^ Middle
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getMiddle()); }
	}

	property Vector3Df^ Vector
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getVector()); }
	}

	property Vector3Df^ Start
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->start); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->start = *value->m_NativeValue; }
	}

	property Vector3Df^ End
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->end); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->end = *value->m_NativeValue; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0})-({1})", Start, End);
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