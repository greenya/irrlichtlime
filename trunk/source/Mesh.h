#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class Mesh : ReferenceCounted
{
public:

internal:

	Mesh(scene::IMesh* mesh);

	scene::IMesh* m_Mesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime