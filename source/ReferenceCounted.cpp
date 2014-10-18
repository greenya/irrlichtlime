#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

bool ReferenceCounted::operator == (ReferenceCounted^ v1, ReferenceCounted^ v2)
{
	bool v1n = Object::ReferenceEquals(v1, nullptr);
	bool v2n = Object::ReferenceEquals(v2, nullptr);

	if (v1n && v2n)
		return true;

	if (v1n || v2n)
		return false;

	return v1->m_ReferenceCounted == v2->m_ReferenceCounted;
}

bool ReferenceCounted::operator != (ReferenceCounted^ v1, ReferenceCounted^ v2)
{
	return !(v1 == v2);
}

bool ReferenceCounted::Equals(ReferenceCounted^ other)
{
	return (this == other);
}

bool ReferenceCounted::Equals(Object^ other)
{
	if (other == nullptr)
		return false;
	ReferenceCounted^ otherCasted = dynamic_cast<ReferenceCounted^>(other);
	if (otherCasted != nullptr)
		return Equals(otherCasted);
	else
		return false;
}

int ReferenceCounted::GetHashCode()
{
	return (int)m_ReferenceCounted;	//returns the first four bytes of the pointer
}

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