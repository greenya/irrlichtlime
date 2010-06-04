#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Recti : Lime::NativeValue<core::recti, Lime::NativeValueKind::Value>
{
public:

	Recti(int x1, int y1, int x2, int y2)
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
			return gcnew Vector2Di(m_NativeValue->UpperLeftCorner);
		}

		void set(Vector2Di^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->UpperLeftCorner = *value->m_NativeValue;
		}
	}

	property Vector2Di^ LowerRightCorner
	{
		Vector2Di^ get()
		{
			return gcnew Vector2Di(m_NativeValue->LowerRightCorner);
		}

		void set(Vector2Di^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->LowerRightCorner = *value->m_NativeValue;
		}
	}

	property int Width
	{
		int get() { return m_NativeValue->getWidth(); }
	}

	property int Height
	{
		int get() { return m_NativeValue->getHeight(); }
	}

	property int Area
	{
		int get() { return m_NativeValue->getArea(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("UpperLeftCorner={{{0}}}; LowerRightCorner={{{1}}}", UpperLeftCorner, LowerRightCorner);
	}

internal:

	Recti(const core::recti& value)
	{
		m_NativeValue = new core::recti(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime