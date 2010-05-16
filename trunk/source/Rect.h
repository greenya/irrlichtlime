#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Core
{
	public ref class Recti : Lime::NativeObject
	{
	public:

		Recti(Int32 x1, Int32 y1, Int32 x2, Int32 y2)
		{
			m_NativeObject = new core::recti(x1, y1, x2, y2);
		}

		Recti(Vector2Di^ upperLeft, Vector2Di^ lowerRight)
		{
			m_NativeObject = new core::recti(
				*(core::vector2di*)upperLeft->m_NativeObject,
				*(core::vector2di*)lowerRight->m_NativeObject);
		}

		property Vector2Di^ UpperLeftCorner
		{
			Vector2Di^ get()
			{
				core::vector2di v = ((core::recti*)m_NativeObject)->UpperLeftCorner;
				return gcnew Vector2Di(v.X, v.Y);
			}

			void set(Vector2Di^ value)
			{
				((core::recti*)m_NativeObject)->UpperLeftCorner = *((core::vector2di*)value->m_NativeObject);
			}
		}

		property Vector2Di^ LowerRightCorner
		{
			Vector2Di^ get()
			{
				core::vector2di v = ((core::recti*)m_NativeObject)->LowerRightCorner;
				return gcnew Vector2Di(v.X, v.Y);
			}

			void set(Vector2Di^ value)
			{
				((core::recti*)m_NativeObject)->LowerRightCorner = *((core::vector2di*)value->m_NativeObject);
			}
		}

		property Int32 Width
		{
			Int32 get() { return ((core::recti*)m_NativeObject)->getWidth(); }
		}

		property Int32 Height
		{
			Int32 get() { return ((core::recti*)m_NativeObject)->getHeight(); }
		}

		property Int32 Area
		{
			Int32 get() { return ((core::recti*)m_NativeObject)->getArea(); }
		}

		virtual String^ ToString() override
		{
			return String::Format("UpperLeftCorner={{{0}}}; LowerRightCorner={{{1}}}", UpperLeftCorner, LowerRightCorner);
		}

	internal:

		Recti(core::recti value)
		{
			m_NativeObject = new core::recti(value);
		}
	};
}
}