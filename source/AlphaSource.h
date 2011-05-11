#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

[Flags]
public enum class AlphaSource
{
	None = EAS_NONE,
	VertexColor = EAS_VERTEX_COLOR,
	Texture = EAS_TEXTURE
};

} // end namespace Video
} // end namespace IrrlichtLime