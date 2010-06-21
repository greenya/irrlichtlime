#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

public ref class AttributeExchangingObject : ReferenceCounted
{
public:

	// void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0)
	// void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)

internal:

	AttributeExchangingObject(io::IAttributeExchangingObject* ref_or_null);
	void setAttributeExchangingObject(io::IAttributeExchangingObject* ref);

	io::IAttributeExchangingObject* m_AttributeExchangingObject;
};

} // end namespace IO
} // end namespace IrrlichtLime