#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class VertexType
{
	Standard = EVT_STANDARD,
	TTCoords = EVT_2TCOORDS,
	Tangents = EVT_TANGENTS
};

} // end namespace Video
} // end namespace IrrlichtLime