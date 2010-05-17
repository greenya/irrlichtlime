#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Vector2Di : Lime::NativeValue<core::vector2di>
{
public:

	Vector2Di(Int32 x, Int32 y)
	{
		m_NativeValue = new core::vector2di(x, y);
	}

	Vector2Di(Int32 xy)
	{
		m_NativeValue = new core::vector2di(xy);
	}

	Vector2Di()
	{
		m_NativeValue = new core::vector2di();
	}

	property Int32 X
	{
		Int32 get() { return m_NativeValue->X; }
		void set(Int32 value) { m_NativeValue->X = value; }
	}

	property Int32 Y
	{
		Int32 get() { return m_NativeValue->Y; }
		void set(Int32 value) { m_NativeValue->Y = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("X={0}; Y={1}", X, Y);
	}
};

public ref class Vector3Df : Lime::NativeValue<core::vector3df>
{
public:

	Vector3Df(float x, float y, float z)
	{
		m_NativeValue = new core::vector3df(x, y, z);
	}

	Vector3Df(float xyz)
	{
		m_NativeValue = new core::vector3df(xyz);
	}

	Vector3Df()
	{
		m_NativeValue = new core::vector3df();
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
		return String::Format("X={0}; Y={1}; Z={2}", X, Y, Z);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime