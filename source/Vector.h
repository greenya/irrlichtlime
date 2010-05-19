#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Vector2Di : Lime::NativeValue<core::vector2di>
{
public:

	Vector2Di(int x, int y)
	{
		m_NativeValue = new core::vector2di(x, y);
	}

	Vector2Di(int xy)
	{
		m_NativeValue = new core::vector2di(xy);
	}

	Vector2Di()
	{
		m_NativeValue = new core::vector2di();
	}

	property int X
	{
		int get() { return m_NativeValue->X; }
		void set(int value) { m_NativeValue->X = value; }
	}

	property int Y
	{
		int get() { return m_NativeValue->Y; }
		void set(int value) { m_NativeValue->Y = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("X={0}; Y={1}", X, Y);
	}
};

public ref class Vector2Df : Lime::NativeValue<core::vector2df>
{
public:

	Vector2Df(float x, float y)
	{
		m_NativeValue = new core::vector2df(x, y);
	}

	Vector2Df(float xy)
	{
		m_NativeValue = new core::vector2df(xy);
	}

	Vector2Df()
	{
		m_NativeValue = new core::vector2df();
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