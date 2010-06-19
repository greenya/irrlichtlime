#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::Reflection; // for Assembly
using namespace System::Runtime::InteropServices; // for Marshal

#ifdef _DEBUG
#define LIME_ASSERT(condition) System::Diagnostics::Debug::Assert(condition, #condition);
#define LIME_ASSERT2(condition, details) System::Diagnostics::Debug::Assert(condition, #condition, details);
#else
#define LIME_ASSERT(condition)
#define LIME_ASSERT2(condition, details)
#endif

#define LIME_SAFEREF(object, member) (object == nullptr ? nullptr : object->member)

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
			if (m_DeleteOnFinalize &&
				m_NativeValue != nullptr)
			{
				delete m_NativeValue;
				m_NativeValue = nullptr;
			}
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
			String^ s = String::Format("{0}.{1}.{2}", v->Major, v->Minor, v->Build);
#if _DEBUG
			s += " DEBUG";
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
		if (s == nullptr)
			return core::stringc();

		char* c = (char*)Marshal::StringToHGlobalAnsi(s).ToPointer();
		core::stringc strC = core::stringc(c);

		Marshal::FreeHGlobal(IntPtr(c));
		return strC;
	}

	static core::stringw StringToStringW(String^ s)
	{
		if (s == nullptr)
			return core::stringw();

		wchar_t* w = (wchar_t*)Marshal::StringToHGlobalUni(s).ToPointer();
		core::stringw strW = core::stringw(w);

		Marshal::FreeHGlobal(IntPtr(w));
		return strW;
	}

private:

	Lime() {}
};

} // end namespace IrrlichtLime