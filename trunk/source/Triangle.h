#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Triangle3Df
{
public:

	Vector3Df A;
	Vector3Df B;
	Vector3Df C;

	/*static bool operator == (Triangle3Df^ v1, Triangle3Df^ v2)
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
	}*/

	Triangle3Df(Vector3Df point1, Vector3Df point2, Vector3Df point3)
		: A(point1), B(point2), C(point3)
	{
	}

	void Set(Vector3Df point1, Vector3Df point2, Vector3Df point3)
	{
		A = point1;
		B = point2;
		C = point3;
	}

	Vector3Df GetClosestPointOnTriangle(Vector3Df point)
	{
		Vector3Df rab = Line3Df(A, B).GetClosestPoint(point);
		Vector3Df rbc = Line3Df(B, C).GetClosestPoint(point);
		Vector3Df rca = Line3Df(C, A).GetClosestPoint(point);

		float d1 = rab.GetDistanceFrom(point);
		float d2 = rbc.GetDistanceFrom(point);
		float d3 = rca.GetDistanceFrom(point);

		if (d1 < d2)
			return d1 < d3 ? rab : rca;

		return d2 < d3 ? rbc : rca;
	}

	bool IsTotalInsideBox(AABBox^ box)
	{
		LIME_ASSERT(box != nullptr);
		return (box->IsInside(A) &&
				box->IsInside(B) &&
				box->IsInside(C));
	}

	bool IsTotalOutsideBox(AABBox^ box)
	{
		LIME_ASSERT(box != nullptr);
		Vector3Df minEdge = box->MinEdge;
		Vector3Df maxEdge = box->MaxEdge;
		return ((A.X > maxEdge.X && B.X > maxEdge.X && C.X > maxEdge.X) ||
				(A.Y > maxEdge.Y && B.Y > maxEdge.Y && C.Y > maxEdge.Y) ||
				(A.Z > maxEdge.Z && B.Z > maxEdge.Z && C.Z > maxEdge.Z) ||
				(A.X < minEdge.X && B.X < minEdge.X && C.X < minEdge.X) ||
				(A.Y < minEdge.Y && B.Y < minEdge.Y && C.Y < minEdge.Y) ||
				(A.Z < minEdge.Z && B.Z < minEdge.Z && C.Z < minEdge.Z));
	}

	bool IsFrontFacing(Vector3Df lookDirection)
	{
		Vector3Df n = Normal.Normalize();
		float d = (float)n.DotProduct(lookDirection);
		return F32_LOWER_EQUAL_0(d);
	}

	bool IsPointInside(Vector3Df point)
	{
		Vector3Dd af64((f64)A.X, (f64)A.Y, (f64)A.Z);
		Vector3Dd bf64((f64)B.X, (f64)B.Y, (f64)B.Z);
		Vector3Dd cf64((f64)C.X, (f64)C.Y, (f64)C.Z);
		Vector3Dd pf64((f64)point.X, (f64)point.Y, (f64)point.Z);
		return (isOnSameSide(pf64, af64, bf64, cf64) &&
			isOnSameSide(pf64, bf64, af64, cf64) &&
			isOnSameSide(pf64, cf64, af64, bf64));
	}

	bool IsPointInsideFast(Vector3Df point)
	{
		Vector3Df a = C - A;
		Vector3Df b = B - A;
		Vector3Df c = point - A;

		const f64 dotAA = a.DotProduct( a);
		const f64 dotAB = a.DotProduct( b);
		const f64 dotAC = a.DotProduct( c);
		const f64 dotBB = b.DotProduct( b);
		const f64 dotBC = b.DotProduct( c);

		// get coordinates in barycentric coordinate system
		const f64 invDenom =  1/(dotAA * dotBB - dotAB * dotAB);
		const f64 u = (dotBB * dotAC - dotAB * dotBC) * invDenom;
		const f64 v = (dotAA * dotBC - dotAB * dotAC ) * invDenom;

		// We count border-points as inside to keep downward compatibility.
		// Rounding-error also needed for some test-cases.
		return (u > -ROUNDING_ERROR_f32) && (v >= 0) && (u + v < 1+ROUNDING_ERROR_f32);
	}

	bool GetIntersectionWithLine(Vector3Df linePoint, Vector3Df lineVect, [Out] Vector3Df% intersection)
	{
		if (GetIntersectionOfPlaneWithLine(linePoint, lineVect, intersection))
			return IsPointInside(intersection);
		return false;
	}

	bool GetIntersectionWithLimitedLine(Line3Df line, [Out] Vector3Df% intersection)
	{
		return GetIntersectionWithLine(line.Start,
			line.Vector, intersection) &&
			intersection.IsBetweenPoints(line.Start, line.End);
	}

	bool GetIntersectionOfPlaneWithLine(Vector3Df linePoint, Vector3Df lineVect, [Out] Vector3Df% intersection)
	{
		//!!! We don't have Triangle3Dd, so we use native classes here to guarantee high precision !!!

		// Work with f64 to get more precise results (makes enough difference to be worth the casts).
		const core::vector3d<f64> linePointf64(linePoint.X, linePoint.Y, linePoint.Z);
		const core::vector3d<f64> lineVectf64(lineVect.X, lineVect.Y, lineVect.Z);
		core::vector3d<f64> outIntersectionf64;

		core::triangle3d<irr::f64> trianglef64(core::vector3d<f64>((f64)A.X, (f64)A.Y, (f64)A.Z)
									,core::vector3d<f64>((f64)B.X, (f64)B.Y, (f64)B.Z)
									, core::vector3d<f64>((f64)C.X, (f64)C.Y, (f64)C.Z));
		const core::vector3d<irr::f64> normalf64 = trianglef64.getNormal().normalize();
		f64 t2;

		if ( core::iszero ( t2 = normalf64.dotProduct(lineVectf64) ) )
			return false;

		f64 d = trianglef64.pointA.dotProduct(normalf64);
		f64 t = -(normalf64.dotProduct(linePointf64) - d) / t2;
		outIntersectionf64 = linePointf64 + (lineVectf64 * t);

		intersection.X = (float)outIntersectionf64.X;
		intersection.Y = (float)outIntersectionf64.Y;
		intersection.Z = (float)outIntersectionf64.Z;
		return true;
	}

	property Plane3Df^ Plane
	{
		Plane3Df^ get() { return gcnew Plane3Df(A, B, C); }
	}

	property float Area
	{
		float get() { return (B - A).CrossProduct(C - A).Length * 0.5f; }
	}

	property Vector3Df Normal
	{
		Vector3Df get() { return (B - A).CrossProduct(C - A); }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) - ({1}) - ({2})", A, B, C);
	}

internal:

	Triangle3Df(const core::triangle3df& value)
	{
		A = Vector3Df(value.pointA);
		B = Vector3Df(value.pointB);
		C = Vector3Df(value.pointC);
	}

	operator core::triangle3df()
	{
		return core::triangle3df(A.ToNative(), B.ToNative(), C.ToNative());
	}

	core::triangle3df ToNative()
	{
		return (core::triangle3df)*this;
	}

private:

	bool isOnSameSide(Vector3Dd p1, Vector3Dd p2,
			Vector3Dd a, Vector3Dd b)
	{
		Vector3Dd bminusa = b - a;
		Vector3Dd cp1 = bminusa.CrossProduct(p1 - a);
		Vector3Dd cp2 = bminusa.CrossProduct(p2 - a);
		f64 res = cp1.DotProduct(cp2);
		if ( res < 0 )
		{
			// This catches some floating point troubles.
			// Unfortunately slightly expensive and we don't really know the best epsilon for iszero.
			Vector3Dd cp1 = bminusa.Normalize().CrossProduct((p1 - a).Normalize());
			if (core::iszero(cp1.X, (f64)ROUNDING_ERROR_f32)
				&& core::iszero(cp1.Y, (f64)ROUNDING_ERROR_f32)
				&& core::iszero(cp1.Z, (f64)ROUNDING_ERROR_f32) )
			{
				res = 0.f;
			}
		}
		return (res >= 0.0f);
	}

};

} // end namespace Core
} // end namespace IrrlichtLime