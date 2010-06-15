#if !defined(_REFCLASS_) || !defined(_WRAPCLASS_) || !defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be defined for this file to process.
#endif

public ref class _REFCLASS_ : Lime::NativeValue<_WRAPCLASS_>
{
	#include "Vector_common_template.h"

public:

	_REFCLASS_(_WRAPTYPE_ x, _WRAPTYPE_ y)
		: Lime::NativeValue<_WRAPCLASS_>(true)
	{
		m_NativeValue = new _WRAPCLASS_(x, y);
	}

	void Set(_WRAPTYPE_ x, _WRAPTYPE_ y)
	{
		m_NativeValue->set(x, y);
	}

	double GetAngleWith(_REFCLASS_^ other)
	{
		LIME_ASSERT(other != nullptr);
		return m_NativeValue->getAngleWith(*other->m_NativeValue);
	}

	_REFCLASS_^ RotateBy(double degrees, _REFCLASS_^ center)
	{
		LIME_ASSERT(center != nullptr);
		return gcnew _REFCLASS_(m_NativeValue->rotateBy(degrees, *center->m_NativeValue));
	}

	_REFCLASS_^ RotateBy(double degrees)
	{
		return gcnew _REFCLASS_(m_NativeValue->rotateBy(degrees));
	}

	property double Angle
	{
		double get() { return m_NativeValue->getAngle(); }
	}

	// !!! excluded becuase of http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?p=225930#225930
	//property double AngleTrig
	//{
	//	double get() { return m_NativeValue->getAngleTrig(); }
	//}

	virtual String^ ToString() override
	{
		return String::Format("{0}, {1}", X, Y);
	}
};