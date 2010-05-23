#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

AttributeExchangingObject::AttributeExchangingObject(io::IAttributeExchangingObject* attributeExchangingObject_or_null)
	: ReferenceCounted(attributeExchangingObject_or_null)
{
	m_AttributeExchangingObject = attributeExchangingObject_or_null;
}

void AttributeExchangingObject::setAttributeExchangingObject(io::IAttributeExchangingObject* attributeExchangingObject)
{
	LIME_ASSERT(attributeExchangingObject != nullptr);
	m_ReferenceCounted = attributeExchangingObject;
	m_AttributeExchangingObject = attributeExchangingObject;
}

} // end namespace IO
} // end namespace IrrlichtLime