#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
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

	static _REFCLASS_^ operator + (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		return gcnew _REFCLASS_((*v1->m_NativeValue) + (*v2->m_NativeValue));
	}

	static _REFCLASS_^ operator - (_REFCLASS_^ v1, _REFCLASS_^ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		LIME_ASSERT(v2 != nullptr);

		// this operator not implemented in Irrlicht' core::dimension2d<T>, so we implement it here
		return gcnew _REFCLASS_(
			v1->m_NativeValue->Width - v2->m_NativeValue->Width,
			v1->m_NativeValue->Height - v2->m_NativeValue->Height);
	}

	static _REFCLASS_^ operator * (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) * v2);
	}

	static _REFCLASS_^ operator / (_REFCLASS_^ v1, _WRAPTYPE_ v2)
	{
		LIME_ASSERT(v1 != nullptr);
		return gcnew _REFCLASS_((*v1->m_NativeValue) / v2);
	}

	_REFCLASS_(_REFCLASS_^ copy)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		LIME_ASSERT(copy != nullptr);
		m_NativeValue = new _WRAPCLASS_(*copy->m_NativeValue);
	}

	_REFCLASS_()
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_();
	}

	_REFCLASS_(_WRAPTYPE_ widthAndHeight)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(widthAndHeight, widthAndHeight);
	}

	_REFCLASS_(_WRAPTYPE_ width, _WRAPTYPE_ height)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(width, height);
	}

	void Set(_WRAPTYPE_ width, _WRAPTYPE_ height)
	{
		m_NativeValue->set(width, height);
	}

	_REFCLASS_^ GetInterpolated(_REFCLASS_^ other, float d)
	{
		LIME_ASSERT(other != nullptr);
		return gcnew _REFCLASS_(m_NativeValue->getInterpolated(*other->m_NativeValue, d));
	}

	_REFCLASS_^ GetOptimalSize(bool requirePowerOfTwo, bool requireSquare, bool larger, unsigned int maxValue)
	{
		return gcnew _REFCLASS_(m_NativeValue->getOptimalSize(requirePowerOfTwo, requireSquare, larger, maxValue));
	}

	_REFCLASS_^ GetOptimalSize(bool requirePowerOfTwo, bool requireSquare, bool larger)
	{
		return gcnew _REFCLASS_(m_NativeValue->getOptimalSize(requirePowerOfTwo, requireSquare, larger));
	}

	_REFCLASS_^ GetOptimalSize(bool requirePowerOfTwo, bool requireSquare)
	{
		return gcnew _REFCLASS_(m_NativeValue->getOptimalSize(requirePowerOfTwo, requireSquare));
	}

	_REFCLASS_^ GetOptimalSize(bool requirePowerOfTwo)
	{
		return gcnew _REFCLASS_(m_NativeValue->getOptimalSize(requirePowerOfTwo));
	}

	_REFCLASS_^ GetOptimalSize()
	{
		return gcnew _REFCLASS_(m_NativeValue->getOptimalSize());
	}

	property _WRAPTYPE_ Width
	{
		_WRAPTYPE_ get() { return m_NativeValue->Width; }
		void set(_WRAPTYPE_ value) { m_NativeValue->Width = value; }
	}

	property _WRAPTYPE_ Height
	{
		_WRAPTYPE_ get() { return m_NativeValue->Height; }
		void set(_WRAPTYPE_ value) { m_NativeValue->Height = value; }
	}

	property _WRAPTYPE_ Area
	{
		_WRAPTYPE_ get() { return m_NativeValue->getArea(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0} x {1}", Width, Height);
	}

internal:

	_REFCLASS_(const _WRAPCLASS_& value)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(value);
	}
};