#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class MeshBuffer
{
public:

internal:

	MeshBuffer(scene::IMeshBuffer* meshBuffer);

	scene::IMeshBuffer* m_MeshBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime