#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Coloru : Lime::NativeValue<video::SColor>
{
public:

	Coloru(unsigned int color)
	{
		m_NativeValue = new video::SColor(color);
	}

	Coloru(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
	{
		m_NativeValue = new video::SColor(a, r, g, b);
	}

	void Set(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
	{
		m_NativeValue->set(a, r, g, b);
	}

	property unsigned int Alpha
	{
		unsigned int get() { return m_NativeValue->getAlpha(); }
		void set(unsigned int value) { m_NativeValue->setAlpha(value); }
	}

	property unsigned int Average
	{
		unsigned int get() { return m_NativeValue->getAverage(); }
	}

	property unsigned int Blue
	{
		unsigned int get() { return m_NativeValue->getBlue(); }
		void set(unsigned int value) { m_NativeValue->setBlue(value); }
	}

	property unsigned int Color
	{
		unsigned int get() { return m_NativeValue->color; }
		void set(unsigned int value) { m_NativeValue->color = value; }
	}

	property unsigned int Green
	{
		unsigned int get() { return m_NativeValue->getGreen(); }
		void set(unsigned int value) { m_NativeValue->setGreen(value); }
	}

	property float Lightness
	{
		float get() { return m_NativeValue->getLightness(); }
	}

	property float Luminance
	{
		float get() { return m_NativeValue->getLuminance(); }
	}

	property unsigned int Red
	{
		unsigned int get() { return m_NativeValue->getRed(); }
		void set(unsigned int value) { m_NativeValue->setRed(value); }
	}

	property unsigned __int16 A1R5G5B5
	{
		unsigned __int16 get() { return m_NativeValue->toA1R5G5B5(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("Color={0:X}", Color);
	}

internal:

	Coloru(const video::SColor& value)
	{
		m_NativeValue = new video::SColor(value);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime