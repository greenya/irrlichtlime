#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public enum class MouseEventType
{
	LeftDown = EMIE_LMOUSE_PRESSED_DOWN,
	RightDown = EMIE_RMOUSE_PRESSED_DOWN,
	MiddleDown = EMIE_MMOUSE_PRESSED_DOWN,
	LeftUp = EMIE_LMOUSE_LEFT_UP,
	RightUp = EMIE_RMOUSE_LEFT_UP,
	MiddleUp = EMIE_MMOUSE_LEFT_UP,
	Move = EMIE_MOUSE_MOVED,
	Wheel = EMIE_MOUSE_WHEEL,
	LeftDoubleClick = EMIE_LMOUSE_DOUBLE_CLICK,
	RightDoubleClick = EMIE_RMOUSE_DOUBLE_CLICK,
	MiddleDoubleClick = EMIE_MMOUSE_DOUBLE_CLICK,
	LeftTripleClick = EMIE_LMOUSE_TRIPLE_CLICK,
	RightTripleClick = EMIE_RMOUSE_TRIPLE_CLICK,
	MiddleTripleClick = EMIE_MMOUSE_TRIPLE_CLICK
};

} // end namespace IrrlichtLime