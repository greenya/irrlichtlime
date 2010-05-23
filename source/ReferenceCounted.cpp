#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

ReferenceCounted::ReferenceCounted(irr::IReferenceCounted* referenceCounted_or_null)
{
	m_ReferenceCounted = referenceCounted_or_null;
}

bool ReferenceCounted::Drop()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	return m_ReferenceCounted->drop();
}

void ReferenceCounted::Grab()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	m_ReferenceCounted->grab();
}

String^ ReferenceCounted::DebugName::get()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	return gcnew String(m_ReferenceCounted->getDebugName());
}

int ReferenceCounted::ReferenceCount::get()
{
	LIME_ASSERT(m_ReferenceCounted != nullptr);
	return m_ReferenceCounted->getReferenceCount();
}

} // end namespace IrrlichtLime