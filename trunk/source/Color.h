#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Coloru : Lime::NativeValue<video::SColor>
{
public:

	Coloru(UInt32 color)
	{
		m_NativeValue = new video::SColor(color);
	}

	Coloru(UInt32 a, UInt32 r, UInt32 g, UInt32 b)
	{
		m_NativeValue = new video::SColor(a, r, g, b);
	}

	void Set(UInt32 a, UInt32 r, UInt32 g, UInt32 b)
	{
		((video::SColor*)m_NativeValue)->set(a, r, g, b);
	}

	property UInt32 Alpha
	{
		UInt32 get() { return m_NativeValue->getAlpha(); }
		void set(UInt32 value) { m_NativeValue->setAlpha(value); }
	}

	property UInt32 Average
	{
		UInt32 get() { return m_NativeValue->getAverage(); }
	}

	property UInt32 Blue
	{
		UInt32 get() { return m_NativeValue->getBlue(); }
		void set(UInt32 value) { m_NativeValue->setBlue(value); }
	}

	property UInt32 Color
	{
		UInt32 get() { return m_NativeValue->color; }
		void set(UInt32 value) { m_NativeValue->color = value; }
	}

	property UInt32 Green
	{
		UInt32 get() { return m_NativeValue->getGreen(); }
		void set(UInt32 value) { m_NativeValue->setGreen(value); }
	}

	property float Lightness
	{
		float get() { return m_NativeValue->getLightness(); }
	}

	property float Luminance
	{
		float get() { return m_NativeValue->getLuminance(); }
	}

	property UInt32 Red
	{
		UInt32 get() { return m_NativeValue->getRed(); }
		void set(UInt32 value) { m_NativeValue->setRed(value); }
	}

	property UInt16 A1R5G5B5
	{
		UInt16 get() { return m_NativeValue->toA1R5G5B5(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("Color={0:X}", Color);
	}

internal:

	Coloru(video::SColor value)
	{
		m_NativeValue = new video::SColor(value);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime