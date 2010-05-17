#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

public ref class Dimension2Du : Lime::NativeValue<core::dimension2du>
{
public:

	Dimension2Du(UInt32 width, UInt32 height)
	{
		m_NativeValue = new core::dimension2du(width, height);
	}

	property UInt32 Width
	{
		UInt32 get() { return m_NativeValue->Width; }
		void set(UInt32 value) { m_NativeValue->Width = value; }
	}

	property UInt32 Height
	{
		UInt32 get() { return m_NativeValue->Height; }
		void set(UInt32 value) { m_NativeValue->Height = value; }
	}

	property UInt32 Area
	{
		UInt32 get() { return m_NativeValue->getArea(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("Width={0}; Height={1}", Width, Height);
	}

internal:

	Dimension2Du(core::dimension2du value)
	{
		m_NativeValue = new core::dimension2du(value);
	}
};

} // end namespace Core
} // end namespace IrrlichtLime