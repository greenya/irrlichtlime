#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Video
{
	public enum class DriverType
	{
		Null = video::EDT_NULL,
		Software = video::EDT_SOFTWARE,
		BurningsVideo = video::EDT_BURNINGSVIDEO,
		Direct3D8 = video::EDT_DIRECT3D8,
		Direct3D9 = video::EDT_DIRECT3D9,
		OpenGL = video::EDT_OPENGL
	};
}
}