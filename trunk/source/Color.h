#pragma once

#include "stdafx.h"
#include "irrMath.h"	//for core::min_ and core::max_, etc

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Color
{
public:

	static property Color OpaqueBlack { Color get() { return Color(0, 0, 0); } }
	static property Color OpaqueBlue { Color get() { return Color(0, 0, 255); } }
	static property Color OpaqueCyan { Color get() { return Color(0, 255, 255); } }
	static property Color OpaqueGreen { Color get() { return Color(0, 255, 0); } }
	static property Color OpaqueMagenta { Color get() { return Color(255, 0, 255); } }
	static property Color OpaqueRed { Color get() { return Color(255, 0, 0); } }
	static property Color OpaqueWhite { Color get() { return Color(255, 255, 255); } }
	static property Color OpaqueYellow { Color get() { return Color(255, 255, 0); } }

	static bool operator == (Color v1, Color v2)
	{
		return v1.color == v2.color;
	}

	static bool operator != (Color v1, Color v2)
	{
		return v1.color != v2.color;
	}

	Color(unsigned int argb)
	{
		color = argb;
	}

	Color(int r, int g, int b, int a)
	
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);
		LIME_ASSERT(a >= 0 && a <= 255);

		color = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
	}

	Color(int r, int g, int b)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);

		color = (((255 & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
	}

	void GetData(void *data, ColorFormat format)
	{
		switch(format)
		{
			case ColorFormat::A1R5G5B5:
			{
				u16 * dest = (u16*)data;
				*dest = video::A8R8G8B8toA1R5G5B5( color );
			}
			break;

			case ColorFormat::R5G6B5:
			{
				u16 * dest = (u16*)data;
				*dest = video::A8R8G8B8toR5G6B5( color );
			}
			break;

			case ColorFormat::R8G8B8:
			{
				u8* dest = (u8*)data;
				dest[0] = (u8)Red;
				dest[1] = (u8)Green;
				dest[2] = (u8)Blue;
			}
			break;

			case ColorFormat::A8R8G8B8:
			{
				u32 * dest = (u32*)data;
				*dest = color;
			}
			break;

		default:
			break;
		}
	}

	Color GetInterpolated(Color other, float d)
	{
		d = core::clamp(d, 0.f, 1.f);
		const f32 inv = 1.0f - d;
		return Color((u32)core::round32(other.Alpha*inv + Alpha*d),
			(u32)core::round32(other.Red*inv + Red*d),
			(u32)core::round32(other.Green*inv + Green*d),
			(u32)core::round32(other.Blue*inv + Blue*d));
	}

	void SetData(const void* data, ColorFormat format)
	{
		switch (format)
		{
			case ColorFormat::A1R5G5B5:
				color = A1R5G5B5toA8R8G8B8(*(u16*)data);
				break;
			case ColorFormat::R5G6B5:
				color = R5G6B5toA8R8G8B8(*(u16*)data);
				break;
			case ColorFormat::A8R8G8B8:
				color = *(u32*)data;
				break;
			case ColorFormat::R8G8B8:
				{
					u8* p = (u8*)data;
					Set(p[0],p[1],p[2], 255);
				}
				break;
			default:
				color = 0xffffffff;
			break;
		}
	}

	void Set(unsigned int col)
	{
		color = col;
	}

	void Set(int r, int g, int b, int a)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);
		LIME_ASSERT(a >= 0 && a <= 255);

		color = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
	}

	/*void Set(int r, int g, int b)
	{
		LIME_ASSERT(r >= 0 && r <= 255);
		LIME_ASSERT(g >= 0 && g <= 255);
		LIME_ASSERT(b >= 0 && b <= 255);

		m_NativeValue->set(m_NativeValue->getAlpha(), r, g, b);
	}*/

	/*void Set(unsigned int argb)
	{
		m_NativeValue->set(argb);
	}*/

	property unsigned __int16 A1R5G5B5
	{
		unsigned __int16 get() { return A8R8G8B8toA1R5G5B5(color); }
	}

	property unsigned int Alpha
	{
		unsigned int get() { return color>>24;; }
		void set(unsigned int value) { LIME_ASSERT(value >= 0 && value <= 255); color = ((value & 0xff)<<24) | (color & 0x00ffffff); }
	}

	property unsigned int ARGB
	{
		unsigned int get() { return color; }
		void set(unsigned int value) { color = value; }
	}

	property int Average
	{
		int get() { return (Red + Green + Blue) / 3; }
	}

	property unsigned int Blue
	{
		unsigned int get() { return color & 0xff; }
		void set(unsigned int value) { LIME_ASSERT(value >= 0 && value <= 255); color = (value & 0xff) | (color & 0xffffff00); }
	}


	property unsigned int Green
	{
		unsigned int get() { return (color>>8) & 0xff; }
		void set(unsigned int value) { LIME_ASSERT(value >= 0 && value <= 255); color = ((value & 0xff)<<8) | (color & 0xffff00ff); }
	}

	property float Lightness
	{
		float get() { return 0.5f*(core::max_(core::max_(Red,Green),Blue)+core::min_(core::min_(Red,Green),Blue)); }
	}

	property float Luminance
	{
		float get() { return 0.3f*Red + 0.59f*Green + 0.11f*Blue; }
	}

	property unsigned int Red
	{
		unsigned int get() { return (color>>16) & 0xff; }
		void set(unsigned int value) { LIME_ASSERT(value >= 0 && value <= 255); color = ((value & 0xff)<<16) | (color & 0xff00ffff); }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0:X2}, {1:X2}, {2:X2} ^ {3:X2}", Red, Green, Blue, Alpha);
	}

internal:

	Color(const video::SColor& value)
	{
		color = value.color;
	}

	operator SColor()	//Allow cast to SColor without cast
	{
		return color;
	}

	SColor ToNative()
	{
		return color;
	}

private:

	unsigned int color;

};

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Colorf
{
public:

	/*
	static bool operator == (Colorf v1, Colorf v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		video::SColorf& c1 = *v1->m_NativeValue;
		video::SColorf& c2 = *v2->m_NativeValue;

		return
			core::equals(c1.r, c2.r) &&
			core::equals(c1.g, c2.g) &&
			core::equals(c1.b, c2.b) &&
			core::equals(c1.a, c2.a);
	}

	static bool operator != (Colorf v1, Colorf v2)
	{
		return !(v1 == v2);
	}
	*/

	/*Colorf()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}*/

	/*Colorf(Colorf copyColorf)
		: Lime::NativeValue<video::SColorf>(true)
	{
		LIME_ASSERT(copyColorf != nullptr);
		m_NativeValue = new video::SColorf(
			copyColorf->m_NativeValue->r,
			copyColorf->m_NativeValue->g,
			copyColorf->m_NativeValue->b,
			copyColorf->m_NativeValue->a);
	}*/

	Colorf(Color copyColor)
	{
		const f32 inv = 1.0f / 255.0f;
		r = copyColor.Red * inv;
		g = copyColor.Green * inv;
		b = copyColor.Blue * inv;
		a = copyColor.Alpha * inv;
	}

	Colorf(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);
		LIME_ASSERT(a >= 0.0f && a <= 1.0f);
	}

	Colorf(float r, float g, float b)
		: r(r), g(g), b(b), a(255)
	{
		LIME_ASSERT(r >= 0.0f && r <= 1.0f);
		LIME_ASSERT(g >= 0.0f && g <= 1.0f);
		LIME_ASSERT(b >= 0.0f && b <= 1.0f);
	}

	/*
	void Set(Colorf copyColorf)
	{
		LIME_ASSERT(copyColorf != nullptr);
		m_NativeValue->set(
			copyColorf->m_NativeValue->a,
			copyColorf->m_NativeValue->r,
			copyColorf->m_NativeValue->g,
			copyColorf->m_NativeValue->b);
	}

	void Set(Color copyColor)
	{
		LIME_ASSERT(copyColor != nullptr);
		m_NativeValue->set(
			copyColor->m_NativeValue->getAlpha() / 255.0f,
			copyColor->m_NativeValue->getRed() / 255.0f,
			copyColor->m_NativeValue->getGreen() / 255.0f,
			copyColor->m_NativeValue->getBlue() / 255.0f);
	}
	*/

	void Set(float rr, float gg, float bb, float aa)
	{
		LIME_ASSERT(rr >= 0.0f && rr <= 1.0f);
		LIME_ASSERT(gg >= 0.0f && gg <= 1.0f);
		LIME_ASSERT(bb >= 0.0f && bb <= 1.0f);
		LIME_ASSERT(aa >= 0.0f && aa <= 1.0f);

		a = aa;
		r = rr;
		g = gg;
		b = bb;
	}

	void Set(float rr, float gg, float bb)
	{
		LIME_ASSERT(rr >= 0.0f && rr <= 1.0f);
		LIME_ASSERT(gg >= 0.0f && gg <= 1.0f);
		LIME_ASSERT(bb >= 0.0f && bb <= 1.0f);

		r = rr;
		g = gg;
		b = bb;
	}


	array<float>^ ToArray()
	{
		array<float>^ ar = gcnew array<float>(4);

		ar[0] = r;
		ar[1] = g;
		ar[2] = b;
		ar[3] = a;

		return ar;
	}

	Color ToColor()
	{
		return Color((unsigned int)core::round32(a*255.0f), (unsigned int)core::round32(r*255.0f), (unsigned int)core::round32(g*255.0f), (unsigned int)core::round32(b*255.0f));
	}

	property float Alpha
	{
		float get() { return a; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); a = value; }
	}

	property float Blue
	{
		float get() { return b; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); b = value; }
	}

	property float Green
	{
		float get() { return g; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); g = value; }
	}

	property float Red
	{
		float get() { return r; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 1.0f); r = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0:F3}, {1:F3}, {2:F3} ^ {3:F3}", Red, Green, Blue, Alpha);
	}

internal:

	Colorf(const video::SColorf& value)
	{
		r = value.r;
		g = value.g;
		b = value.b;
		a = value.a;
	}

	operator SColorf()
	{
		return SColorf(r, g, b, a);
	}

private:

	float r;
	float g;
	float b;
	float a;

};

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class ColorHSL
{
public:

	/*
	static bool operator == (ColorHSL v1, ColorHSL v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		video::SColorHSL& c1 = *v1->m_NativeValue;
		video::SColorHSL& c2 = *v2->m_NativeValue;

		return
			core::equals(c1.Hue, c2.Hue) &&
			core::equals(c1.Saturation, c2.Saturation) &&
			core::equals(c1.Luminance, c2.Luminance);
	}

	static bool operator != (ColorHSL v1, ColorHSL v2)
	{
		return !(v1 == v2);
	}

	ColorHSL()
		: Lime::NativeValue<video::SColorHSL>(true)
	{
		m_NativeValue = new video::SColorHSL();
	}

	ColorHSL(ColorHSL copyColorHSL)
		: Lime::NativeValue<video::SColorHSL>(true)
	{
		LIME_ASSERT(copyColorHSL != nullptr);

		video::SColorHSL &c = *copyColorHSL->m_NativeValue;
		m_NativeValue = new video::SColorHSL(c.Hue, c.Saturation, c.Luminance);
	}
	*/

	ColorHSL(Color copyColor)
	{
		ColorHSL copy = fromRGB(Colorf(copyColor));
		hue = copy.hue;
		saturation = copy.saturation;
		luminance = copy.luminance;
	}

	ColorHSL(Colorf copyColorf)
	{
		ColorHSL copy = fromRGB(copyColorf);
		hue = copy.hue;
		saturation = copy.saturation;
		luminance = copy.luminance;
	}

	ColorHSL(float hue, float saturation, float luminance)
		: hue(hue), saturation(saturation), luminance(luminance)
	{
		LIME_ASSERT(hue >= 0.0f && hue <= 360.0f);
		LIME_ASSERT(saturation >= 0.0f && saturation <= 100.0f);
		LIME_ASSERT(luminance >= 0.0f && luminance <= 100.0f);
	}
	/*
	void Set(ColorHSL copyColorHSL)
	{
		LIME_ASSERT(copyColorHSL != nullptr);

		video::SColorHSL &c = *copyColorHSL->m_NativeValue;
		m_NativeValue->Hue = c.Hue;
		m_NativeValue->Saturation = c.Saturation;
		m_NativeValue->Luminance = c.Luminance;
	}

	void Set(Color copyColor)
	{
		LIME_ASSERT(copyColor != nullptr);
		m_NativeValue->fromRGB(video::SColorf(*copyColor->m_NativeValue));
	}

	void Set(Colorf copyColorf)
	{
		LIME_ASSERT(copyColorf != nullptr);
		m_NativeValue->fromRGB(*copyColorf->m_NativeValue);
	}*/

	void Set(float h, float s, float l)
	{
		LIME_ASSERT(h >= 0.0f && h <= 360.0f);
		LIME_ASSERT(s >= 0.0f && s <= 100.0f);
		LIME_ASSERT(l >= 0.0f && l <= 100.0f);

		hue = h;
		saturation = s;
		luminance = l;
	}

	Color ToColor()
	{
		Colorf c = ToColorf();
		return c.ToColor();
	}

	Colorf ToColorf()
	{
		const float l = luminance/100;
		if (core::iszero(saturation)) // grey
		{
			Colorf(l, l, l);
		}

		float rm2;

		if ( luminance <= 50 )
		{
			rm2 = l + l * (saturation/100);
		}
		else
		{
			rm2 = l + (1 - l) * (saturation/100);
		}

		const float rm1 = 2.0f * l - rm2;

		const float h = hue / 360.0f;
		return Colorf( toRGB1(rm1, rm2, h + 1.f/3.f),
			toRGB1(rm1, rm2, h),
			toRGB1(rm1, rm2, h - 1.f/3.f)
			);
	}

	// algorithm from Foley/Van-Dam
	inline float toRGB1(f32 rm1, f32 rm2, f32 rh) 
	{
		if (rh<0)
			rh += 1;
		if (rh>1)
			rh -= 1;

		if (rh < 1.f/6.f)
			rm1 = rm1 + (rm2 - rm1) * rh*6.f;
		else if (rh < 0.5f)
			rm1 = rm2;
		else if (rh < 2.f/3.f)
			rm1 = rm1 + (rm2 - rm1) * ((2.f/3.f)-rh)*6.f;

		return rm1;
	}

	property float Hue
	{
		float get() { return hue; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 360.0f); hue = value; }
	}

	property float Luminance
	{
		float get() { return luminance; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 100.0f); luminance = value; }
	}

	property float Saturation
	{
		float get() { return saturation; }
		void set(float value) { LIME_ASSERT(value >= 0.0f && value <= 100.0f); saturation = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("Hue={0:F3}, Saturation={1:F3}, Luminance={2:F3}", Hue, Saturation, Luminance);
	}

internal:

	ColorHSL(const video::SColorHSL& value)
	{
		hue = value.Hue;
		saturation = value.Saturation;
		luminance = value.Luminance;
	}

	operator SColorHSL()
	{
		return SColorHSL(hue, saturation, luminance);
	}

private:

	float hue;
	float saturation;
	float luminance;

	static ColorHSL fromRGB(Colorf copyColor)
	{
		ColorHSL ret;
		const float maxVal = core::max_(copyColor.Red, copyColor.Green, copyColor.Blue);
		const float minVal = (float)core::min_(copyColor.Red, copyColor.Green, copyColor.Blue);
		ret.luminance = (maxVal+minVal)*50;
		if (core::equals(maxVal, minVal))
		{
			ret.hue=0.f;
			ret.saturation=0.f;
			return ret;
		}

		const f32 delta = maxVal-minVal;
		if ( ret.luminance <= 50 )
		{
			ret.saturation = (delta)/(maxVal+minVal);
		}
		else
		{
			ret.saturation = (delta)/(2-maxVal-minVal);
		}
		ret.saturation *= 100;

		if (core::equals(maxVal, copyColor.Red))
			ret.hue = (copyColor.Green-copyColor.Blue)/delta;
		else if (core::equals(maxVal, copyColor.Green))
			ret.hue = 2+((copyColor.Blue-copyColor.Red)/delta);
		else // blue is max
			ret.hue = 4+((copyColor.Red-copyColor.Green)/delta);

		ret.hue *= 60.0f;
		while ( ret.hue < 0.f )
			ret.hue += 360;

		return ret;
	}
};

} // end namespace Video
} // end namespace IrrlichtLime