#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_) || !defined(_OTHERTYPE1_) || !defined(_OTHERTYPE2_)
#error _REFCLASS_, _WRAPCLASS_, _WRAPTYPE_, _OTHERTYPE1_ and _OTHERTYPE2_ must be defined for this file to process.
#endif

public ref class _REFCLASS_ : Lime::NativeValue<_WRAPCLASS_>
{
public:

	static bool operator == (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		bool v1n = Object::ReferenceEquals(v1, nullptr);
		bool v2n = Object::ReferenceEquals(v2, nullptr);

		if (v1n && v2n)
			return true;

		if (v1n || v2n)
			return false;

		return (*v1->m_NativeValue) == (*v2->m_NativeValue);
	}

	static bool operator != (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		return !(v1 == v2);
	}

	static _REFCLASS_^ operator + (_REFCLASS_^ v1, _OTHERTYPE1_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) + (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator - (_REFCLASS_^ v1, _OTHERTYPE1_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) - (*v2->m_NativeValue));
	}

	_REFCLASS_()
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_();
	}

	_REFCLASS_(_WRAPTYPE_ x1, _WRAPTYPE_ y1, _WRAPTYPE_ x2, _WRAPTYPE_ y2)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(x1, y1, x2, y2);
	}

	_REFCLASS_(_OTHERTYPE1_^ pos, _OTHERTYPE2_^ size)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		LIME_ASSERT(pos != nullptr);
		LIME_ASSERT(size != nullptr);
		LIME_ASSERT(size->Width >= 0);
		LIME_ASSERT(size->Height >= 0);

		m_NativeValue = new _WRAPCLASS_(*pos->m_NativeValue, *size->m_NativeValue);
	}

	_REFCLASS_(_OTHERTYPE1_^ upperLeft, _OTHERTYPE1_^ lowerRight)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		LIME_ASSERT(upperLeft != nullptr);
		LIME_ASSERT(lowerRight != nullptr);

		m_NativeValue = new _WRAPCLASS_(*upperLeft->m_NativeValue, *lowerRight->m_NativeValue);
	}

	void Repair()
	{
		m_NativeValue->repair();
	}

	void AddInternalPoint(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		m_NativeValue->addInternalPoint(x, y);
	}

	void AddInternalPoint(_OTHERTYPE1_^ point)
	{
		LIME_ASSERT(point != nullptr);
		m_NativeValue->addInternalPoint(*point->m_NativeValue);
	}

	void Adjust(_WRAPTYPE_ x1, _WRAPTYPE_ y1, _WRAPTYPE_ x2, _WRAPTYPE_ y2)
	{
		m_NativeValue->UpperLeftCorner.X += x1;
		m_NativeValue->UpperLeftCorner.Y += y1;
		m_NativeValue->LowerRightCorner.X += x2;
		m_NativeValue->LowerRightCorner.Y += y2;
	}

	void ClipAgainst(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->clipAgainst(*other->m_NativeValue);
	}

	bool ConstrainTo(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->constrainTo(*other->m_NativeValue);
	}

	void Inflate(_WRAPTYPE_ width, _WRAPTYPE_ height)
	{
		_WRAPTYPE_ w2 = width / 2;
		_WRAPTYPE_ h2 = height / 2;

		m_NativeValue->UpperLeftCorner.X -= w2;
		m_NativeValue->UpperLeftCorner.Y -= h2;
		m_NativeValue->LowerRightCorner.X += w2;
		m_NativeValue->LowerRightCorner.Y += h2;
	}

	bool IsPointInside(_OTHERTYPE1_^ pos)
	{
		LIME_ASSERT(pos != nullptr);
		return m_NativeValue->isPointInside(*pos->m_NativeValue);
	}

	bool IsRectCollided(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->isRectCollided(*other->m_NativeValue);
	}

	void Offset(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		m_NativeValue->UpperLeftCorner.X += x;
		m_NativeValue->UpperLeftCorner.Y += y;
		m_NativeValue->LowerRightCorner.X += x;
		m_NativeValue->LowerRightCorner.Y += y;
	}

	property bool Valid
	{
		bool get() { return m_NativeValue->isValid(); }
	}

	property _WRAPTYPE_ Width
	{
		_WRAPTYPE_ get() { return m_NativeValue->getWidth(); }
	}

	property _WRAPTYPE_ Height
	{
		_WRAPTYPE_ get() { return m_NativeValue->getHeight(); }
	}

	property _WRAPTYPE_ Area
	{
		_WRAPTYPE_ get() { return m_NativeValue->getArea(); }
	}

	property _OTHERTYPE1_^ Center
	{
		_OTHERTYPE1_^ get() { return gcnew _OTHERTYPE1_(m_NativeValue->getCenter()); }
	}

	property _OTHERTYPE1_^ UpperLeftCorner
	{
		_OTHERTYPE1_^ get() { return gcnew _OTHERTYPE1_(m_NativeValue->UpperLeftCorner); }
		void set(_OTHERTYPE1_^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->UpperLeftCorner = *value->m_NativeValue; }
	}

	property _OTHERTYPE1_^ LowerRightCorner
	{
		_OTHERTYPE1_^ get() { return gcnew _OTHERTYPE1_(m_NativeValue->LowerRightCorner); }
		void set(_OTHERTYPE1_^ value) { LIME_ASSERT(value != nullptr); m_NativeValue->LowerRightCorner = *value->m_NativeValue; }
	}

	virtual String^ ToString() override
	{
		return String::Format("({0}) :: ({1})", UpperLeftCorner, LowerRightCorner);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& value)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(value);
	}
};