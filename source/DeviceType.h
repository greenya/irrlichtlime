#pragma once
#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public enum class DeviceType
{
	Win32 = EIDT_WIN32,
	WinCE = EIDT_WINCE,
	X11 = EIDT_X11,
	OSX = EIDT_OSX,
	SDL = EIDT_SDL,
	FrameBuffer = EIDT_FRAMEBUFFER,
	Console = EIDT_CONSOLE,
	Best = EIDT_BEST
};

} // end namespace IrrlichtLime