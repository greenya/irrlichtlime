#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class MeshBuffer : ReferenceCounted
{
public:

internal:

	MeshBuffer(scene::IMeshBuffer* ref);

	scene::IMeshBuffer* m_MeshBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime