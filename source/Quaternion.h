#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Quaternion : Lime::NativeValue<core::quaternion>
{
public:

	static property Quaternion^ Identity { Quaternion^ get() { return gcnew Quaternion(); } }

	static bool operator == (Quaternion^ q1, Quaternion^ q2)
	{
		bool q1n = Object::ReferenceEquals(q1, nullptr);
		bool q2n = Object::ReferenceEquals(q2, nullptr);

		if (q1n && q2n)
			return true;

		if (q1n || q2n)
			return false;

		return (*q1->m_NativeValue) == (*q2->m_NativeValue);
	}

	static bool operator != (Quaternion^ q1, Quaternion^ q2)
	{
		return !(q1 == q2);
	}

	static Quaternion^ operator + (Quaternion^ q1, Quaternion^ q2)
	{
		LIME_ASSERT(q1 != nullptr);
		LIME_ASSERT(q2 != nullptr);

		return gcnew Quaternion((*q1->m_NativeValue) + (*q2->m_NativeValue));
	}

	static Quaternion^ operator * (Quaternion^ q1, Quaternion^ q2)
	{
		LIME_ASSERT(q1 != nullptr);
		LIME_ASSERT(q2 != nullptr);

		return gcnew Quaternion((*q1->m_NativeValue) * (*q2->m_NativeValue));
	}

	static Quaternion^ operator * (Quaternion^ q, Vector3Df^ v)
	{
		LIME_ASSERT(q != nullptr);
		LIME_ASSERT(v != nullptr);

		return gcnew Quaternion((*q->m_NativeValue) * (*v->m_NativeValue));
	}

	static Quaternion^ operator * (Quaternion^ q, float a)
	{
		LIME_ASSERT(q != nullptr);
		return gcnew Quaternion((*q->m_NativeValue) * a);
	}

	Quaternion()
		: Lime::NativeValue<core::quaternion>(true)
	{
		m_NativeValue = new core::quaternion();
	}

	Quaternion(Quaternion^ copy)
		: Lime::NativeValue<core::quaternion>(true)
	{
		LIME_ASSERT(copy != nullptr);

		m_NativeValue = new core::quaternion();
		m_NativeValue->set(*copy->m_NativeValue);
	}

	Quaternion(float x, float y, float z, float w)
		: Lime::NativeValue<core::quaternion>(true)
	{
		m_NativeValue = new core::quaternion(x, y, z, w);
	}

	Quaternion(Matrix^ mat)
		: Lime::NativeValue<core::quaternion>(true)
	{
		LIME_ASSERT(mat != nullptr);
		m_NativeValue = new core::quaternion(*mat->m_NativeValue);
	}

	Quaternion(Vector3Df^ eulerAngles)
		: Lime::NativeValue<core::quaternion>(true)
	{
		LIME_ASSERT(eulerAngles != nullptr);
		m_NativeValue = new core::quaternion(*eulerAngles->m_NativeValue);
	}

	Quaternion(float eulerAngleX, float eulerAngleY, float eulerAngleZ)
		: Lime::NativeValue<core::quaternion>(true)
	{
		m_NativeValue = new core::quaternion(eulerAngleX, eulerAngleY, eulerAngleZ);
	}

	void Set(Quaternion^ newQuat)
	{
		LIME_ASSERT(newQuat != nullptr);
		m_NativeValue->set(*newQuat->m_NativeValue);
	}

	void Set(Vector3Df^ eulerAngles)
	{
		LIME_ASSERT(eulerAngles != nullptr);
		m_NativeValue->set(*eulerAngles->m_NativeValue);
	}

	void Set(float newX, float newY, float newZ, float newW)
	{
		m_NativeValue->set(newX, newY, newZ, newW);
	}

	void Set(float eulerAngleX, float eulerAngleY, float eulerAngleZ)
	{
		m_NativeValue->set(eulerAngleX, eulerAngleY, eulerAngleZ);
	}

	float DotProduct(Quaternion^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->dotProduct(*other->m_NativeValue);
	}

	bool EqualsTo(Quaternion^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->equals(*other->m_NativeValue);
	}

	Matrix^ GetMatrix()
	{
		return gcnew Matrix(m_NativeValue->getMatrix());
	}

	Matrix^ GetMatrix(Vector3Df^ translation)
	{
		LIME_ASSERT(translation != nullptr);

		Matrix^ m = gcnew Matrix();
		m_NativeValue->getMatrix(*m->m_NativeValue, *translation->m_NativeValue);

		return m;
	}

	Matrix^ GetMatrixCenter(Vector3Df^ center, Vector3Df^ translation)
	{
		LIME_ASSERT(center != nullptr);
		LIME_ASSERT(translation != nullptr);

		Matrix^ m = gcnew Matrix();
		m_NativeValue->getMatrixCenter(*m->m_NativeValue, *center->m_NativeValue, *translation->m_NativeValue);

		return m;
	}

	Quaternion^ Lerp(Quaternion^ q1, Quaternion^ q2, float time)
	{
		LIME_ASSERT(q1 != nullptr);
		LIME_ASSERT(q2 != nullptr);

		m_NativeValue->lerp(*q1->m_NativeValue, *q2->m_NativeValue, time);
		return this;
	}

	Quaternion^ MakeIdentity()
	{
		m_NativeValue->makeIdentity();
		return this;
	}

	Quaternion^ MakeInverse()
	{
		m_NativeValue->makeInverse();
		return this;
	}

	Quaternion^ MakeRotation(Vector3Df^ from, Vector3Df^ to)
	{
		LIME_ASSERT(from != nullptr);
		LIME_ASSERT(to != nullptr);

		m_NativeValue->rotationFromTo(*from->m_NativeValue, *to->m_NativeValue);
		return this;
	}

	Quaternion^ MakeRotation(float angle, Vector3Df^ axis)
	{
		LIME_ASSERT(axis != nullptr);

		m_NativeValue->fromAngleAxis(angle, *axis->m_NativeValue);
		return this;
	}

	Quaternion^ Normalize()
	{
		m_NativeValue->normalize();
		return gcnew Quaternion(*m_NativeValue);
	}

	Quaternion^ Slerp(Quaternion^ q1, Quaternion^ q2, float time)
	{
		LIME_ASSERT(q1 != nullptr);
		LIME_ASSERT(q2 != nullptr);

		m_NativeValue->slerp(*q1->m_NativeValue, *q2->m_NativeValue, time);
		return this;
	}

	Quaternion^ Slerp(Quaternion^ q1, Quaternion^ q2, float time, float threshold)
	{
		LIME_ASSERT(q1 != nullptr);
		LIME_ASSERT(q2 != nullptr);

		m_NativeValue->slerp(*q1->m_NativeValue, *q2->m_NativeValue, time, threshold);
		return this;
	}

	void ToAngleAxis([Out] float% angle, [Out] Vector3Df^% axis)
	{
		LIME_ASSERT(axis != nullptr);

		float a;
		m_NativeValue->toAngleAxis(a, *axis->m_NativeValue);
		angle = a;
	}

	Vector3Df^ ToEuler()
	{
		core::vector3df v;
		m_NativeValue->toEuler(v);

		return gcnew Vector3Df(v);
	}

	property float W
	{
		float get() { return m_NativeValue->W; }
		void set(float value) { m_NativeValue->W = value; }
	}

	property float X
	{
		float get() { return m_NativeValue->X; }
		void set(float value) { m_NativeValue->X = value; }
	}

	property float Y
	{
		float get() { return m_NativeValue->Y; }
		void set(float value) { m_NativeValue->Y = value; }
	}

	property float Z
	{
		float get() { return m_NativeValue->Z; }
		void set(float value) { m_NativeValue->Z = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) W={1}", gcnew Vector3Df(X, Y, Z), W);
	}

internal:

	Quaternion(const core::quaternion& value)
		: Lime::NativeValue<core::quaternion>(true)
	{
		m_NativeValue = new core::quaternion(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime