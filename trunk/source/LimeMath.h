#pragma once

//#include "stdafx.h"

//using namespace System;

#define LimeM IrrlichtLime::LimeMath

namespace IrrlichtLime {

private ref class LimeMath abstract sealed	//"abstract sealed" means "static" in C#
{
public:

	literal int ROUNDING_ERROR_S32 = 0;
	literal long long ROUNDING_ERROR_S64 = 0;
	literal float ROUNDING_ERROR_f32 = 0.000001f;
	literal double ROUNDING_ERROR_f64 = 0.00000001;

	literal float PI = 3.14159265359f;
	literal float RECIPROCAL_PI = 1.0f/PI;
	literal float HALF_PI = PI/2.0f;
	literal double PI64 = 3.1415926535897932384626433832795028841971693993751;
	literal double RECIPROCAL_PI64 = 1.0/PI64;
	literal float DEGTORAD = PI / 180.0f;
	literal float RADTODEG   = 180.0f / PI;
	literal double DEGTORAD64 = PI64 / 180.0;
	literal double RADTODEG64 = 180.0 / PI64;

	//these are only defines in irrMath.h 
	//and the compiler redirects them automatically to System::Math. I'm impressed.

	/*static double Atan2(const double Y, const double X)
	{
		return System::Math::Atan2(Y, X);
	}*/

	//wherever the float version of atan2 is used, it creates a native call. So we need this one.
	static float Atan2(const float Y, const float X)
	{
		return (float)System::Math::Atan2(Y, X);
	}
	
	static float Sinf(const float f)
	{
		return (float)System::Math::Sin(f);
	}

	static float Cosf(const float f)
	{
		return (float)System::Math::Cos(f);
	}

	static float Asinf(const float f)
	{
		return (float)System::Math::Asin(f);
	}

	static float Acosf(const float f)
	{
		return (float)System::Math::Acos(f);
	}

	//for whatever reason sqrtf and squareroot do the same thing in irrlicht...
	static float Sqrtf(const float f)
	{
		return (float)System::Math::Sqrt(f);
	}

	static float Squareroot(const float f)
	{
		return (float)System::Math::Sqrt(f);
	}

	static double Squareroot(const double f)
	{
		return System::Math::Sqrt(f);
	}

	static int Squareroot(const int f)
	{
		return (int)Squareroot((float)f);
	}

	static long long Squareroot(const long long f)
	{
		return (long long)Squareroot((double)f);
	}

	static double Reciprocal_squareroot(const double x)
	{
		return 1.0 / System::Math::Sqrt(x);
	}

	static float Reciprocal_squareroot(const float f)
	{
		return 1.f / (float)System::Math::Sqrt(f);
	}

	static int Reciprocal_squareroot(const int x)
	{
		return (int)Reciprocal_squareroot((float)x);
	}


	static float Reciprocal(const float f)
	{
		return 1.f / f;
	}

	static double Reciprocal (const double f)
	{
		return 1.0 / f;
	}

	static int Round32(float x)
	{
		return (int)System::Math::Round(x);
	}

	template<class T>
	static const T Min_(const T a, const T b)
	{
		return a < b ? a : b;
	}

	template<class T>
	static const T Min_(const T a, const T b, const T c)
	{
		return a < b ? Min_(a, c) : Min_(b, c);
	}

	template<class T>
	static const T Max_(const T a, const T b)
	{
		return a < b ? b : a;
	}

	template<class T>
	static const T Max_(const T a, const T b, const T c)
	{
		return a < b ? Max_(b, c) : Max_(a, c);
	}

	template <class T>
	static const T Clamp(const T value, const T low, const T high)
	{
		return Min_(Max_(value,low), high);
	}

	static bool Iszero(const double a, const double tolerance)
	{
		return System::Math::Abs(a) <= tolerance;
	}

	static bool Iszero(const double a)
	{
		const double tolerance = LimeM::ROUNDING_ERROR_f64;
		return System::Math::Abs(a) <= tolerance;
	}

	static bool Iszero(const float a, const float tolerance)
	{
		return System::Math::Abs(a) <= tolerance;
	}

	static bool Iszero(const float a)
	{
		const float tolerance = LimeM::ROUNDING_ERROR_f32;
		return System::Math::Abs(a) <= tolerance;
	}

	static bool Isnotzero(const float a, const float tolerance)
	{
		return System::Math::Abs(a) > tolerance;
	}

	static bool Isnotzero(const float a)
	{
		const float tolerance = LimeM::ROUNDING_ERROR_f32;
		return System::Math::Abs(a) > tolerance;
	}

	static bool Iszero(const int a, const int tolerance)
	{
		return ( a & 0x7ffffff ) <= tolerance;
	}

	static bool Iszero(const int a)
	{
		const int tolerance = 0;
		return ( a & 0x7ffffff ) <= tolerance;
	}

	static bool Iszero(const unsigned int a, const unsigned int tolerance)
	{
		return a <= tolerance;
	}

	static bool Iszero(const unsigned int a)
	{
		const unsigned int tolerance = 0;
		return a <= tolerance;
	}

	static bool Iszero(const long long a, const long long tolerance)
	{
		return System::Math::Abs(a) <= tolerance;
	}

	static bool Iszero(const long long a)
	{
		const long long tolerance = 0;
		return System::Math::Abs(a) <= tolerance;
	}


	static bool Equals(const double a, const double b, const double tolerance)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const double a, const double b)
	{
		const double tolerance = ROUNDING_ERROR_f64;
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const float a, const float b, const float tolerance)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const float a, const float b)
	{
		const float tolerance = ROUNDING_ERROR_f32;
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const int a, const int b, const int tolerance)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const int a, const int b)
	{
		const int tolerance = ROUNDING_ERROR_S32;
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const unsigned int a, const unsigned int b, const int tolerance)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	static bool Equals(const unsigned int a, const unsigned int b)
	{
		const int tolerance = ROUNDING_ERROR_S32;
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	template <class T>
	static bool EqualsRelative(const T a, const T b, const T factor)
	{
		const T maxi = Max_( a, b);
		const T mini = Min_( a, b);
		const T maxMagnitude = Max_( maxi, -mini);

		return	(maxMagnitude*factor + maxi) == (maxMagnitude*factor + mini); // MAD Wise
	}

	template <class T>
	static bool EqualsRelative(const T a, const T b)
	{
		const T factor = RelativeErrorFactor<T>::Value;
		return EqualsRelative(a, b, factor);
	}

internal:

	template<class T>
	value class RoundingError { };

	template<>
	value class RoundingError<float> { public: literal float Value = LimeM::ROUNDING_ERROR_f32; };

	template<>
	value class RoundingError<double> { public:  literal double Value = LimeM::ROUNDING_ERROR_f64; };

	template<>
	value class RoundingError<int> { public:  literal int Value = LimeM::ROUNDING_ERROR_S32; };

	template<>
	value class RoundingError<long long> { public: literal long long Value = LimeM::ROUNDING_ERROR_S64; };


	template<class T>
	value class RelativeErrorFactor { public: literal int Value = 1; };

	template<>
	value class RelativeErrorFactor<float> { public: literal float Value = 4; };

	template<>
	value class RelativeErrorFactor<double> { public: literal double Value = 8; };
};

} // end namespace IrrlichtLime