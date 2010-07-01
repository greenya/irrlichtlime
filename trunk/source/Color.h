#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Color : Lime::NativeValue<video::SColor>
{
public:

	Color()
		: Lime::NativeValue<video::SColor>(true)
	{
		m_NativeValue = new video::SColor();
	}

	Color(Color^ copy)
		: Lime::NativeValue<video::SColor>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new video::SColor(copy->m_NativeValue->color);
	}

	Color(unsigned int argb)
		: Lime::NativeValue<video::SColor>(true)
	{
		m_NativeValue = new video::SColor(argb);
	}

	Color(int r, int g, int b, int a)
		: Lime::NativeValue<video::SColor>(true)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);
		LIME_ASSERT(a >= 0 && a <= 255);

		m_NativeValue = new video::SColor(a, r, g, b);
	}

	Color(int r, int g, int b)
		: Lime::NativeValue<video::SColor>(true)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);

		m_NativeValue = new video::SColor(255, r, g, b);
	}

	void Set(Color^ copy)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue->set(copy->m_NativeValue->color);
	}

	void Set(int r, int g, int b, int a)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);
		LIME_ASSERT(a >= 0 && a <= 255);

		m_NativeValue->set(a, r, g, b);
	}

	void Set(int r, int g, int b)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);

		m_NativeValue->set(m_NativeValue->getAlpha(), r, g, b);
	}

	void Set(unsigned int argb)
	{
		m_NativeValue->set(argb);
	}

	property unsigned __int16 A1R5G5B5
	{
		unsigned __int16 get() { return m_NativeValue->toA1R5G5B5(); }
	}

	property int Alpha
	{
		int get() { return m_NativeValue->getAlpha(); }
		void set(int value) { LIME_ASSERT(value >= 0 && value <= 255); m_NativeValue->setAlpha(value); }
	}

	property unsigned int ARGB
	{
		unsigned int get() { return m_NativeValue->color; }
		void set(unsigned int value) { m_NativeValue->color = value; }
	}

	property int Average
	{
		int get() { return m_NativeValue->getAverage(); }
	}

	property int Blue
	{
		int get() { return m_NativeValue->getBlue(); }
		void set(int value) { LIME_ASSERT(value >= 0 && value <= 255); m_NativeValue->setBlue(value); }
	}

	property int Green
	{
		int get() { return m_NativeValue->getGreen(); }
		void set(int value) { LIME_ASSERT(value >= 0 && value <= 255); m_NativeValue->setGreen(value); }
	}

	property float Lightness
	{
		float get() { return m_NativeValue->getLightness(); }
	}

	property float Luminance
	{
		float get() { return m_NativeValue->getLuminance(); }
	}

	property int Red
	{
		int get() { return m_NativeValue->getRed(); }
		void set(int value) { LIME_ASSERT(value >= 0 && value <= 255); m_NativeValue->setRed(value); }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0:X2}, {1:X2}, {2:X2} ^ {3:X2}", Red, Green, Blue, Alpha);
	}

internal:

	Color(const video::SColor& value)
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

	Colorf(Colorf^ copy)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new video::SColorf(
			copy->m_NativeValue->r,
			copy->m_NativeValue->g,
			copy->m_NativeValue->b,
			copy->m_NativeValue->a);
	}

	Colorf(Color^ copy)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new video::SColorf(*copy->m_NativeValue);
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

	void Set(Colorf^ copy)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue->set(
			copy->m_NativeValue->a,
			copy->m_NativeValue->r,
			copy->m_NativeValue->g,
			copy->m_NativeValue->b);
	}

	void Set(Color^ copy)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue->set(
			copy->m_NativeValue->getAlpha() / 255.0f,
			copy->m_NativeValue->getRed() / 255.0f,
			copy->m_NativeValue->getGreen() / 255.0f,
			copy->m_NativeValue->getBlue() / 255.0f);
	}

	void Set(float r, float g, float b, float a)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);
		LIME_ASSERT(a >= 0.0f && a <= 1.0f);

		m_NativeValue->set(a, r, g, b);
	}

	void Set(float r, float g, float b)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);

		m_NativeValue->set(r, g, b);
	}

	Color^ ToColor()
	{
		return gcnew Color(m_NativeValue->toSColor());
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