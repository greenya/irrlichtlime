#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

#include "irrMath.h"
[StructLayoutAttribute(LayoutKind::Sequential)]
public value class _REFCLASS_
{

public:

	_REFCLASS_(_WRAPTYPE_ x, _WRAPTYPE_ y)
		: x(x), y(y)
	{
	}

	explicit _REFCLASS_(_WRAPTYPE_ all)
		: x(all), y(all)
	{
	}

	// operators

	static bool equals(_REFCLASS_ v1, _REFCLASS_ v2, _WRAPTYPE_ tolerance)
	{
		return core::equals(v1.x, v2.x, tolerance) && core::equals(v1.y, v2.y, tolerance);
	}

	static bool equals(_REFCLASS_ v1, _REFCLASS_ v2)
	{
		_WRAPTYPE_ tolerance = (_WRAPTYPE_)ROUNDING_ERROR_f32;
		return core::equals(v1.x, v2.x, tolerance) && core::equals(v1.y, v2.y, tolerance);
	}

	static bool operator == (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return equals(v1, v2);
	}

	static bool operator != (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return !equals(v1, v2);
	}

	static bool operator > (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x>v2.x && !core::equals(v1.x, v2.x)) ||
				(core::equals(v1.x, v2.x) && v1.y>v2.y && !core::equals(v1.y, v2.y));
	}

	static bool operator >= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x>v2.x || core::equals(v1.x, v2.x)) ||
				(core::equals(v1.x, v2.x) && (v1.y>v2.y || core::equals(v1.y, v2.y)));
	}

	static bool operator < (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x<v2.x && !core::equals(v1.x, v2.x)) ||
				(core::equals(v1.x, v2.x) && v1.y<v2.y && !core::equals(v1.y, v2.y));
	}

	static bool operator <= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x<v2.x || core::equals(v1.x, v2.x)) ||
				(core::equals(v1.x, v2.x) && (v1.y<v2.y || core::equals(v1.y, v2.y)));
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x + v2.x, v1.y + v2.y);
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x + v2, v1.y + v2);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _REFCLASS_ v2)
	{

		return _REFCLASS_(v1.x - v2.x, v1.y - v2.y);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x - v2, v1.y - v2);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x * v2.x, v1.y * v2.y);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x * v2, v1.y * v2);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x / v2.x, v1.y / v2.y);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x / v2, v1.y / v2);
	}

	void Set(_WRAPTYPE_ nx, _WRAPTYPE_ ny)
	{
		x = nx;
		y = ny;
	}

	void Set(_REFCLASS_ copy)
	{
		x = copy.x;
		y = copy.y;
	}

	double GetAngleWith(_REFCLASS_ other)
	{
		double tmp = (double)(x*other.x + y*other.y);

		if (tmp == 0.0)
			return 90.0;

		tmp = tmp / core::squareroot((double)((x*x + y*y) * (other.x*other.x + other.y*other.y)));
		if (tmp < 0.0)
			tmp = -tmp;
		if ( tmp > 1.0 ) //   avoid floating-point trouble
			tmp = 1.0;

		return atan(sqrt(1 - tmp*tmp) / tmp) * RADTODEG64;
	}

	_REFCLASS_ RotateBy(double degrees, _REFCLASS_ center)
	{
		degrees *= DEGTORAD64;
		const f64 cs = cos(degrees);
		const f64 sn = sin(degrees);

		x -= center.x;
		y -= center.y;

		Set((_WRAPTYPE_)(x*cs - y*sn), (_WRAPTYPE_)(x*sn + y*cs));

		x += center.x;
		y += center.y;
		return *this;
	}

	_REFCLASS_ RotateBy(double degrees)
	{
		return RotateBy(degrees, _REFCLASS_());	//dunno if we need to write a * in front of RotateBy... both compile
	}

	property double Angle
	{
		double get()
		{
			if (y == 0) // corrected thanks to a suggestion by Jox
				return x < 0 ? 180 : 0;
			else if (x == 0)
				return y < 0 ? 90 : 270;

			// don't use getLength here to avoid precision loss with s32 vectors
			// avoid floating-point trouble as sqrt(y*y) is occasionally larger than y, so clamp
			const f64 tmp = core::clamp(y / sqrt((f64)(x*x + y*y)), -1.0, 1.0);
			const f64 angle = atan( core::squareroot(1 - tmp*tmp) / tmp) * RADTODEG64;

			if (x>0 && y>0)
				return angle + 270;
			else
			if (x>0 && y<0)
				return angle + 90;
			else
			if (x<0 && y<0)
				return 90 - angle;
			else
			if (x<0 && y>0)
				return 270 - angle;

			return angle;
		}
	}

	property double AngleTrig
	{
		double get() 
		{
			if (y == 0)
				return x < 0 ? 180 : 0;
			else
			if (x == 0)
				return y < 0 ? 270 : 90;

			if (y > 0)
				if (x > 0)
					return atan((irr::f64)y/(irr::f64)x) * RADTODEG64;
				else
					return 180.0-atan((irr::f64)y/-(irr::f64)x) * RADTODEG64;
			else
				if (x > 0)
					return 360.0-atan(-(irr::f64)y/(irr::f64)x) * RADTODEG64;
				else
					return 180.0+atan(-(irr::f64)y/-(irr::f64)x) * RADTODEG64;
		}
	}

	property _WRAPTYPE_ Length
	{
		_WRAPTYPE_ get() {  return core::squareroot(x*x + y*y); }
	}


	_WRAPTYPE_ DotProduct(_REFCLASS_ other)
	{
		return x*other.x + y*other.y;
	}

	bool EqualsTo(_REFCLASS_ other)
	{
		return equals(*this, other);
	}

	_WRAPTYPE_ GetDistanceFrom(_REFCLASS_ other)
	{
		return _REFCLASS_(x - other.x, y - other.y).Length;
	}

	_WRAPTYPE_ GetDistanceFromSQ(_REFCLASS_ other)
	{
		return _REFCLASS_(x - other.x, y - other.y).LengthSQ;
	}

	_REFCLASS_ GetInterpolated(_REFCLASS_ other, double d)
	{
		f64 inv = 1.0f - d;
		return _REFCLASS_((_WRAPTYPE_)(other.x*inv + x*d), (_WRAPTYPE_)(other.y*inv + y*d));
	}

	_REFCLASS_ GetInterpolatedQuadratic(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		const f64 inv = 1.0f - d;
		const f64 mul0 = inv * inv;
		const f64 mul1 = 2.0f * d * inv;
		const f64 mul2 = d * d;

		return _REFCLASS_( (_WRAPTYPE_)(x * mul0 + other1.x * mul1 + other2.x * mul2),
					(_WRAPTYPE_)(y * mul0 + other1.y * mul1 + other2.y * mul2));
	}

	_REFCLASS_ Interpolate(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		x = (_WRAPTYPE_)((f64)other1.x + ( ( other1.x - other2.x ) * d ));
		y = (_WRAPTYPE_)((f64)other2.y + ( ( other1.y - other2.y ) * d ));
		return *this;
	}

	bool IsBetweenPoints(_REFCLASS_ begin, _REFCLASS_ end)
	{
		if (begin.x != end.x)
		{
			return ((begin.x <= x && x <= end.x) ||
				(begin.x >= x && x >= end.x));
		}
		else
		{
			return ((begin.y <= y && y <= end.y) ||
				(begin.y >= y && y >= end.y));
		}
	}

	_REFCLASS_ Normalize()
	{
		f32 length = (f32)(x*x + y*y);
		if ( length == 0 )
			return *this;
		length = core::reciprocal_squareroot ( length );
		x = (_WRAPTYPE_)(x * length);
		y = (_WRAPTYPE_)(y * length);
		return *this;
	}

	// properties

	property _WRAPTYPE_ LengthSQ
	{
		_WRAPTYPE_ get() { return x*x + y*y; }
	}

	property _WRAPTYPE_ X
	{
		_WRAPTYPE_ get() { return x; }
		void set(_WRAPTYPE_ value) { x = value; }
	}

	property _WRAPTYPE_ Y
	{
		_WRAPTYPE_ get() { return y; }
		void set(_WRAPTYPE_ value) { y = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0}, {1}", X, Y);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& other)
	{
		x = other.X;
		y = other.Y;
	}
	
	operator _WRAPCLASS_()
	{
		return _WRAPCLASS_(x, y);
	}

	_WRAPCLASS_ ToNative()
	{
		return (_WRAPCLASS_)*this;
	}

private:
	
	_WRAPTYPE_ x;
	_WRAPTYPE_ y;

};