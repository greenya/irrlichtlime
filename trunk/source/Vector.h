#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Vector2Di : Lime::NativeObject
{
public:

	Vector2Di(Int32 x, Int32 y)
	{
		m_NativeObject = new core::vector2di(x, y);
	}

	Vector2Di(Int32 xy)
	{
		m_NativeObject = new core::vector2di(xy);
	}

	Vector2Di()
	{
		m_NativeObject = new core::vector2di();
	}

	property Int32 X
	{
		Int32 get() { return ((core::vector2di*)m_NativeObject)->X; }
		void set(Int32 value) { ((core::vector2di*)m_NativeObject)->X = value; }
	}

	property Int32 Y
	{
		Int32 get() { return ((core::vector2di*)m_NativeObject)->Y; }
		void set(Int32 value) { ((core::vector2di*)m_NativeObject)->Y = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("X={0}; Y={1}", X, Y);
	}
};

public ref class Vector3Df : Lime::NativeObject
{
public:

	Vector3Df(float x, float y, float z)
	{
		m_NativeObject = new core::vector3df(x, y, z);
	}

	Vector3Df(float xyz)
	{
		m_NativeObject = new core::vector3df(xyz);
	}

	Vector3Df()
	{
		m_NativeObject = new core::vector3df();
	}

	property float X
	{
		float get() { return ((core::vector3df*)m_NativeObject)->X; }
		void set(float value) { ((core::vector3df*)m_NativeObject)->X = value; }
	}

	property float Y
	{
		float get() { return ((core::vector3df*)m_NativeObject)->Y; }
		void set(float value) { ((core::vector3df*)m_NativeObject)->Y = value; }
	}

	property float Z
	{
		float get() { return ((core::vector3df*)m_NativeObject)->Z; }
		void set(float value) { ((core::vector3df*)m_NativeObject)->Z = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("X={0}; Y={1}; Z={2}", X, Y, Z);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime