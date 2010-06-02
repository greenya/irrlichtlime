#include "stdafx.h"
#include "Mesh.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

Mesh^ Mesh::Wrap(scene::IMesh* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew Mesh(ref);
}

Mesh::Mesh(scene::IMesh* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_Mesh = ref;
}

} // end namespace Scene
} // end namespace IrrlichtLime