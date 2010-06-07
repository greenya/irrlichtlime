#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Coloru : Lime::NativeValue<video::SColor>
{
public:

	Coloru()
		: Lime::NativeValue<video::SColor>(true)
	{
		m_NativeValue = new video::SColor();
	}

	Coloru(unsigned int color)
		: Lime::NativeValue<video::SColor>(true)
	{
		m_NativeValue = new video::SColor(color);
	}

	Coloru(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		: Lime::NativeValue<video::SColor>(true)
	{
		LIME_ASSERT(r <= 255);
		LIME_ASSERT(g <= 255);
		LIME_ASSERT(b <= 255);
		LIME_ASSERT(a <= 255);

		m_NativeValue = new video::SColor(a, r, g, b);
	}

	Coloru(unsigned int r, unsigned int g, unsigned int b)
		: Lime::NativeValue<video::SColor>(true)
	{
		LIME_ASSERT(r <= 255);
		LIME_ASSERT(g <= 255);
		LIME_ASSERT(b <= 255);

		m_NativeValue = new video::SColor(255, r, g, b);
	}

	void Set(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
	{
		LIME_ASSERT(r <= 255);
		LIME_ASSERT(g <= 255);
		LIME_ASSERT(b <= 255);
		LIME_ASSERT(a <= 255);

		m_NativeValue->set(a, r, g, b);
	}

	void Set(unsigned int r, unsigned int g, unsigned int b)
	{
		LIME_ASSERT(r <= 255);
		LIME_ASSERT(g <= 255);
		LIME_ASSERT(b <= 255);

		m_NativeValue->set(m_NativeValue->getAlpha(), r, g, b);
	}

	void Set(unsigned int argb)
	{
		m_NativeValue->set(argb);
	}

	property unsigned int Alpha
	{
		unsigned int get() { return m_NativeValue->getAlpha(); }
		void set(unsigned int value) { LIME_ASSERT(value <= 255); m_NativeValue->setAlpha(value); }
	}

	property unsigned int Average
	{
		unsigned int get() { return m_NativeValue->getAverage(); }
	}

	property unsigned int Blue
	{
		unsigned int get() { return m_NativeValue->getBlue(); }
		void set(unsigned int value) { LIME_ASSERT(value <= 255); m_NativeValue->setBlue(value); }
	}

	property unsigned int Color
	{
		unsigned int get() { return m_NativeValue->color; }
		void set(unsigned int value) { m_NativeValue->color = value; }
	}

	property unsigned int Green
	{
		unsigned int get() { return m_NativeValue->getGreen(); }
		void set(unsigned int value) { LIME_ASSERT(value <= 255); m_NativeValue->setGreen(value); }
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
		void set(unsigned int value) { LIME_ASSERT(value <= 255); m_NativeValue->setRed(value); }
	}

	property unsigned __int16 A1R5G5B5
	{
		unsigned __int16 get() { return m_NativeValue->toA1R5G5B5(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0:X2}, {1:X2}, {2:X2} ^ {3:X2}", Red, Green, Blue, Alpha);
	}

internal:

	Coloru(const video::SColor& value)
		: Lime::NativeValue<video::SColor>(true)
	{
		m_NativeValue = new video::SColor(value);
	}
};

public ref class Colorf : Lime::NativeValue<video::SColorf>
{
public:

	Colorf()
		: Lime::NativeValue<video::SColorf>(true)
	{
		m_NativeValue = new video::SColorf();
	}

	Colorf(float r, float g, float b, float a)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);
		LIME_ASSERT(a >= 0.0f && a <= 1.0f);

		m_NativeValue = new video::SColorf(r, g, b, a);
	}

	Colorf(float r, float g, float b)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);

		m_NativeValue = new video::SColorf(r, g, b);
	}

	Colorf(Coloru^ color)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(color != nullptr);
		m_NativeValue = new video::SColorf(*color->m_NativeValue);
	}

	void Set(float r, float g, float b)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);

		m_NativeValue->set(r, g, b);
	}

	void Set(float r, float g, float b, float a)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);
		LIME_ASSERT(a >= 0.0f && a <= 1.0f);

		m_NativeValue->set(a, r, g, b);
	}

	Coloru^ ToColoru()
	{
		return gcnew Coloru(m_NativeValue->toSColor());
	}

	property float Alpha
	{
		float get() { return m_NativeValue->a; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); m_NativeValue->a = value; }
	}

	property float Blue
	{
		float get() { return m_NativeValue->b; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); m_NativeValue->b = value; }
	}

	property float Green
	{
		float get() { return m_NativeValue->g; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); m_NativeValue->g = value; }
	}

	property float Red
	{
		float get() { return m_NativeValue->r; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); m_NativeValue->r = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0:F3}, {1:F3}, {2:F3} ^ {3:F3}", Red, Green, Blue, Alpha);
	}

internal:

	Colorf(const video::SColorf& value)
		: Lime::NativeValue<video::SColorf>(true)
	{
		m_NativeValue = new video::SColorf(value);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime