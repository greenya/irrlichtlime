#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_) || !defined(_OTHERTYPE1_) || !defined(_OTHERTYPE2_)
#error _REFCLASS_, _WRAPCLASS_, _WRAPTYPE_, _OTHERTYPE1_ and _OTHERTYPE2_ must be defined for this file to process.
#endif

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class _REFCLASS_ : public IEquatable<_REFCLASS_>
{
public:

	_OTHERTYPE1_ UpperLeftCorner;
	_OTHERTYPE1_ LowerRightCorner;

	virtual bool Equals(_REFCLASS_ other) sealed
	{
		return (UpperLeftCorner == other.UpperLeftCorner &&
			LowerRightCorner == other.LowerRightCorner);
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

	static _REFCLASS_ operator + (_REFCLASS_ v1, _OTHERTYPE1_ v2)
	{
		v1.UpperLeftCorner += v2;
		v1.LowerRightCorner += v2;
		return v1;
	}

	static _REFCLASS_ operator - (_REFCLASS_ v1, _OTHERTYPE1_ v2)
	{
		v1.UpperLeftCorner -= v2;
		v1.LowerRightCorner -= v2;
		return v1;
	}

	_REFCLASS_(_WRAPTYPE_ x1, _WRAPTYPE_ y1, _WRAPTYPE_ x2, _WRAPTYPE_ y2)
		: UpperLeftCorner(x1, y1), LowerRightCorner(x2, y2)
	{
	}

	_REFCLASS_(_OTHERTYPE1_ upperLeft, _OTHERTYPE1_ lowerRight)
		: UpperLeftCorner(upperLeft), LowerRightCorner(lowerRight)
	{
	}

	_REFCLASS_(_OTHERTYPE2_^ size)
	{
		LIME_ASSERT(size != nullptr);
		LIME_ASSERT(size->Width >= 0);
		LIME_ASSERT(size->Height >= 0);

		UpperLeftCorner = _OTHERTYPE1_(0, 0);
		LowerRightCorner = _OTHERTYPE1_(size->Width, size->Height);
	}

	_REFCLASS_(_OTHERTYPE1_ pos, _OTHERTYPE2_^ size)
	{
		LIME_ASSERT(size != nullptr);
		LIME_ASSERT(size->Width >= 0);
		LIME_ASSERT(size->Height >= 0);

		UpperLeftCorner = pos;
		LowerRightCorner = _OTHERTYPE1_(size->Width, size->Height) + pos;
	}

	void Repair()
	{
		if (LowerRightCorner.X < UpperLeftCorner.X)
		{
			_WRAPTYPE_ t = LowerRightCorner.X;
			LowerRightCorner.X = UpperLeftCorner.X;
			UpperLeftCorner.X = t;
		}

		if (LowerRightCorner.Y < UpperLeftCorner.Y)
		{
			_WRAPTYPE_ t = LowerRightCorner.Y;
			LowerRightCorner.Y = UpperLeftCorner.Y;
			UpperLeftCorner.Y = t;
		}
	}

	void AddInternalPoint(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		if (x>LowerRightCorner.X)
			LowerRightCorner.X = x;
		if (y>LowerRightCorner.Y)
			LowerRightCorner.Y = y;

		if (x<UpperLeftCorner.X)
			UpperLeftCorner.X = x;
		if (y<UpperLeftCorner.Y)
			UpperLeftCorner.Y = y;
	}

	void AddInternalPoint(_OTHERTYPE1_ point)
	{
		AddInternalPoint(point.X, point.Y);
	}
	
	void Adjust(_WRAPTYPE_ x1, _WRAPTYPE_ y1, _WRAPTYPE_ x2, _WRAPTYPE_ y2)
	{
		UpperLeftCorner.X += x1;
		UpperLeftCorner.Y += y1;
		LowerRightCorner.X += x2;
		LowerRightCorner.Y += y2;
	}

	void ClipAgainst(_REFCLASS_ other)
	{
		if (other.LowerRightCorner.X < LowerRightCorner.X)
			LowerRightCorner.X = other.LowerRightCorner.X;
		if (other.LowerRightCorner.Y < LowerRightCorner.Y)
			LowerRightCorner.Y = other.LowerRightCorner.Y;

		if (other.UpperLeftCorner.X > UpperLeftCorner.X)
			UpperLeftCorner.X = other.UpperLeftCorner.X;
		if (other.UpperLeftCorner.Y > UpperLeftCorner.Y)
			UpperLeftCorner.Y = other.UpperLeftCorner.Y;

		// correct possible invalid rect resulting from clipping
		if (UpperLeftCorner.Y > LowerRightCorner.Y)
			UpperLeftCorner.Y = LowerRightCorner.Y;
		if (UpperLeftCorner.X > LowerRightCorner.X)
			UpperLeftCorner.X = LowerRightCorner.X;
	}

	bool ConstrainTo(_REFCLASS_ other)
	{
		if (other.Width < Width || other.Height < Height)
			return false;

		_WRAPTYPE_ diff = other.LowerRightCorner.X - LowerRightCorner.X;
		if (diff < 0)
		{
			LowerRightCorner.X += diff;
			UpperLeftCorner.X  += diff;
		}

		diff = other.LowerRightCorner.Y - LowerRightCorner.Y;
		if (diff < 0)
		{
			LowerRightCorner.Y += diff;
			UpperLeftCorner.Y  += diff;
		}

		diff = UpperLeftCorner.X - other.UpperLeftCorner.X;
		if (diff < 0)
		{
			UpperLeftCorner.X  -= diff;
			LowerRightCorner.X -= diff;
		}

		diff = UpperLeftCorner.Y - other.UpperLeftCorner.Y;
		if (diff < 0)
		{
			UpperLeftCorner.Y  -= diff;
			LowerRightCorner.Y -= diff;
		}

		return true;
	}

	void Inflate(_WRAPTYPE_ width, _WRAPTYPE_ height)
	{
		_WRAPTYPE_ w2 = width / 2;
		_WRAPTYPE_ h2 = height / 2;

		UpperLeftCorner.X -= w2;
		UpperLeftCorner.Y -= h2;
		LowerRightCorner.X += w2;
		LowerRightCorner.Y += h2;
	}

	bool IsPointInside(_OTHERTYPE1_ pos)
	{
		return (UpperLeftCorner.X <= pos.X &&
			UpperLeftCorner.Y <= pos.Y &&
			LowerRightCorner.X >= pos.X &&
			LowerRightCorner.Y >= pos.Y);
	}

	bool IsPointInside(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		return IsPointInside(_OTHERTYPE1_(x, y));
	}

	bool IsRectCollided(_REFCLASS_ other)
	{
		return (LowerRightCorner.Y > other.UpperLeftCorner.Y &&
			UpperLeftCorner.Y < other.LowerRightCorner.Y &&
			LowerRightCorner.X > other.UpperLeftCorner.X &&
			UpperLeftCorner.X < other.LowerRightCorner.X);
	}

	void Offset(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		UpperLeftCorner.X += x;
		UpperLeftCorner.Y += y;
		LowerRightCorner.X += x;
		LowerRightCorner.Y += y;
	}

	property bool Valid
	{
		bool get()
		{
			return (
				(LowerRightCorner.X >= UpperLeftCorner.X) &&
				(LowerRightCorner.Y >= UpperLeftCorner.Y));
		}
	}

	property _WRAPTYPE_ Width
	{
		_WRAPTYPE_ get() { return LowerRightCorner.X - UpperLeftCorner.X; }
	}

	property _WRAPTYPE_ Height
	{
		_WRAPTYPE_ get() { return LowerRightCorner.Y - UpperLeftCorner.Y; }
	}

	property _WRAPTYPE_ Area
	{
		_WRAPTYPE_ get() { return Width * Height; }
	}

	property _OTHERTYPE1_ Center
	{
		_OTHERTYPE1_ get()
		{
			return _OTHERTYPE1_(
				(UpperLeftCorner.X + LowerRightCorner.X) / 2,
				(UpperLeftCorner.Y + LowerRightCorner.Y) / 2); 
		}
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) :: ({1})", UpperLeftCorner, LowerRightCorner);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& value)
		: UpperLeftCorner(value.UpperLeftCorner), LowerRightCorner(value.LowerRightCorner)
	{
	}

	operator _WRAPCLASS_()
	{
#ifdef FAST_TO_NATIVE
		return (_WRAPCLASS_&)*this;
		//return *(interior_ptr<_WRAPCLASS_>)this;
#else
		return _WRAPCLASS_(UpperLeftCorner.ToNative(), LowerRightCorner.ToNative());
#endif
	}

	_WRAPCLASS_ ToNative()
	{
		return (_WRAPCLASS_)*this;
	}

	static _REFCLASS_ Wrap(const _WRAPCLASS_& value)
	{
		return _REFCLASS_(value);
	}
};