#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

AttributeExchangingObject::AttributeExchangingObject(io::IAttributeExchangingObject* ref_or_null)
	: ReferenceCounted(ref_or_null)
{
	m_AttributeExchangingObject = ref_or_null;
}

void AttributeExchangingObject::setAttributeExchangingObject(io::IAttributeExchangingObject* ref)
{
	LIME_ASSERT(ref != nullptr);

	m_ReferenceCounted = ref;
	m_AttributeExchangingObject = ref;
}

} // end namespace IO
} // end namespace IrrlichtLime