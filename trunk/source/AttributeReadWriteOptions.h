#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace IO {

// !!! Why do we not use Lime::NativeValue here? That is why:
//
//	void AttributeReadWriteOptions::Filename::set(String^ value)
//	{
//		// !!! i don't like it! Filename is not stringc but only c8* !!!
//		// !!! returned stringc by Lime::StringToStringC() going to be destroyed after this method ends !!!
//		// TODO: maybe remove this method or even all the AttributeReadWriteOptions class, its used only in de/serialization
//		// and the pointer only required on this class, so maybe design own class and use it, and only when needed create internal
//		// io::SAttributeReadWriteOptions and pass to Irrlicht? Maybe!
//		m_NativeValue->Filename = Lime::StringToStringC(value).c_str();
//	}
//
// So i decided to don't hesitate and i used ordinary managed struct-like class, because every usage of
// io::SAttributeReadWriteOptions in Irrlicht is just an input arg, so Irrlicht internally only reads it.
// We are going to prepare (convert) each time when we need our class to io::SAttributeReadWriteOptions.
// Only this way we can guarantee that memory won't leak.

public ref class AttributeReadWriteOptions
{
public:

	String^ Filename;
	AttributeReadWriteFlag Flags;

	AttributeReadWriteOptions(AttributeReadWriteFlag flags, String^ filename)
		: Flags(flags)
		, Filename(filename) {}

	AttributeReadWriteOptions(AttributeReadWriteFlag flags)
		: Flags(flags)
		, Filename(nullptr) {}

	AttributeReadWriteOptions()
		: Flags((AttributeReadWriteFlag)0)
		, Filename(nullptr) {}

	virtual String^ ToString() override
	{
		return String::Format("AttributeReadWriteOptions: Flags={0}; Filename={1}", Flags, Filename);
	}

internal:

	// Allocates io::SAttributeReadWriteOptions and returns pointer.
	// Note: Free_SAttributeReadWriteOptions() must be called for returned pointer after all.
	io::SAttributeReadWriteOptions* Allocate_SAttributeReadWriteOptions()
	{
		io::SAttributeReadWriteOptions* o = new io::SAttributeReadWriteOptions();
		
		o->Flags = (io::E_ATTRIBUTE_READ_WRITE_FLAGS)Flags;
		o->Filename = nullptr;

		if (!String::IsNullOrEmpty(Filename))
		{
			int s = Filename->Length + 1;
			o->Filename = new c8[s];

			core::stringc c = Lime::StringToStringC(Filename);
			LIME_ASSERT(s == c.size() + 1);

			strcpy_s((c8*)o->Filename, s, c.c_str());
		}

		return o;
	}

	// Frees io::SAttributeReadWriteOptions pointer, previously allocated by Allocate_SAttributeReadWriteOptions().
	void Free_SAttributeReadWriteOptions(io::SAttributeReadWriteOptions* o)
	{
		LIME_ASSERT(o != nullptr);

		if (o->Filename != nullptr)
			delete o->Filename;

		delete o;
	}
};

} // end namespace IO
} // end namespace IrrlichtLime