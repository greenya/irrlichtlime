#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Recti : Lime::NativeValue<core::recti>
{
public:

	Recti(Int32 x1, Int32 y1, Int32 x2, Int32 y2)
	{
		m_NativeValue = new core::recti(x1, y1, x2, y2);
	}

	Recti(Vector2Di^ upperLeft, Vector2Di^ lowerRight)
	{
		m_NativeValue = new core::recti(*upperLeft->m_NativeValue, *lowerRight->m_NativeValue);
	}

	property Vector2Di^ UpperLeftCorner
	{
		Vector2Di^ get()
		{
			return gcnew Vector2Di(m_NativeValue->UpperLeftCorner.X, m_NativeValue->UpperLeftCorner.Y);
		}

		void set(Vector2Di^ value)
		{
			m_NativeValue->UpperLeftCorner = *value->m_NativeValue;
		}
	}

	property Vector2Di^ LowerRightCorner
	{
		Vector2Di^ get()
		{
			return gcnew Vector2Di(m_NativeValue->LowerRightCorner.X, m_NativeValue->LowerRightCorner.Y);
		}

		void set(Vector2Di^ value)
		{
			m_NativeValue->LowerRightCorner = *value->m_NativeValue;
		}
	}

	property Int32 Width
	{
		Int32 get() { return m_NativeValue->getWidth(); }
	}

	property Int32 Height
	{
		Int32 get() { return m_NativeValue->getHeight(); }
	}

	property Int32 Area
	{
		Int32 get() { return m_NativeValue->getArea(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("UpperLeftCorner={{{0}}}; LowerRightCorner={{{1}}}", UpperLeftCorner, LowerRightCorner);
	}

internal:

	Recti(core::recti value)
	{
		m_NativeValue = new core::recti(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime