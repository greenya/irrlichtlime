#pragma once

#if defined(_REFCLASS_) || defined(_WRAPCLASS_) || defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be undefined for this file to process.
#endif

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Vector2Df : Lime::NativeValue<core::vector2df>
{
public:

	Vector2Df(Vector2Df^ copy)
		: Lime::NativeValue<core::vector2df>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new core::vector2df(*copy->m_NativeValue);
	}

	Vector2Df(float x, float y)
		: Lime::NativeValue<core::vector2df>(true)
	{
		m_NativeValue = new core::vector2df(x, y);
	}

	Vector2Df(float xy)
		: Lime::NativeValue<core::vector2df>(true)
	{
		m_NativeValue = new core::vector2df(xy);
	}

	Vector2Df()
		: Lime::NativeValue<core::vector2df>(true)
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
		return String::Format("{0},{1}", X, Y);
	}

internal:

	Vector2Df(const core::vector2df& other)
		: Lime::NativeValue<core::vector2df>(true)
	{
		m_NativeValue = new core::vector2df(other);
	}
};

public ref class Vector2Di : Lime::NativeValue<core::vector2di>
{
public:

	Vector2Di(Vector2Di^ copy)
		: Lime::NativeValue<core::vector2di>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new core::vector2di(*copy->m_NativeValue);
	}

	Vector2Di(int x, int y)
		: Lime::NativeValue<core::vector2di>(true)
	{
		m_NativeValue = new core::vector2di(x, y);
	}

	Vector2Di(int xy)
		: Lime::NativeValue<core::vector2di>(true)
	{
		m_NativeValue = new core::vector2di(xy);
	}

	Vector2Di()
		: Lime::NativeValue<core::vector2di>(true)
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
		return String::Format("{0},{1}", X, Y);
	}

internal:

	Vector2Di(const core::vector2di& other)
		: Lime::NativeValue<core::vector2di>(true)
	{
		m_NativeValue = new core::vector2di(other);
	}
};

#define _REFCLASS_ Vector3Df
#define _WRAPCLASS_ core::vector3df
#define _WRAPTYPE_ float
#include "Vector3D_template.h"
#undef _WRAPTYPE_
#undef _WRAPCLASS_
#undef _REFCLASS_

#define _REFCLASS_ Vector3Di
#define _WRAPCLASS_ core::vector3di
#define _WRAPTYPE_ int
#include "Vector3D_template.h"
#undef _WRAPTYPE_
#undef _WRAPCLASS_
#undef _REFCLASS_

} // end namespace Core
} // end namespace IrrlichtLime