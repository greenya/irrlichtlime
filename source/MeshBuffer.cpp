#pragma once

#include "stdafx.h"
#include "MeshBuffer.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshBuffer::MeshBuffer(scene::IMeshBuffer* meshBuffer)
{
	LIME_ASSERT(meshBuffer != nullptr);
	m_MeshBuffer = meshBuffer;
}

} // end namespace Scene
} // end namespace IrrlichtLime