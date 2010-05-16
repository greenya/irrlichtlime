#pragma once

#include "stdafx.h"
#include "Mesh.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

Mesh::Mesh(scene::IMesh* mesh)
{
	LIME_ASSERT(mesh != nullptr);
	m_Mesh = mesh;
}

} // end namespace Scene
} // end namespace IrrlichtLime