#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix : Lime::NativeValue<core::matrix4>
{
public:

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