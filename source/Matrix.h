#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Matrix4f : Lime::NativeValue<core::matrix4, Lime::NativeValueKind::Value>
{
public:

internal:

	Matrix4f(const core::matrix4& other)
	{
		m_NativeValue = new core::matrix4(other);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime