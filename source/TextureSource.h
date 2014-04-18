#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class TextureSource
{
	Unknown = ETS_UNKNOWN,
	FromCache = ETS_FROM_CACHE,
	FromFile = ETS_FROM_FILE
};

} // end namespace Video
} // end namespace IrrlichtLime

