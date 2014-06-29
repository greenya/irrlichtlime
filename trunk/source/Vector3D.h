#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

#include "irrMath.h"
[StructLayoutAttribute(LayoutKind::Sequential)]
public value class _REFCLASS_
{
public:

	_REFCLASS_(_WRAPTYPE_ x, _WRAPTYPE_ y, _WRAPTYPE_ z)
		: x(x), y(y), z(z)
	{
	}

	explicit _REFCLASS_(_WRAPTYPE_ all)
		: x(all), y(all), z(all)
	{
	}

	// operators

	static bool equals(_REFCLASS_ v1, _REFCLASS_ v2, _WRAPTYPE_ tolerance)
	{
		return core::equals(v1.x, v2.x, tolerance) &&
			core::equals(v1.y, v2.y, tolerance) &&
			core::equals(v1.z, v2.z, tolerance);
	}

	static bool equals(_REFCLASS_ v1, _REFCLASS_ v2)
	{
		_WRAPTYPE_ tolerance = (_WRAPTYPE_)ROUNDING_ERROR_f32;
		return core::equals(v1.x, v2.x, tolerance) &&
			core::equals(v1.y, v2.y, tolerance) &&
			core::equals(v1.z, v2.z, tolerance);
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
			(core::equals(v1.x, v2.x) && v1.y>v2.y && !core::equals(v1.y, v2.y)) ||
			(core::equals(v1.x, v2.x) && core::equals(v1.y, v2.y) && v1.z>v2.z && !core::equals(v1.z, v2.z));
	}

	static bool operator >= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x>v2.x || core::equals(v1.x, v2.x)) ||
			(core::equals(v1.x, v2.x) && (v1.y>v2.y || core::equals(v1.y, v2.y))) ||
			(core::equals(v1.x, v2.x) && core::equals(v1.y, v2.y) && (v1.z>v2.z || core::equals(v1.z, v2.z)));
	}

	static bool operator < (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x<v2.x && !core::equals(v1.x, v2.x)) ||
			(core::equals(v1.x, v2.x) && v1.y<v2.y && !core::equals(v1.y, v2.y)) ||
			(core::equals(v1.x, v2.x) && core::equals(v1.y, v2.y) && v1.z<v2.z && !core::equals(v1.z, v2.z));
	}

	static bool operator <= (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return (v1.x<v2.x || core::equals(v1.x, v2.x)) ||
			(core::equals(v1.x, v2.x) && (v1.y<v2.y || core::equals(v1.y, v2.y))) ||
			(core::equals(v1.x, v2.x) && core::equals(v1.y, v2.y) && (v1.z<v2.z || core::equals(v1.z, v2.z)));
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	static _REFCLASS_ operator + (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x + v2, v1.y + v2, v1.z + v2);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1)
	{
		return _REFCLASS_(-v1.x, -v1.y, -v1.z);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x - v2, v1.y - v2, v1.z - v2);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	static _REFCLASS_ operator * (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
		return _REFCLASS_(v1.x * v2, v1.y * v2, v1.z * v2);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _REFCLASS_ v2)
	{
		return _REFCLASS_(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}

	static _REFCLASS_ operator / (_REFCLASS_ v1, _WRAPTYPE_ v2)
	{
//Irrlicht has another implementation for floating point types, but I can't get it compile
//#if _WRAPTYPE_ int
		return _REFCLASS_(v1.x / v2, v1.y / v2, v1.z / v2);
//#else
//		_WRAPTYPE_ i = (_WRAPTYPE)1.0/v2;
//		return _REFCLASS_(v1.x * i, v1.y * i, v1.z * i);
//#endif
	}

	void Set(_WRAPTYPE_ nx, _WRAPTYPE_ ny, _WRAPTYPE_ nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}

	void Set(_REFCLASS_ copy)
	{
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}

	_REFCLASS_ CrossProduct(_REFCLASS_ other)
	{
		return _REFCLASS_(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	bool EqualsTo(_REFCLASS_ other, _WRAPTYPE_ tolerance)
	{
		return equals(*this, other, tolerance);
	}

	array<_WRAPTYPE_>^ ToArray()
	{
		array<_WRAPTYPE_>^ a = gcnew array<_WRAPTYPE_>(4);
		a[0] = x;
		a[1] = y;
		a[2] = z;
		a[3] = 0;

		return a;
	}

	_REFCLASS_ Invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		return *this;
	}

	void RotateXYby(double degrees, _REFCLASS_ center)
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		x -= center.x;
		y -= center.y;
		Set((_WRAPTYPE_)(x*cs - y*sn), (_WRAPTYPE_)(x*sn + y*cs), z);
		x += center.x;
		y += center.y;
	}

	void RotateXYby(double degrees)
	{
		RotateXYby(degrees, _REFCLASS_());
	}

	void RotateXZby(double degrees, _REFCLASS_ center)
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		x -= center.x;
		z -= center.z;
		Set((_WRAPTYPE_)(x*cs - z*sn), y, (_WRAPTYPE_)(x*sn + z*cs));
		x += center.x;
		z += center.z;
	}

	void RotateXZby(double degrees)
	{
		RotateXZby(degrees, _REFCLASS_());
	}

	void RotateYZby(double degrees, _REFCLASS_ center)
	{
		degrees *= DEGTORAD64;
		f64 cs = cos(degrees);
		f64 sn = sin(degrees);
		z -= center.z;
		y -= center.y;
		Set(x, (_WRAPTYPE_)(y*cs - z*sn), (_WRAPTYPE_)(y*sn + z*cs));
		z += center.z;
		y += center.y;
	}

	void RotateYZby(double degrees)
	{
		RotateYZby(degrees, _REFCLASS_());
	}

	_REFCLASS_ RotationToDirection(_REFCLASS_ forwards)
	{
		const f64 cr = cos( core::DEGTORAD64 * x );
		const f64 sr = sin( core::DEGTORAD64 * x );
		const f64 cp = cos( core::DEGTORAD64 * y );
		const f64 sp = sin( core::DEGTORAD64 * y );
		const f64 cy = cos( core::DEGTORAD64 * z );
		const f64 sy = sin( core::DEGTORAD64 * z );

		const f64 srsp = sr*sp;
		const f64 crsp = cr*sp;

		const f64 pseudoMatrix[] = {
			( cp*cy ), ( cp*sy ), ( -sp ),
			( srsp*cy-cr*sy ), ( srsp*sy+cr*cy ), ( sr*cp ),
			( crsp*cy+sr*sy ), ( crsp*sy-sr*cy ), ( cr*cp )};

		return _REFCLASS_(
			(_WRAPTYPE_)(forwards.x * pseudoMatrix[0] +
						 forwards.y * pseudoMatrix[3] +
						 forwards.z * pseudoMatrix[6]),
			(_WRAPTYPE_)(forwards.x * pseudoMatrix[1] +
						 forwards.y * pseudoMatrix[4] +
						 forwards.z * pseudoMatrix[7]),
			(_WRAPTYPE_)(forwards.x * pseudoMatrix[2] +
						 forwards.y * pseudoMatrix[5] +
						 forwards.z * pseudoMatrix[8]));
	}

	_REFCLASS_ RotationToDirection()
	{
		return RotationToDirection(_REFCLASS_(0, 0, 1));
	}

	
	_WRAPTYPE_ DotProduct(_REFCLASS_ other)
	{
		return x*other.x + y*other.y + z*other.z;
	}

	bool EqualsTo(_REFCLASS_ other)
	{
		return equals(*this, other);
	}

	_WRAPTYPE_ GetDistanceFrom(_REFCLASS_ other)
	{
		return _REFCLASS_(x - other.x, y - other.y, z - other.z).Length;
	}

	_WRAPTYPE_ GetDistanceFromSQ(_REFCLASS_ other)
	{
		return _REFCLASS_(x - other.x, y - other.y, z - other.z).LengthSQ;
	}

	_REFCLASS_ GetInterpolated(_REFCLASS_ other, double d)
	{
		const f64 inv = 1.0 - d;
		return _REFCLASS_((_WRAPTYPE_)(other.x*inv + x*d), (_WRAPTYPE_)(other.y*inv + y*d), (_WRAPTYPE_)(other.z*inv + z*d));
	}

	_REFCLASS_ GetInterpolatedQuadratic(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		const f64 inv = (_WRAPTYPE_) 1.0 - d;
		const f64 mul0 = inv * inv;
		const f64 mul1 = (_WRAPTYPE_) 2.0 * d * inv;
		const f64 mul2 = d * d;

		return _REFCLASS_((_WRAPTYPE_)(x * mul0 + other1.x * mul1 + other2.x * mul2),
				(_WRAPTYPE_)(y * mul0 + other1.y * mul1 + other2.y * mul2),
				(_WRAPTYPE_)(z * mul0 + other1.z * mul1 + other2.z * mul2));
	}

	_REFCLASS_ Interpolate(_REFCLASS_ other1, _REFCLASS_ other2, double d)
	{
		x = (_WRAPTYPE_)((f64)other2.x + ( ( other1.x - other2.x ) * d ));
		y = (_WRAPTYPE_)((f64)other2.y + ( ( other1.y - other2.y ) * d ));
		z = (_WRAPTYPE_)((f64)other2.z + ( ( other1.z - other2.z ) * d ));
		return *this;
	}

	bool IsBetweenPoints(_REFCLASS_ begin, _REFCLASS_ end)
	{
		const _WRAPTYPE_ f = (end - begin).LengthSQ;
		return GetDistanceFromSQ(begin) <= f &&
			GetDistanceFromSQ(end) <= f;
	}

	_REFCLASS_ Normalize()
	{
		f64 length = x*x + y*y + z*z;
		if (length == 0 ) // this check isn't an optimization but prevents getting NAN in the sqrt.
			return *this;
		length = core::reciprocal_squareroot(length);

		x = (_WRAPTYPE_)(x * length);
		y = (_WRAPTYPE_)(y * length);
		z = (_WRAPTYPE_)(z * length);
		return *this;
	}

	property _REFCLASS_ HorizontalAngle
	{
		_REFCLASS_ get()
		{ 
			_REFCLASS_ angle;

			// tmp avoids some precision troubles on some compilers when working with T=s32
			f64 tmp = (atan2((f64)x, (f64)z) * RADTODEG64);
			angle.y = (_WRAPTYPE_)tmp;

			if (angle.y < 0)
				angle.y += 360;
			if (angle.y >= 360)
				angle.y -= 360;

			const f64 z1 = core::squareroot(x*x + z*z);

			tmp = (atan2((f64)z1, (f64)y) * RADTODEG64 - 90.0);
			angle.x = (_WRAPTYPE_)tmp;

			if (angle.x < 0)
				angle.x += 360;
			if (angle.x >= 360)
				angle.x -= 360;

			return angle;
		}
	}

	property _WRAPTYPE_ Length
	{
		_WRAPTYPE_ get() { return core::squareroot( x*x + y*y + z*z ); }
		void set(_WRAPTYPE_ value)
		{ 
			Normalize();
			*this *= value;
		}
	}

	property _WRAPTYPE_ LengthSQ
	{
		_WRAPTYPE_ get() { return x*x + y*y + z*z; }
	}

	property _REFCLASS_ SphericalCoordinateAngles
	{
		_REFCLASS_ get() 
		{
			_REFCLASS_ angle;
			const f64 length = x*x + y*y + z*z;

			if (length)
			{
				if (x!=0)
				{
					angle.y = (_WRAPTYPE_)(atan2((f64)z,(f64)x) * RADTODEG64);
				}
				else if (z<0)
					angle.y=180;

				angle.x = (_WRAPTYPE_)(acos(y * core::reciprocal_squareroot(length)) * RADTODEG64);
			}
			return angle;
		}
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

	property _WRAPTYPE_ Z
	{
		_WRAPTYPE_ get() { return z; }
		void set(_WRAPTYPE_ value) { z = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0}, {1}, {2}", X, Y, Z);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& other)
	{
		x = other.X;
		y = other.Y;
		z = other.Z;
	}
	
	operator _WRAPCLASS_()
	{
		return _WRAPCLASS_(x, y, z);
	}

	_WRAPCLASS_ ToNative()
	{
		return (_WRAPCLASS_)*this;
	}

private:

	_WRAPTYPE_ x;
	_WRAPTYPE_ y;
	_WRAPTYPE_ z;

};