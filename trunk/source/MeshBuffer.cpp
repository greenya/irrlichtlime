#include "stdafx.h"
#include "MeshBuffer.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshBuffer::MeshBuffer(scene::IMeshBuffer* meshBuffer)
	: ReferenceCounted(meshBuffer)
{
	LIME_ASSERT(meshBuffer != nullptr);
	m_MeshBuffer = meshBuffer;
}

} // end namespace Scene
} // end namespace IrrlichtLime