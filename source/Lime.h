#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::Reflection; // for Assembly
using namespace System::Runtime::InteropServices; // for Marshal

//#define FAST_TO_NATIVE	//generates faster code when passing structs to native code, but untested (doesn't use the construtor, instead it generates a cpblk instruction)
//maybe test it some day, but disabled for now, actually only generates the cpblk instruction for quaternion, not for others (don't know why, maybe because it's exactly 16 bytes)

#ifdef _DEBUG
#define LIME_ASSERT(condition) System::Diagnostics::Debug::Assert(condition, #condition);
#define LIME_ASSERT2(condition, details) System::Diagnostics::Debug::Assert(condition, #condition, details);
#else
#define LIME_ASSERT(condition) 
#define LIME_ASSERT2(condition, details) 
#endif

//Purpose of these: make code easier-to-read and shorter.
//They are espacially useful for passing variables to native code.
//
//LIME_SAFEREF: makes sure the object is not null before trying to access the member.
//
//LIME_NULLABLE: Takes a nullable and returns a pointer to its value (and calls ToNative()). If it has no value it returns null.
//BUT IT CAUSES A C4238 WARNING! Because we return a pointer to a temporary variable. But it works as expected because the variables live long enough.
//May cause problems with other compiler versions, which don't support this. For now, I've disabled this warning in the project settings.
//Tested with VS 2010

#define LIME_SAFEREF(object, member) ((object) == nullptr ? nullptr : (object)->member)
#define LIME_NULLABLE(nullable) (((nullable).HasValue ? &(nullable).Value.ToNative() : nullptr))
#define LIME_SAFESTRINGTOSTRINGC_C_STR(string) ((string) == nullptr ? nullptr : Lime::StringToStringC(string).c_str())
#define LIME_SAFESTRINGTOSTRINGW_C_STR(string) ((string) == nullptr ? nullptr : Lime::StringToStringW(string).c_str())

//experimental macros. not in use.
/*#define LIME_STACK(object, managedClass) managedClass##_native object##_stack = (object).m_NativeValue
#define LIME_ACCESS(object, nativeClass) (*(nativeClass*)&object##_stack)
#define LIME_UNSTACK(object) object.m_NativeValue = object##_stack

#define LIME_STACK_THIS(managedClass) managedClass##_native this_stack = (*this).m_NativeValue
#define LIME_ACCESS_THIS(nativeClass) (*(nativeClass*)&this_stack)
#define LIME_UNSTACK_THIS() (*this).m_NativeValue = this_stack*/

//Note: Warning 4714 is disabled. It shows up, when something could not be inlined. Happens when using Irrlicht math.

namespace IrrlichtLime {

public ref class Lime
{
public:

	template <class T>
	ref class NativeValue
	{
	public:		

		~NativeValue()
		{
			this->!NativeValue();
		}

		!NativeValue()
		{
			if (m_DeleteOnFinalize)
				delete m_NativeValue;
		}

		virtual int GetHashCode() override
		{
			return *(int*)m_NativeValue;	//assumes our native value is at least four bytes long, needs to be overwritten for smaller types
		}

	internal:

		T* m_NativeValue;

	protected:

		NativeValue(bool deleteOnFinalize)
		{
			m_DeleteOnFinalize = deleteOnFinalize;
		}

	private:

		bool m_DeleteOnFinalize;
	};

	static property String^ Version
	{
		String^ get()
		{
			System::Version^ v = Assembly::GetAssembly(Lime::typeid)->GetName()->Version;
			String^ s;

			if (v->Build != 0)
				s = String::Format("{0}.{1}.{2}", v->Major, v->Minor, v->Build);
			else
				s = String::Format("{0}.{1}", v->Major, v->Minor);

			if (System::IntPtr::Size == 4)
				s += " (x86)";
			else if (System::IntPtr::Size == 8)
				s += " (x64)";
			else
				s += " (x??)";

#if _DEBUG
			s += " (DEBUG)";
#endif
			return s;
		}
	}

internal:

	static io::path StringToPath(String^ s)
	{
		return io::path(StringToStringW(s));
	}

	static core::stringc StringToStringC(String^ s)
	{
		LIME_ASSERT(s != nullptr);

		char* c = (char*)Marshal::StringToHGlobalAnsi(s).ToPointer();
		core::stringc strC = core::stringc(c);

		Marshal::FreeHGlobal(IntPtr(c));
		return strC;
	}

	static core::stringw StringToStringW(String^ s)
	{
		LIME_ASSERT(s != nullptr);

		wchar_t* w = (wchar_t*)Marshal::StringToHGlobalUni(s).ToPointer();
		core::stringw strW = core::stringw(w);

		Marshal::FreeHGlobal(IntPtr(w));
		return strW;
	}

private:

	Lime() {}
};

} // end namespace IrrlichtLime