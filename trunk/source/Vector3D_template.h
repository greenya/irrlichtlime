#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

public ref class _REFCLASS_ : Lime::NativeValue<_WRAPCLASS_>
{
	#include "Vector_common_template.h"

public:

	_REFCLASS_(_WRAPTYPE_ x, _WRAPTYPE_ y, _WRAPTYPE_ z)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(x, y, z);
	}

	void Set(_WRAPTYPE_ x, _WRAPTYPE_ y, _WRAPTYPE_ z)
	{
		m_NativeValue->set(x, y, z);
	}

	_REFCLASS_^ CrossProduct(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return gcnew _REFCLASS_(m_NativeValue->crossProduct(*other->m_NativeValue));
	}

	bool EqualsTo(_REFCLASS_^ other, _WRAPTYPE_ tolerance)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->equals(*other->m_NativeValue, tolerance);
	}

	array<_WRAPTYPE_>^ ToArray()
	{
		_WRAPTYPE_ b[4];
		m_NativeValue->getAs4Values(b);

		array<_WRAPTYPE_>^ a = gcnew array<_WRAPTYPE_>(4);
		for (int i = 0; i < 4; i++)
			a[i] = b[i];

		return a;
	}

	_REFCLASS_^ Invert()
	{
		m_NativeValue->invert();
		return gcnew _REFCLASS_(*m_NativeValue);
	}

	void RotateXYby(double degrees, _REFCLASS_^ center)
	{
		LIME_ASSERT(center != nullptr);
		m_NativeValue->rotateXYBy(degrees, *center->m_NativeValue);
	}

	void RotateXYby(double degrees)
	{
		m_NativeValue->rotateXYBy(degrees);
	}

	void RotateXZby(double degrees, _REFCLASS_^ center)
	{
		LIME_ASSERT(center != nullptr);
		m_NativeValue->rotateXZBy(degrees, *center->m_NativeValue);
	}

	void RotateXZby(double degrees)
	{
		m_NativeValue->rotateXZBy(degrees);
	}

	void RotateYZby(double degrees, _REFCLASS_^ center)
	{
		LIME_ASSERT(center != nullptr);
		m_NativeValue->rotateYZBy(degrees, *center->m_NativeValue);
	}

	void RotateYZby(double degrees)
	{
		m_NativeValue->rotateYZBy(degrees);
	}

	_REFCLASS_^ RotationToDirection(_REFCLASS_^ forwards)
	{
		LIME_ASSERT(forwards != nullptr);
		return gcnew _REFCLASS_(m_NativeValue->rotationToDirection(*forwards->m_NativeValue));
	}

	_REFCLASS_^ RotationToDirection()
	{
		return gcnew _REFCLASS_(m_NativeValue->rotationToDirection());
	}

	property _REFCLASS_^ HorizontalAngle
	{
		_REFCLASS_^ get() { return gcnew _REFCLASS_(m_NativeValue->getHorizontalAngle()); }
	}

	property _WRAPTYPE_ Length
	{
		_WRAPTYPE_ get() { return m_NativeValue->getLength(); }
		void set(_WRAPTYPE_ value) { m_NativeValue->setLength(value); }
	}

	property _REFCLASS_^ SphericalCoordinateAngles
	{
		_REFCLASS_^ get() { return gcnew _REFCLASS_(m_NativeValue->getSphericalCoordinateAngles()); }
	}

	property _WRAPTYPE_ Z
	{
		_WRAPTYPE_ get() { return m_NativeValue->Z; }
		void set(_WRAPTYPE_ value) { m_NativeValue->Z = value; }
	}

	virtual String^ ToString() override
	{
		return String::Format("{0},{1},{2}", X, Y, Z);
	}
};