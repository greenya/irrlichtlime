#pragma once

#include "stdafx.h"
#include "irrMath.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Quaternion : public IEquatable<Quaternion>
{
public:

	float X;
	float Y;
	float Z;
	float W;

	static property Quaternion^ Identity { Quaternion^ get() { return gcnew Quaternion(0, 0, 0, 1); } }

	
	static bool operator == (Quaternion v1, Quaternion v2)
	{
		return v1.Equals(v2);
	}

	virtual bool Equals(Quaternion other) sealed
	{
		return core::equals(X, other.X, ROUNDING_ERROR_f32) &&
			core::equals(Y, other.Y, ROUNDING_ERROR_f32) &&
			core::equals(Z, other.Z, ROUNDING_ERROR_f32) &&
			core::equals(W, other.W, ROUNDING_ERROR_f32);
	}

	bool Equals(Quaternion other, float tolerance)
	{
		return core::equals(X, other.X, tolerance) &&
			core::equals(Y, other.Y, tolerance) &&
			core::equals(Z, other.Z, tolerance) &&
			core::equals(W, other.W, tolerance);
	}

	virtual bool Equals(Object^ other) override sealed
	{
		if (other == nullptr)
			return false;

		if (other->GetType() == Quaternion::typeid)
			return Equals((Quaternion)other);
		else
			return false;
	}

	static Quaternion operator + (Quaternion q1, Quaternion q2)
	{
		return Quaternion(q1.X + q2.X, q1.Y + q2.Y, q1.Z + q2.Z, q1.W + q2.W);
	}

	static Quaternion operator * (Quaternion q1, Quaternion q2)
	{
		Quaternion tmp;

		tmp.W = (q2.W * q1.W) - (q2.X * q1.X) - (q2.Y * q1.Y) - (q2.Z * q1.Z);
		tmp.X = (q2.W * q1.X) + (q2.X * q1.W) + (q2.Y * q1.Z) - (q2.Z * q1.Y);
		tmp.Y = (q2.W * q1.Y) + (q2.Y * q1.W) + (q2.Z * q1.X) - (q2.X * q1.Z);
		tmp.Z = (q2.W * q1.Z) + (q2.Z * q1.W) + (q2.X * q1.Y) - (q2.Y * q1.X);

		return tmp;
	}

	static Vector3Df operator * (Quaternion q, Vector3Df v)
	{
		// nVidia SDK implementation

		Vector3Df uv, uuv;
		Vector3Df qvec(q.X, q.Y, q.Z);
		uv = qvec.CrossProduct(v);
		uuv = qvec.CrossProduct(uv);
		uv *= (2.0f * q.W);
		uuv *= 2.0f;

		return v + uv + uuv;
	}

	static Quaternion operator * (Quaternion q, float a)
	{
		return Quaternion(a * q.X, a * q.Y, a * q.Z, a * q.W);
	}

	Quaternion(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w)
	{
	}

	Quaternion(Matrix^ mat)
	{
		LIME_ASSERT(mat != nullptr);
		Set(mat);
	}

	Quaternion(Vector3Df eulerAngles)
	{
		Set(eulerAngles);
	}

	Quaternion(float eulerAngleX, float eulerAngleY, float eulerAngleZ)
	{
		Set(eulerAngleX, eulerAngleY, eulerAngleZ);
	}

	void Set(Quaternion newQuat)
	{
		*this = newQuat;
	}

	void Set(float newX, float newY, float newZ, float newW)
	{
		X = newX;
		Y = newY;
		Z = newZ;
		W = newW;
	}

	void Set(Matrix^ mat)
	{
		LIME_ASSERT(mat != nullptr);
		const core::matrix4& m = *(mat->m_NativeValue);

		const f32 diag = m[0] + m[5] + m[10] + 1;

		if( diag > 0.0f )
		{
			const f32 scale = sqrtf(diag) * 2.0f; // get scale from diagonal

			// TODO: speed this up
			X = (m[6] - m[9]) / scale;
			Y = (m[8] - m[2]) / scale;
			Z = (m[1] - m[4]) / scale;
			W = 0.25f * scale;
		}
		else
		{
			if (m[0]>m[5] && m[0]>m[10])
			{
				// 1st element of diag is greatest value
				// find scale according to 1st element, and double it
				const f32 scale = sqrtf(1.0f + m[0] - m[5] - m[10]) * 2.0f;

				// TODO: speed this up
				X = 0.25f * scale;
				Y = (m[4] + m[1]) / scale;
				Z = (m[2] + m[8]) / scale;
				W = (m[6] - m[9]) / scale;
			}
			else if (m[5]>m[10])
			{
				// 2nd element of diag is greatest value
				// find scale according to 2nd element, and double it
				const f32 scale = sqrtf(1.0f + m[5] - m[0] - m[10]) * 2.0f;

				// TODO: speed this up
				X = (m[4] + m[1]) / scale;
				Y = 0.25f * scale;
				Z = (m[9] + m[6]) / scale;
				W = (m[8] - m[2]) / scale;
			}
			else
			{
				// 3rd element of diag is greatest value
				// find scale according to 3rd element, and double it
				const f32 scale = sqrtf(1.0f + m[10] - m[0] - m[5]) * 2.0f;

				// TODO: speed this up
				X = (m[8] + m[2]) / scale;
				Y = (m[9] + m[6]) / scale;
				Z = 0.25f * scale;
				W = (m[1] - m[4]) / scale;	
			}
		}
		Normalize();
	}

	void Set(Vector3Df eulerAngles)
	{
		Set(eulerAngles.X, eulerAngles.Y, eulerAngles.Z);
	}

	void Set(float eulerAngleX, float eulerAngleY, float eulerAngleZ)
	{
		f64 angle;

		angle = eulerAngleX * 0.5;
		const f64 sr = sin(angle);
		const f64 cr = cos(angle);

		angle = eulerAngleY * 0.5;
		const f64 sp = sin(angle);
		const f64 cp = cos(angle);

		angle = eulerAngleZ * 0.5;
		const f64 sy = sin(angle);
		const f64 cy = cos(angle);

		const f64 cpcy = cp * cy;
		const f64 spcy = sp * cy;
		const f64 cpsy = cp * sy;
		const f64 spsy = sp * sy;

		X = (f32)(sr * cpcy - cr * spsy);
		Y = (f32)(cr * spcy + sr * cpsy);
		Z = (f32)(cr * cpsy - sr * spcy);
		W = (f32)(cr * cpcy + sr * spsy);

		Normalize();
	}

	float DotProduct(Quaternion other)
	{
		return (X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W);
	}

	Matrix^ GetMatrix()
	{
		Matrix^ m = gcnew Matrix();
		GetMatrix(m, Vector3Df());
		return m;
	}

	Matrix^ GetMatrix(Vector3Df center)
	{
		Matrix^ m = gcnew Matrix();
		GetMatrix(m, center);
		return m;
	}

	Matrix^ GetMatrixCenter(Vector3Df center, Vector3Df translation)
	{
		Matrix^ m = gcnew Matrix();
		GetMatrixCenter(m, center, translation);
		return m;
	}

	Matrix^ GetMatrixTransposed()
	{
		Matrix^ m = gcnew Matrix();
		GetMatrixTransposed(m);
		return m;
	}

	void GetMatrix(Matrix^ m)
	{
		GetMatrix(m, Vector3Df());
	}

	void GetMatrix(Matrix^ m, Vector3Df center)
	{
		LIME_ASSERT(m != nullptr);
		core::matrix4& dest = *(m->m_NativeValue);

		dest[0] = 1.0f - 2.0f*Y*Y - 2.0f*Z*Z;
		dest[1] = 2.0f*X*Y + 2.0f*Z*W;
		dest[2] = 2.0f*X*Z - 2.0f*Y*W;
		dest[3] = 0.0f;

		dest[4] = 2.0f*X*Y - 2.0f*Z*W;
		dest[5] = 1.0f - 2.0f*X*X - 2.0f*Z*Z;
		dest[6] = 2.0f*Z*Y + 2.0f*X*W;
		dest[7] = 0.0f;

		dest[8] = 2.0f*X*Z + 2.0f*Y*W;
		dest[9] = 2.0f*Z*Y - 2.0f*X*W;
		dest[10] = 1.0f - 2.0f*X*X - 2.0f*Y*Y;
		dest[11] = 0.0f;

		dest[12] = center.X;
		dest[13] = center.Y;
		dest[14] = center.Z;
		dest[15] = 1.f;

		dest.setDefinitelyIdentityMatrix ( false );
	}

	void GetMatrixCenter(Matrix^ m, Vector3Df center, Vector3Df translation)
	{
		LIME_ASSERT(m != nullptr);
		core::matrix4& dest = *(m->m_NativeValue);

		dest[0] = 1.0f - 2.0f*Y*Y - 2.0f*Z*Z;
		dest[1] = 2.0f*X*Y + 2.0f*Z*W;
		dest[2] = 2.0f*X*Z - 2.0f*Y*W;
		dest[3] = 0.0f;

		dest[4] = 2.0f*X*Y - 2.0f*Z*W;
		dest[5] = 1.0f - 2.0f*X*X - 2.0f*Z*Z;
		dest[6] = 2.0f*Z*Y + 2.0f*X*W;
		dest[7] = 0.0f;

		dest[8] = 2.0f*X*Z + 2.0f*Y*W;
		dest[9] = 2.0f*Z*Y - 2.0f*X*W;
		dest[10] = 1.0f - 2.0f*X*X - 2.0f*Y*Y;
		dest[11] = 0.0f;

		dest.setRotationCenter ( center, translation );
	}

	void GetMatrixTransposed(Matrix^ m)
	{
		LIME_ASSERT(m != nullptr);
		core::matrix4& dest = *(m->m_NativeValue);

		dest[0] = 1.0f - 2.0f*Y*Y - 2.0f*Z*Z;
		dest[4] = 2.0f*X*Y + 2.0f*Z*W;
		dest[8] = 2.0f*X*Z - 2.0f*Y*W;
		dest[12] = 0.0f;

		dest[1] = 2.0f*X*Y - 2.0f*Z*W;
		dest[5] = 1.0f - 2.0f*X*X - 2.0f*Z*Z;
		dest[9] = 2.0f*Z*Y + 2.0f*X*W;
		dest[13] = 0.0f;

		dest[2] = 2.0f*X*Z + 2.0f*Y*W;
		dest[6] = 2.0f*Z*Y - 2.0f*X*W;
		dest[10] = 1.0f - 2.0f*X*X - 2.0f*Y*Y;
		dest[14] = 0.0f;

		dest[3] = 0.f;
		dest[7] = 0.f;
		dest[11] = 0.f;
		dest[15] = 1.f;

		dest.setDefinitelyIdentityMatrix(false);
	}

	Quaternion Lerp(Quaternion other, float time)
	{
		const f32 scale = 1.0f - time;
		return (*this = (*this*scale) + (other*time));
	}

	static Quaternion Lerp(Quaternion q1, Quaternion q2, float time)
	{
		return q1.Lerp(q2, time);	//q1 is already a copy, so we can override it
	}

	Quaternion MakeIdentity()
	{
		W = 1.f;
		X = 0.f;
		Y = 0.f;
		Z = 0.f;
		return *this;
	}

	Quaternion MakeInverse()
	{
		X = -X; Y = -Y; Z = -Z;
		return *this;
	}

	Quaternion MakeRotation(Vector3Df from, Vector3Df to)
	{
		// Based on Stan Melax's article in Game Programming Gems

		from.Normalize();
		to.Normalize();

		const f32 d = from.DotProduct(to);
		if (d >= 1.0f) // If dot == 1, vectors are the same
		{
			return MakeIdentity();
		}
		else if (d <= -1.0f) // exactly opposite
		{
			Vector3Df axis(1.0f, 0.f, 0.f);
			axis = axis.CrossProduct(from);
			if (axis.Length==0)
			{
				axis.Set(0.f,1.f,0.f);
				axis = axis.CrossProduct(from);
			}
			// same as fromAngleAxis(core::PI, axis).normalize();
			Set(axis.X, axis.Y, axis.Z, 0);
			Normalize();
			return *this;
		}

		const f32 s = sqrtf( (1+d)*2 ); // optimize inv_sqrt
		const f32 invs = 1.f / s;
		Vector3Df c = from.CrossProduct(to)*invs;
		Set(c.X, c.Y, c.Z, s * 0.5f);
		Normalize();
		return *this;
	}

	Quaternion MakeRotation(float angle, Vector3Df axis)
	{
		const f32 fHalfAngle = 0.5f*angle;
		const f32 fSin = sinf(fHalfAngle);
		W = cosf(fHalfAngle);
		X = fSin*axis.X;
		Y = fSin*axis.Y;
		Z = fSin*axis.Z;
		return *this;
	}

	Quaternion Normalize()
	{
		const f32 n = X*X + Y*Y + Z*Z + W*W;

		if (n == 1)
			return *this;

		//n = 1.0f / sqrtf(n);
		return (*this *= core::reciprocal_squareroot ( n ));
	}

	Quaternion Slerp(Quaternion other, float time)
	{
		return Slerp(other, time, .05f);
	}

	static Quaternion Slerp(Quaternion q1, Quaternion q2, float time)
	{
		return q1.Slerp(q2, time);	//q1 is already a copy, so we can override it
	}

	Quaternion Slerp(Quaternion other, float time, float threshold)
	{
		f32 angle = DotProduct(other);

		// make sure we use the short rotation
		if (angle < 0.0f)
		{
			*this *= -1.0f;
			angle *= -1.0f;
		}

		if (angle <= (1-threshold)) // spherical interpolation
		{
			const f32 theta = acosf(angle);
			const f32 invsintheta = core::reciprocal(sinf(theta));
			const f32 scale = sinf(theta * (1.0f-time)) * invsintheta;
			const f32 invscale = sinf(theta * time) * invsintheta;
			return (*this = (*this*scale) + (other*invscale));
		}
		else // linear interploation
			return Lerp(other, time);
	}

	static Quaternion Slerp(Quaternion q1, Quaternion q2, float time, float threshold)
	{
		return q1.Slerp(q2, time, threshold);	//q1 is already a copy, so we can override it
	}

	void ToAngleAxis([Out] float% angle, [Out] Vector3Df% axis)
	{
		const f32 scale = sqrtf(X*X + Y*Y + Z*Z);

		if (core::iszero(scale) || W > 1.0f || W < -1.0f)
		{
			angle = 0.0f;
			axis.X = 0.0f;
			axis.Y = 1.0f;
			axis.Z = 0.0f;
		}
		else
		{
			const f32 invscale = core::reciprocal(scale);
			angle = 2.0f * acosf(W);
			axis.X = X * invscale;
			axis.Y = Y * invscale;
			axis.Z = Z * invscale;
		}
	}

	Vector3Df ToEuler()
	{
		Vector3Df euler;

		const f64 sqw = W*W;
		const f64 sqx = X*X;
		const f64 sqy = Y*Y;
		const f64 sqz = Z*Z;
		const f64 test = 2.0 * (Y*W - X*Z);

		if (core::equals(test, 1.0, 0.000001))
		{
			// heading = rotation about z-axis
			euler.Z = (f32) (-2.0*atan2(X, W));
			// bank = rotation about x-axis
			euler.X = 0;
			// attitude = rotation about y-axis
			euler.Y = (f32) (core::PI64/2.0);
		}
		else if (core::equals(test, -1.0, 0.000001))
		{
			// heading = rotation about z-axis
			euler.Z = (f32) (2.0*atan2(X, W));
			// bank = rotation about x-axis
			euler.X = 0;
			// attitude = rotation about y-axis
			euler.Y = (f32) (core::PI64/-2.0);
		}
		else
		{
			// heading = rotation about z-axis
			euler.Z = (f32) atan2(2.0 * (X*Y +Z*W),(sqx - sqy - sqz + sqw));
			// bank = rotation about x-axis
			euler.X = (f32) atan2(2.0 * (Y*Z +X*W),(-sqx - sqy + sqz + sqw));
			// attitude = rotation about y-axis
			euler.Y = (f32) asin( core::clamp(test, -1.0, 1.0) );
		}
		
		return euler;
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) W={1}", Vector3Df(X, Y, Z), W);
	}

internal:

	Quaternion(const core::quaternion& value)
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	operator core::quaternion()
	{
		return core::quaternion(X, Y, Z, W);
	}

	core::quaternion ToNative()
	{
		return (core::quaternion)*this;
	}

};

} // end namespace Core
} // end namespace IrrlichtLime