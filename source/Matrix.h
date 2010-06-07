#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix4f : Lime::NativeValue<core::matrix4>
{
public:

internal:

	Matrix4f(const core::matrix4& other)
		: Lime::NativeValue<core::matrix4>(true)
	{
		m_NativeValue = new core::matrix4(other);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime