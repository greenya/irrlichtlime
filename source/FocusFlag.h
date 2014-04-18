#pragma once
#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

[Flags]
public enum class FocusFlag
{
	SetOnLMouseDown = EFF_SET_ON_LMOUSE_DOWN,
	SetOnRMouseDown = EFF_SET_ON_RMOUSE_DOWN,
	SetOnMouseOver = EFF_SET_ON_MOUSE_OVER,
	SetOnTab = EFF_SET_ON_TAB,
	CanFocusDisabled = EFF_CAN_FOCUS_DISABLED
};

} // end namespace GUI
} // end namespace IrrlichtLime