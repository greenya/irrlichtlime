#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Core
{
	public ref class Dimension2Du : Lime::NativeObject
	{
	public:
		Dimension2Du(UInt32 width, UInt32 height)
		{
			m_NativeObject = new core::dimension2du(width, height);
		}

		property UInt32 Width
		{
			UInt32 get() { return ((core::dimension2du*)m_NativeObject)->Width; }
			void set(UInt32 value) { ((core::dimension2du*)m_NativeObject)->Width = value; }
		}

		property UInt32 Height
		{
			UInt32 get() { return ((core::dimension2du*)m_NativeObject)->Height; }
			void set(UInt32 value) { ((core::dimension2du*)m_NativeObject)->Height = value; }
		}

		property UInt32 Area
		{
			UInt32 get() { return ((core::dimension2du*)m_NativeObject)->getArea(); }
		}

		virtual String^ ToString() override
		{
			return String::Format("Width={0}; Height={1}", Width, Height);
		}

	internal:

		Dimension2Du(core::dimension2du value)
		{
			m_NativeObject = new core::dimension2du(value);
		}
	};
}
}