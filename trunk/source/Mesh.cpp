#include "stdafx.h"
#include "Mesh.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

Mesh::Mesh(scene::IMesh* mesh)
	: ReferenceCounted(mesh)
{
	LIME_ASSERT(mesh != nullptr);
	m_Mesh = mesh;
}

} // end namespace Scene
} // end namespace IrrlichtLime