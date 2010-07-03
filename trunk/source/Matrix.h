#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix : Lime::NativeValue<core::matrix4>
{
public:

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

	Matrix()
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
	}

	property Vector3Df^ Scale
	{
		Vector3Df^ get() { return gcnew Vector3Df(m_NativeValue->getScale()); }
		void set(Vector3Df^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->setScale(*value->m_NativeValue); }
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