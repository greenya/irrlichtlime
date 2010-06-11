#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

public:

	// operators

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

	static bool operator > (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return (*v1->m_NativeValue) > (*v2->m_NativeValue);
	}

	static bool operator >= (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return (*v1->m_NativeValue) >= (*v2->m_NativeValue);
	}

	static bool operator < (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return (*v1->m_NativeValue) < (*v2->m_NativeValue);
	}

	static bool operator <= (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return (*v1->m_NativeValue) <= (*v2->m_NativeValue);
	}

	static _REFCLASS_^ operator + (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) + (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator + (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) + v2);
	}

	static _REFCLASS_^ operator - (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) - (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator - (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) - v2);
	}

	static _REFCLASS_^ operator * (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) * (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator * (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) * v2);
	}

	static _REFCLASS_^ operator / (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) / (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator / (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) / v2);
	}

	// constructors

	_REFCLASS_(_REFCLASS_^ copy)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new _WRAPCLASS_(*copy->m_NativeValue);
	}

	_REFCLASS_(_WRAPTYPE_ value)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(value);
	}

	_REFCLASS_()
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_();
	}

	// Set()

	void Set(_REFCLASS_^ copy)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new _WRAPCLASS_(*copy->m_NativeValue);
	}

	// other common methods

	_WRAPTYPE_ DotProduct(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->dotProduct(*other->m_NativeValue);
	}

	bool EqualsTo(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->equals(*other->m_NativeValue);
	}

	_WRAPTYPE_ GetDistanceFrom(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->getDistanceFrom(*other->m_NativeValue);
	}

	_WRAPTYPE_ GetDistanceFromSQ(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->getDistanceFromSQ(*other->m_NativeValue);
	}

	_REFCLASS_^ GetInterpolated(_REFCLASS_^ other, double d)
	{
		LIME_ASSERT(other != nullptr);
		return gcnew _REFCLASS_(m_NativeValue->getInterpolated(*other->m_NativeValue, d));
	}

	_REFCLASS_^ GetInterpolatedQuadratic(_REFCLASS_^ other1, _REFCLASS_^ other2, double d)
	{
		LIME_ASSERT(other1 != nullptr);
		LIME_ASSERT(other2 != nullptr);

		return gcnew _REFCLASS_(m_NativeValue->getInterpolated_quadratic(*other1->m_NativeValue, *other2->m_NativeValue, d));
	}

	_REFCLASS_^ Interpolate(_REFCLASS_^ other1, _REFCLASS_^ other2, double d)
	{
		LIME_ASSERT(other1 != nullptr);
		LIME_ASSERT(other2 != nullptr);

		m_NativeValue->interpolate(*other1->m_NativeValue, *other2->m_NativeValue, d);
		return gcnew _REFCLASS_(*m_NativeValue);
	}

	bool IsBetweenPoints(_REFCLASS_^ begin, _REFCLASS_^ end)
	{
		LIME_ASSERT(begin != nullptr);
		LIME_ASSERT(end != nullptr);

		return m_NativeValue->isBetweenPoints(*begin->m_NativeValue, *end->m_NativeValue);
	}

	_REFCLASS_^ Normalize()
	{
		m_NativeValue->normalize();
		return gcnew _REFCLASS_(*m_NativeValue);
	}

	// properties

	property _WRAPTYPE_ LengthSQ
	{
		_WRAPTYPE_ get() { return m_NativeValue->getLengthSQ(); }
	}

	property _WRAPTYPE_ X
	{
		_WRAPTYPE_ get() { return m_NativeValue->X; }
		void set(_WRAPTYPE_ value) { m_NativeValue->X = value; }
	}

	property _WRAPTYPE_ Y
	{
		_WRAPTYPE_ get() { return m_NativeValue->Y; }
		void set(_WRAPTYPE_ value) { m_NativeValue->Y = value; }
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& other)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(other);
	}