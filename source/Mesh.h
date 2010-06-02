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

	static Mesh^ Wrap(scene::IMesh* ref);
	Mesh(scene::IMesh* ref);

	scene::IMesh* m_Mesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime