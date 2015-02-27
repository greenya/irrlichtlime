#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

#include "irrMath.h"
[StructLayoutAttribute(LayoutKind::Sequential)]
public value class _REFCLASS_ : public IComparable<_REFCLASS_>, public IEquatable<_REFCLASS_>
{

public:

	_WRAPTYPE_ X;
	_WRAPTYPE_ Y;

	_REFCLASS_(_WRAPTYPE_ x, _WRAPTYPE_ y)
		: X(x), Y(y)
	{
	}

	explicit _REFCLASS_(_WRAPTYPE_ all)
		: X(all), Y(all)
	{
	}

	virtual int CompareTo(_REFCLASS_ other) sealed
	{
		/*if (*this == other)
			return 0;
		else if (*this < other)
			return -1;
		else
			return +1;
		*/
		if (core::equals(X, other.X))
			if (core::equals(Y, other.Y))
				return 0;
			else
				if (Y > other.Y)
					return +1;
				else
					return -1;
		else
			if (X > other.X)
				return +1;
			else
				return -1;

	}

	virtual bool Equals(_REFCLASS_ other) sealed
	{
		const _WRAPTYPE_ tolerance = (_WRAPTYPE_)ROUNDING_ERROR_f32;
		return core::equals(X, other.X, tolerance) && core::equals(Y, other.Y, tolerance);
	}

	bool Equals(_REFCLASS_ other, _WRAPTYPE_ tolerance)
	{
		return core::equals(X, other.X, tolerance) && core::equals(Y, other.Y, tolerance);
	}

	virtual bool Equals(Object^ other) override sealed
	{
		if (other == nullptr)
			return false;

		if (other->GetType() == _REFCLASS_::typeid)
			return Equals((_REFCLASS_)other);
		else
			return false;
	}

	static bool operator == (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return v1.Equals(v2);
	}

	static bool operator != (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return !v1.Equals(v2);
	}

	static bool operator > (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.X>v2.X && !core::equals(v1.X, v2.X)) ||
				(core::equals(v1.X, v2.X) && v1.Y>v2.Y && !core::equals(v1.Y, v2.Y));
	}

	static bool operator >= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.X>v2.X || core::equals(v1.X, v2.X)) ||
				(core::equals(v1.X, v2.X) && (v1.Y>v2.Y || core::equals(v1.Y, v2.Y)));
	}

	static bool operator < (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.X<v2.X && !core::equals(v1.X, v2.X)) ||
				(core::equals(v1.X, v2.X) && v1.Y<v2.Y && !core::equals(v1.Y, v2.Y));
	}

	static bool operator <= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.X<v2.X || core::equals(v1.X, v2.X)) ||
				(core::equals(v1.X, v2.X) && (v1.Y<v2.Y || core::equals(v1.Y, v2.Y)));
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.X + v2.X, v1.Y + v2.Y);
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.X + v2, v1.Y + v2);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _REFCLASS_ v2)
	{

		return _REFCLASS_(v1.X - v2.X, v1.Y - v2.Y);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.X - v2, v1.Y - v2);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.X * v2.X, v1.Y * v2.Y);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.X * v2, v1.Y * v2);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.X / v2.X, v1.Y / v2.Y);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.X / v2, v1.Y / v2);
	}

	void Set(_WRAPTYPE_ nx, _WRAPTYPE_ ny)
	{
		X = nx;
		Y = ny;
	}

	void Set(_REFCLASS_ copy)
	{
		X = copy.X;
		Y = copy.Y;
	}

	double GetAngleWith(_REFCLASS_ other)
	{
		double tmp = (double)(X*other.X + Y*other.Y);

		if (tmp == 0.0)
			return 90.0;

		tmp = tmp / core::squareroot((double)((X*X + Y*Y) * (other.X*other.X + other.Y*other.Y)));
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

		X -= center.X;
		Y -= center.Y;

		Set((_WRAPTYPE_)(X*cs - Y*sn), (_WRAPTYPE_)(X*sn + Y*cs));

		X += center.X;
		Y += center.Y;
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
			if (Y == 0) // corrected thanks to a suggestion by Jox
				return X < 0 ? 180 : 0;
			else if (X == 0)
				return Y < 0 ? 90 : 270;

			// don't use getLength here to avoid precision loss with s32 vectors
			// avoid floating-point trouble as sqrt(Y*Y) is occasionally larger than Y, so clamp
			const f64 tmp = core::clamp(Y / sqrt((f64)(X*X + Y*Y)), -1.0, 1.0);
			const f64 angle = atan( core::squareroot(1 - tmp*tmp) / tmp) * RADTODEG64;

			if (X>0 && Y>0)
				return angle + 270;
			else
			if (X>0 && Y<0)
				return angle + 90;
			else
			if (X<0 && Y<0)
				return 90 - angle;
			else
			if (X<0 && Y>0)
				return 270 - angle;

			return angle;
		}
	}

	property double AngleTrig
	{
		double get() 
		{
			if (Y == 0)
				return X < 0 ? 180 : 0;
			else
			if (X == 0)
				return Y < 0 ? 270 : 90;

			if (Y > 0)
				if (X > 0)
					return atan((irr::f64)Y/(irr::f64)X) * RADTODEG64;
				else
					return 180.0-atan((irr::f64)Y/-(irr::f64)X) * RADTODEG64;
			else
				if (X > 0)
					return 360.0-atan(-(irr::f64)Y/(irr::f64)X) * RADTODEG64;
				else
					return 180.0+atan(-(irr::f64)Y/-(irr::f64)X) * RADTODEG64;
		}
	}

	property _WRAPTYPE_ Length
	{
		_WRAPTYPE_ get() {  return core::squareroot(X*X + Y*Y); }
	}


	_WRAPTYPE_ DotProduct(_REFCLASS_ other)
	{
		return X*other.X + Y*other.Y;
	}

	_WRAPTYPE_ GetDistanceFrom(_REFCLASS_ other)
	{
		return _REFCLASS_(X - other.X, Y - other.Y).Length;
	}

	_WRAPTYPE_ GetDistanceFromSQ(_REFCLASS_ other)
	{
		return _REFCLASS_(X - other.X, Y - other.Y).LengthSQ;
	}

	_REFCLASS_ GetInterpolated(_REFCLASS_ other, double d)
	{
		f64 inv = 1.0f - d;
		return _REFCLASS_((_WRAPTYPE_)(other.X*inv + X*d), (_WRAPTYPE_)(other.Y*inv + Y*d));
	}

	_REFCLASS_ GetInterpolatedQuadratic(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		const f64 inv = 1.0f - d;
		const f64 mul0 = inv * inv;
		const f64 mul1 = 2.0f * d * inv;
		const f64 mul2 = d * d;

		return _REFCLASS_( (_WRAPTYPE_)(X * mul0 + other1.X * mul1 + other2.X * mul2),
					(_WRAPTYPE_)(Y * mul0 + other1.Y * mul1 + other2.Y * mul2));
	}

	_REFCLASS_ Interpolate(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		X = (_WRAPTYPE_)((f64)other1.X + ( ( other1.X - other2.X ) * d ));
		Y = (_WRAPTYPE_)((f64)other2.Y + ( ( other1.Y - other2.Y ) * d ));
		return *this;
	}

	bool IsBetweenPoints(_REFCLASS_ begin, _REFCLASS_ end)
	{
		if (begin.X != end.X)
		{
			return ((begin.X <= X && X <= end.X) ||
				(begin.X >= X && X >= end.X));
		}
		else
		{
			return ((begin.Y <= Y && Y <= end.Y) ||
				(begin.Y >= Y && Y >= end.Y));
		}
	}

	_REFCLASS_ Normalize()
	{
		f32 length = (f32)(X*X + Y*Y);
		if ( length == 0 )
			return *this;
		length = core::reciprocal_squareroot ( length );
		X = (_WRAPTYPE_)(X * length);
		Y = (_WRAPTYPE_)(Y * length);
		return *this;
	}

	// properties

	property _WRAPTYPE_ LengthSQ
	{
		_WRAPTYPE_ get() { return X*X + Y*Y; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0}, {1}", X, Y);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& other)
	{
		X = other.X;
		Y = other.Y;
	}
	
	operator _WRAPCLASS_()
	{
#ifdef FAST_TO_NATIVE
		return *(interior_ptr<_WRAPCLASS_>)this;
#else
		return _WRAPCLASS_(X, Y);
#endif
	}

	_WRAPCLASS_ ToNative()
	{
		return (_WRAPCLASS_)*this;
	}
};