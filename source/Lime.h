#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace IrrlichtLime
{
	public ref class Lime
	{
	public:

		static property String^ Version
		{
			String^ get()
			{
				String^ s = Assembly::GetAssembly(Lime::typeid)->GetName()->Version->ToString();
#if _DEBUG
				s += " DEBUG";
#endif
				return s;
			}
		}

		static core::stringc StringToStringC(String^ s)
		{
			char* c = (char*)Marshal::StringToHGlobalAnsi(s).ToPointer();
			core::stringc strC = core::stringc(c);

			Marshal::FreeHGlobal(IntPtr(c));
			return strC;
		}

		static core::stringw StringToStringW(String^ s)
		{
			wchar_t* w = (wchar_t*)Marshal::StringToHGlobalUni(s).ToPointer();
			core::stringw strW = core::stringw(w);

			Marshal::FreeHGlobal(IntPtr(w));
			return strW;
		}

		ref class NativeObject
		{
			public:

				~NativeObject()
				{
					this->!NativeObject();
				}

				!NativeObject()
				{
					if (m_NativeObject != nullptr)
					{
						delete m_NativeObject;
						m_NativeObject = nullptr;
					}
				}

			internal:

				void* m_NativeObject;

				NativeObject()
				{
					// nothing;
				}
		};
	};
}