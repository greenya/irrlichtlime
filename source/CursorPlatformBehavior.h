#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class CursorPlatformBehavior
{
	None = ECPB_NONE,
	X11CacheUpdates = ECPB_X11_CACHE_UPDATES
};

} // end namespace GUI
} // end namespace IrrlichtLime