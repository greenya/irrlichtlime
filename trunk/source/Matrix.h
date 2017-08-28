#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix : Lime::NativeValue<core::matrix4>, public Video::IShaderConstant
{
public:

	static property Matrix^ Identity { Matrix^ get() { return gcnew Matrix(core::matrix4(core::matrix4::EM4CONST_IDENTITY)); } }

	static bool operator == (Matrix^ v1, Matrix^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (Matrix^ v1, Matrix^ v2)
	{
		return !(v1 == v2);
	}

	static Matrix^ operator + (Matrix^ v1, Matrix^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew Matrix((*v1->m_NativeValue) + (*v2->m_NativeValue));
	}

	static Matrix^ operator - (Matrix^ v1, Matrix^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew Matrix((*v1->m_NativeValue) - (*v2->m_NativeValue));
	}

	static Matrix^ operator * (Matrix^ v1, float v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew Matrix((*v1->m_NativeValue) * v2);
	}

	static Matrix^ operator * (Matrix^ v1, Matrix^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew Matrix((*v1->m_NativeValue) * (*v2->m_NativeValue));
	}

	Matrix()
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
	}

	Matrix(Matrix^ copy)
		: Lime::NativeValue<core::matrix4>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new core::matrix4(*copy->m_NativeValue);
	}

	Matrix(
		float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4(
			r0c0, r0c1, r0c2, r0c3,
			r1c0, r1c1, r1c2, r1c3,
			r2c0, r2c1, r2c2, r2c3,
			r3c0, r3c1, r3c2, r3c3);
	}

	Matrix(Vector3Df translation, Vector3Df rotation, Vector3Df scale)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
		m_NativeValue->setTranslation(translation);
		m_NativeValue->setRotationDegrees(rotation);
		m_NativeValue->setScale(scale);
	}

	Matrix(Vector3Df translation, Vector3Df rotation)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
		m_NativeValue->setTranslation(translation);
		m_NativeValue->setRotationDegrees(rotation);
	}

	Matrix(Vector3Df translation)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
		m_NativeValue->setTranslation(translation);
	}

	void BuildAxisAlignedBillboard(Vector3Df camPos, Vector3Df center, Vector3Df translation, Vector3Df axis, Vector3Df from)
	{
		m_NativeValue->buildAxisAlignedBillboard(
			camPos,
			center,
			translation,
			axis,
			from);
	}

	Matrix^ BuildCameraLookAtMatrixLH(Vector3Df position, Vector3Df target, Vector3Df upVector)
	{
		return gcnew Matrix(m_NativeValue->buildCameraLookAtMatrixLH(
			position,
			target,
			upVector));
	}

	Matrix^ BuildCameraLookAtMatrixRH(Vector3Df position, Vector3Df target, Vector3Df upVector)
	{
		return gcnew Matrix(m_NativeValue->buildCameraLookAtMatrixRH(
			position,
			target,
			upVector));
	}

	Matrix^ BuildNDCToDCMatrix(Recti area, float zScale)
	{
		return gcnew Matrix(m_NativeValue->buildNDCToDCMatrix(
			area,
			zScale));
	}

	Matrix^ BuildProjectionMatrixOrthoLH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixOrthoLH(
			widthOfViewVolume, heightOfViewVolume, zNear, zFar));
	}

	Matrix^ BuildProjectionMatrixOrthoRH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixOrthoRH(
			widthOfViewVolume, heightOfViewVolume, zNear, zFar));
	}

	Matrix^ BuildProjectionMatrixPerspectiveFovLH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixPerspectiveFovLH(
			fieldOfViewRadians, aspectRatio, zNear, zFar));
	}

	Matrix^ BuildProjectionMatrixPerspectiveFovRH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixPerspectiveFovRH(
			fieldOfViewRadians, aspectRatio, zNear, zFar));
	}

	Matrix^ BuildProjectionMatrixPerspectiveLH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixPerspectiveLH(
			widthOfViewVolume, heightOfViewVolume, zNear, zFar));
	}

	Matrix^ BuildProjectionMatrixPerspectiveRH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		return gcnew Matrix(m_NativeValue->buildProjectionMatrixPerspectiveRH(
			widthOfViewVolume, heightOfViewVolume, zNear, zFar));
	}

	Matrix^ BuildRotateFromTo(Vector3Df from, Vector3Df to)
	{
		return gcnew Matrix(m_NativeValue->buildRotateFromTo(
			from,
			to));
	}

	Matrix^ BuildShadowMatrix(Vector3Df light, Plane3Df^ plane, float point)
	{
		LIME_ASSERT(plane != nullptr);
		LIME_ASSERT(point >= 0.0f && point <= 1.0f);

		return gcnew Matrix(m_NativeValue->buildShadowMatrix(
			light,
			*plane->m_NativeValue,
			point));
	}

	Matrix^ BuildShadowMatrix(Vector3Df light, Plane3Df^ plane)
	{
		LIME_ASSERT(plane != nullptr);

		return gcnew Matrix(m_NativeValue->buildShadowMatrix(
			light,
			*plane->m_NativeValue));
	}

	Matrix^ BuildTextureTransform(float rotateRad, Vector2Df rotateCenter, Vector2Df translate, Vector2Df scale)
	{
		return gcnew Matrix(m_NativeValue->buildTextureTransform(
			rotateRad,
			rotateCenter,
			translate,
			scale));
	}

	float GetElement(int row, int column)
	{
		LIME_ASSERT(row >= 0 && row <= 3);
		LIME_ASSERT(column >= 0 && column <= 3);

		return (*m_NativeValue)(row, column);
	}

	float GetElement(int index)
	{
		LIME_ASSERT(index >= 0 && index <= 15);
		return (*m_NativeValue)[index];
	}

	Matrix^ GetInterpolated(Matrix^ other, float time)
	{
		LIME_ASSERT(other != nullptr);
		LIME_ASSERT(time >= 0.0f && time <= 1.0f);

		return gcnew Matrix(m_NativeValue->interpolate(
			*other->m_NativeValue,
			time));
	}

	Matrix^ GetInverse()
	{
		core::matrix4 m;
		if (m_NativeValue->getInverse(m))
			return gcnew Matrix(m);

		return nullptr;
	}

	Matrix^ GetInversePrimitive()
	{
		core::matrix4 m;
		if (m_NativeValue->getInversePrimitive(m))
			return gcnew Matrix(m);

		return nullptr;
	}

	Vector3Df GetRotationDegrees(Vector3Df scale)
	{
		return Vector3Df(m_NativeValue->getRotationDegrees(scale));
	}

	void GetTextureScale([Out] float% sx, [Out] float% sy)
	{
		float sx_;
		float sy_;
		m_NativeValue->getTextureScale(sx_, sy_);
		sx = sx_;
		sy = sy_;
	}

	void GetTextureTranslate([Out] float% x, [Out] float% y)
	{
		float x_;
		float y_;
		m_NativeValue->getTextureTranslate(x_, y_);
		x = x_;
		y = y_;
	}

	void InverseRotateVector(Vector3Df% vect)
	{
		core::vector3df v = vect.ToNative();
		m_NativeValue->inverseRotateVect(v);
		vect = Vector3Df(v);
	}

	void InverseTranslateVector(Vector3Df% vect)
	{
		core::vector3df v = vect.ToNative();
		m_NativeValue->inverseTranslateVect(v);
		vect = Vector3Df(v);
	}

	Matrix^ MakeIdentity()
	{
		m_NativeValue->makeIdentity();
		return this;
	}

	Matrix^ MakeInverse()
	{
		bool b = m_NativeValue->makeInverse();
		return b ? this : nullptr;
	}

	void MultiplyWith1x4Matrix(array<float>^% m1x4)
	{
		LIME_ASSERT(m1x4 != nullptr);
		LIME_ASSERT(m1x4->Length == 4);

		float f[4] = { m1x4[0], m1x4[1], m1x4[2], m1x4[3] };
		m_NativeValue->multiplyWith1x4Matrix(f);

		m1x4[0] = f[0];
		m1x4[1] = f[1];
		m1x4[2] = f[2];
		m1x4[3] = f[3];
	}

	Vector3Df RotateVector(Vector3Df vect)
	{
		core::vector3df v;
		m_NativeValue->rotateVect(v, vect);
		return Vector3Df(v);
	}

	Matrix^ SetByProduct(Matrix^ otherA, Matrix^ otherB)
	{
		LIME_ASSERT(otherA != nullptr);
		LIME_ASSERT(otherB != nullptr);

		m_NativeValue->setbyproduct(*otherA->m_NativeValue, *otherB->m_NativeValue);
		return this;
	}

	Matrix^ SetByProductNoCheck(Matrix^ otherA, Matrix^ otherB)
	{
		LIME_ASSERT(otherA != nullptr);
		LIME_ASSERT(otherB != nullptr);

		m_NativeValue->setbyproduct_nocheck(*otherA->m_NativeValue, *otherB->m_NativeValue);
		return this;
	}

	void SetElement(int row, int column, float value)
	{
		LIME_ASSERT(row >= 0 && row <= 3);
		LIME_ASSERT(column >= 0 && column <= 3);

		(*m_NativeValue)(row, column) = value;
	}

	void SetElement(int index, float value)
	{
		LIME_ASSERT(index >= 0 && index <= 15);
		(*m_NativeValue)[index] = value;
	}

	void SetElementArray(array<float>^ values)
	{
		LIME_ASSERT(values != nullptr);
		LIME_ASSERT(values->Length == 16);

		float p[16];

		for (int i = 0; i < 16; i++)
			p[i] = values[i];

		m_NativeValue->setM(p);
	}

	Matrix^ SetInverseRotationDegrees(Vector3Df rotation)
	{
		m_NativeValue->setInverseRotationDegrees(rotation);
		return this;
	}

	Matrix^ SetInverseRotationRadians(Vector3Df rotation)
	{
		m_NativeValue->setInverseRotationRadians(rotation);
		return this;
	}

	Matrix^ SetInverseTranslation(Vector3Df translation)
	{
		m_NativeValue->setInverseTranslation(translation);
		return this;
	}

	void SetRotationCenter(Vector3Df center, Vector3Df translate)
	{
		m_NativeValue->setRotationCenter(
			center,
			translate);
	}

	Matrix^ SetRotationRadians(Vector3Df rotation)
	{
		m_NativeValue->setRotationRadians(rotation);
		return this;
	}

	Matrix^ SetRotationAxisRadians(float angle, Vector3Df axis)
	{
		m_NativeValue->setRotationAxisRadians(angle, axis);
		return this;
	}

	Matrix^ SetTextureRotationCenter(float radAngle)
	{
		m_NativeValue->setTextureRotationCenter(radAngle);
		return this;
	}

	Matrix^ SetTextureScale(float sx, float sy)
	{
		m_NativeValue->setTextureScale(sx, sy);
		return this;
	}

	Matrix^ SetTextureScaleCenter(float sx, float sy)
	{
		m_NativeValue->setTextureScaleCenter(sx, sy);
		return this;
	}

	Matrix^ SetTextureTranslate(float x, float y)
	{
		m_NativeValue->setTextureTranslate(x, y);
		return this;
	}

	Matrix^ SetTextureTranslateTransposed(float x, float y)
	{
		m_NativeValue->setTextureTranslateTransposed(x, y);
		return this;
	}

	array<float>^ ToArray()
	{
		array<float>^ m = gcnew array<float>(16);
		float* p = m_NativeValue->pointer();

		for (int i = 0; i < 16; i++)
			m[i] = p[i];

		return m;
	}

	[Obsolete("Very inaccurate. Use TransformBoxEx instead.", false)]
	void TransformBox(AABBox^% box)
	{
		LIME_ASSERT(box != nullptr);
		m_NativeValue->transformBox(*box->m_NativeValue);
	}

	void TransformBoxEx(AABBox^% box)
	{
		LIME_ASSERT(box != nullptr);
		m_NativeValue->transformBoxEx(*box->m_NativeValue);
	}

	void TransformPlane(Plane3Df^% plane)
	{
		LIME_ASSERT(plane != nullptr);
		m_NativeValue->transformPlane(*plane->m_NativeValue);
	}

	void TransformVector(Vector3Df% vect)
	{
		core::vector3df v = vect.ToNative();
		m_NativeValue->transformVect(v);
		vect = Vector3Df(v);
	}

	void TranslateVector(Vector3Df% vect)
	{
		core::vector3df v = vect.ToNative();
		m_NativeValue->translateVect(v);
		vect = Vector3Df(v);
	}

	virtual int GetData(float* data) sealed
	{
		float* p = m_NativeValue->pointer();
		data[0] =	p[0];
		data[1] =	p[1];
		data[2] =	p[2];
		data[3] =	p[3];
		data[4] =	p[4];
		data[5] =	p[5];
		data[6] =	p[6];
		data[7] =	p[7];
		data[8] =	p[8];
		data[9] =	p[9];
		data[10] =	p[10];
		data[11] =	p[11];
		data[12] =	p[12];
		data[13] =	p[13];
		data[14] =	p[14];
		data[15] =	p[15];
		return 16;
	}

	property bool DefinitelyIdentity
	{
		bool get() { return m_NativeValue->getDefinitelyIdentityMatrix(); }
		void set(bool value) { m_NativeValue->setDefinitelyIdentityMatrix(value); }
	}

	property bool IdentityIntegerBase
	{
		bool get() { return m_NativeValue->isIdentity_integer_base(); }
	}

	property bool Orthogonal
	{
		bool get() { return m_NativeValue->isOrthogonal(); }
	}

	property Vector3Df Rotation
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getRotationDegrees()); }
		void set(Vector3Df value) { m_NativeValue->setRotationDegrees(value); }
	}

	property Vector3Df Scale
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getScale()); }
		void set(Vector3Df value) { m_NativeValue->setScale(value); }
	}

	property Vector3Df Translation
	{
		Vector3Df get() { return Vector3Df(m_NativeValue->getTranslation()); }
		void set(Vector3Df value) { m_NativeValue->setTranslation(value); }
	}

	property Matrix^ Transposed
	{
		Matrix^ get() { return gcnew Matrix(m_NativeValue->getTransposed()); }
	}

internal:

	Matrix(const core::matrix4& other)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4(other);
	}

	Matrix(core::matrix4* ref)
		: Lime::NativeValue<core::matrix4>(false)
	{
		LIME_ASSERT(ref != nullptr);
		m_NativeValue = ref;
	}
};

} // end namespace Core
} // end namespace IrrlichtLime