#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Coloru : Lime::NativeObject
{
public:

	Coloru(UInt32 color)
	{
		m_NativeObject = new video::SColor(color);
	}

	Coloru(UInt32 a, UInt32 r, UInt32 g, UInt32 b)
	{
		m_NativeObject = new video::SColor(a, r, g, b);
	}

	void Set(UInt32 a, UInt32 r, UInt32 g, UInt32 b)
	{
		((video::SColor*)m_NativeObject)->set(a, r, g, b);
	}

	property UInt32 Alpha
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->getAlpha(); }
		void set(UInt32 value) { ((video::SColor*)m_NativeObject)->setAlpha(value); }
	}

	property UInt32 Average
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->getAverage(); }
	}

	property UInt32 Blue
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->getBlue(); }
		void set(UInt32 value) { ((video::SColor*)m_NativeObject)->setBlue(value); }
	}

	property UInt32 Color
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->color; }
		void set(UInt32 value) { ((video::SColor*)m_NativeObject)->color = value; }
	}

	property UInt32 Green
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->getGreen(); }
		void set(UInt32 value) { ((video::SColor*)m_NativeObject)->setGreen(value); }
	}

	property float Lightness
	{
		float get() { return ((video::SColor*)m_NativeObject)->getLightness(); }
	}

	property float Luminance
	{
		float get() { return ((video::SColor*)m_NativeObject)->getLuminance(); }
	}

	property UInt32 Red
	{
		UInt32 get() { return ((video::SColor*)m_NativeObject)->getRed(); }
		void set(UInt32 value) { ((video::SColor*)m_NativeObject)->setRed(value); }
	}

	property UInt16 A1R5G5B5
	{
		UInt16 get() { return ((video::SColor*)m_NativeObject)->toA1R5G5B5(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("Color={0:X}", Color);
	}

internal:

	Coloru(video::SColor value)
	{
		m_NativeObject = new video::SColor(value);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime