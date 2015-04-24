#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class DriverType
{
	Null = EDT_NULL,
	Software = EDT_SOFTWARE,
	BurningsVideo = EDT_BURNINGSVIDEO,
	[Obsolete("The Direct3D8 driver doesn't exist anymore", false)]
	Direct3D8 = DEPRECATED_EDT_DIRECT3D8_NO_LONGER_EXISTS,
	Direct3D9 = EDT_DIRECT3D9,
	OpenGL = EDT_OPENGL
};

} // end namespace Video
} // end namespace IrrlichtLime