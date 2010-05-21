#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ColorMaterial
{
	None = ECM_NONE,
	Diffuse = ECM_DIFFUSE,
	Ambient = ECM_AMBIENT,
	Emissive = ECM_EMISSIVE,
	Specular = ECM_SPECULAR,
	DiffuseAndAmbient = ECM_DIFFUSE_AND_AMBIENT
};

} // end namespace Video
} // end namespace IrrlichtLime