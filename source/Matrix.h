#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix4f : Lime::NativeValue<core::matrix4>
{
public:

	Matrix4f()
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4();
	}

internal:

	Matrix4f(const core::matrix4& other)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4(other);
	}

	Matrix4f(core::matrix4* ref)
		: Lime::NativeValue<core::matrix4>(false)
	{
		LIME_ASSERT(ref != nullptr);
		m_NativeValue = ref;
	}
};

} // end namespace Core
} // end namespace IrrlichtLime