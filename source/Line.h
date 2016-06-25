#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Line3Df
{
public:

	static property Line3Df Default { Line3Df get() { return Line3Df(0, 0, 0, 1, 1, 1); } }

	static Line3Df operator + (Line3Df v1, Vector3Df v2)
	{
		return Line3Df(v1.Start + v2, v1.End + v2);
	}

	static Line3Df operator - (Line3Df v1, Vector3Df v2)
	{
		return Line3Df(v1.Start - v2, v1.End - v2);
	}

	Vector3Df Start;
	Vector3Df End;

	Line3Df(float startX, float startY, float startZ, float endX, float endY, float endZ)
		: Start(startX, startY, startZ), End(endX, endY, endZ)
	{
	}

	Line3Df(Vector3Df start, Vector3Df end)
		: Start(start), End(end)
	{
	}

	void Set(float newStartX, float newStartY, float newStartZ, float newEndX, float newEndY, float newEndZ)
	{
		Start.Set(newStartX, newStartY, newStartZ);
		End.Set(newEndX, newEndY, newEndZ);
	}

	void Set(Vector3Df newStart, Vector3Df newEnd)
	{
		Start = newStart;
		End = newEnd;
	}

	bool IsPointBetweenStartAndEnd(Vector3Df point)
	{
		return point.IsBetweenPoints(Start, End);
	}

	Vector3Df GetClosestPoint(Vector3Df point)
	{
		Vector3Df c = point - Start;
		Vector3Df v = End - Start;
		float d = (float)v.Length;
		v /= d;
		float t = v.DotProduct(c);

		if (t < (float)0.0)
			return Start;
		if (t > d)
			return End;

		v *= t;
		return Start + v;
	}

	bool GetIntersectionWithSphere(Vector3Df sphereOrigin, float sphereRadius, [Out] double% distance)
	{
		Vector3Df q = sphereOrigin - Start;
		float c = q.Length;
		float v = q.DotProduct(Vector.Normalize());
		float d = sphereRadius * sphereRadius - (c*c - v*v);

		if (d < 0.0)
			return false;

		distance = v - LimeM::Squareroot ( d );
		return true;
	}

	property float Length
	{
		float get() { return Start.GetDistanceFrom(End); }
	}

	property float LengthSQ
	{
		float get() { return Start.GetDistanceFromSQ(End); }
	}

	property Vector3Df Middle
	{
		Vector3Df get() { return (Start + End) / 2; }
	}

	property Vector3Df Vector
	{
		Vector3Df get() { return End - Start; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) - ({1})", Start, End);
	}

internal:

	Line3Df(const core::line3df& value)
	{
#ifdef FAST_FROM_NATIVE
		*this = (Line3Df&)value;
#else
		Start = Vector3Df(value.start);
		End = Vector3Df(value.end);
#endif
	}

	operator core::line3df()
	{
#ifdef FAST_TO_NATIVE
		return (core::line3df&)*this;
		//return *(interior_ptr<core::line3df>)this;
#else
		return core::line3df(Start.ToNative(), End.ToNative());
#endif
	}

	core::line3df ToNative()
	{
		return (core::line3df)*this;
	}
};

} // end namespace Core
} // end namespace IrrlichtLime