#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix : Lime::NativeValue<core::matrix4>
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

	void BuildAxisAlignedBillboard(Vector3Df^ camPos, Vector3Df^ center, Vector3Df^ translation, Vector3Df^ axis, Vector3Df^ from)
	{
		LIME_ASSERT(camPos != nullptr);
		LIME_ASSERT(center != nullptr);
		LIME_ASSERT(translation != nullptr);
		LIME_ASSERT(axis != nullptr);
		LIME_ASSERT(from != nullptr);

		m_NativeValue->buildAxisAlignedBillboard(
			*camPos->m_NativeValue,
			*center->m_NativeValue,
			*translation->m_NativeValue,
			*axis->m_NativeValue,
			*from->m_NativeValue);
	}

	Matrix^ BuildCameraLookAtMatrixLH(Vector3Df^ position, Vector3Df^ target, Vector3Df^ upVector)
	{
		LIME_ASSERT(position != nullptr);
		LIME_ASSERT(target != nullptr);
		LIME_ASSERT(upVector != nullptr);

		return gcnew Matrix(m_NativeValue->buildCameraLookAtMatrixLH(
			*position->m_NativeValue,
			*target->m_NativeValue,
			*upVector->m_NativeValue));
	}

	Matrix^ BuildCameraLookAtMatrixRH(Vector3Df^ position, Vector3Df^ target, Vector3Df^ upVector)
	{
		LIME_ASSERT(position != nullptr);
		LIME_ASSERT(target != nullptr);
		LIME_ASSERT(upVector != nullptr);

		return gcnew Matrix(m_NativeValue->buildCameraLookAtMatrixRH(
			*position->m_NativeValue,
			*target->m_NativeValue,
			*upVector->m_NativeValue));
	}

	Matrix^ BuildNDCToDCMatrix(Recti^ area, float zScale)
	{
		LIME_ASSERT(area != nullptr);

		return gcnew Matrix(m_NativeValue->buildNDCToDCMatrix(
			*area->m_NativeValue,
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

	Matrix^ BuildRotateFromTo(Vector3Df^ from, Vector3Df^ to)
	{
		LIME_ASSERT(from != nullptr);
		LIME_ASSERT(to != nullptr);

		return gcnew Matrix(m_NativeValue->buildRotateFromTo(
			*from->m_NativeValue,
			*to->m_NativeValue));
	}

	Matrix^ BuildShadowMatrix(Vector3Df^ light, Plane3Df^ plane, float point)
	{
		LIME_ASSERT(light != nullptr);
		LIME_ASSERT(plane != nullptr);
		LIME_ASSERT(point >= 0.0f && point <= 1.0f);

		return gcnew Matrix(m_NativeValue->buildShadowMatrix(
			*light->m_NativeValue,
			*plane->m_NativeValue,
			point));
	}

	Matrix^ BuildShadowMatrix(Vector3Df^ light, Plane3Df^ plane)
	{
		LIME_ASSERT(light != nullptr);
		LIME_ASSERT(plane != nullptr);

		return gcnew Matrix(m_NativeValue->buildShadowMatrix(
			*light->m_NativeValue,
			*plane->m_NativeValue));
	}

	Matrix^ BuildTextureTransform(float rotateRad, Vector2Df^ rotateCenter, Vector2Df^ translate, Vector2Df^ scale)
	{
		LIME_ASSERT(rotateCenter != nullptr);
		LIME_ASSERT(translate != nullptr);
		LIME_ASSERT(scale != nullptr);

		return gcnew Matrix(m_NativeValue->buildTextureTransform(
			rotateRad,
			*rotateCenter->m_NativeValue,
			*translate->m_NativeValue,
			*scale->m_NativeValue));
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

	void InverseRotateVector(Vector3Df^% vect)
	{
		LIME_ASSERT(vect != nullptr);
		m_NativeValue->inverseRotateVect(*vect->m_NativeValue);
	}

	void InverseTranslateVector(Vector3Df^% vect)
	{
		LIME_ASSERT(vect != nullptr);
		m_NativeValue->inverseTranslateVect(*vect->m_NativeValue);
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

	void MultiplyWith1x4Matrix(array<float>^ m1x4)
	{
		LIME_ASSERT(m1x4 != nullptr);
		LIME_ASSERT(m1x4->Length == 4);

		float f[4] = { m1x4[0], m1x4[1], m1x4[2], m1x4[3] };
		m_NativeValue->multiplyWith1x4Matrix(f);
	}

	Vector3Df^ RotateVector(Vector3Df^ vect)
	{
		LIME_ASSERT(vect != nullptr);

		core::vector3df v;
		m_NativeValue->rotateVect(v, *vect->m_NativeValue);
		return gcnew Vector3Df(v);
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

	Matrix^ SetInverseRotationDegrees(Vector3Df^ rotation)
	{
		LIME_ASSERT(rotation != nullptr);

		m_NativeValue->setInverseRotationDegrees(*rotation->m_NativeValue);
		return this;
	}

	Matrix^ SetInverseRotationRadians(Vector3Df^ rotation)
	{
		LIME_ASSERT(rotation != nullptr);

		m_NativeValue->setInverseRotationRadians(*rotation->m_NativeValue);
		return this;
	}

	Matrix^ SetInverseTranslation(Vector3Df^ translation)
	{
		LIME_ASSERT(translation != nullptr);

		m_NativeValue->setInverseTranslation(*translation->m_NativeValue);
		return this;
	}

	void SetRotationCenter(Vector3Df^ center, Vector3Df^ translate)
	{
		LIME_ASSERT(center != nullptr);
		LIME_ASSERT(translate != nullptr);

		m_NativeValue->setRotationCenter(
			*center->m_NativeValue,
			*translate->m_NativeValue);
	}

	Matrix^ SetRotationRadians(Vector3Df^ rotation)
	{
		LIME_ASSERT(rotation != nullptr);

		m_NativeValue->setRotationRadians(*rotation->m_NativeValue);
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

	void TransformVector(Vector3Df^% vect)
	{
		LIME_ASSERT(vect != nullptr);
		m_NativeValue->transformVect(*vect->m_NativeValue);
	}

	void TranslateVector(Vector3Df^% vect)
	{
		LIME_ASSERT(vect != nullptr);
		m_NativeValue->translateVect(*vect->m_NativeValue);
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

	property Vector3Df^ Rotation
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getRotationDegrees()); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->setRotationDegrees(*value->m_NativeValue); }
	}

	property Vector3Df^ Scale
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getScale()); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->setScale(*value->m_NativeValue); }
	}

	property Vector3Df^ Translation
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getTranslation()); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->setTranslation(*value->m_NativeValue); }
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