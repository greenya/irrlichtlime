#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public enum class EventType : unsigned int
{
	GUI = EET_GUI_EVENT,
	Mouse = EET_MOUSE_INPUT_EVENT,
	Key = EET_KEY_INPUT_EVENT,
	Joystick = EET_JOYSTICK_INPUT_EVENT,
	Log = EET_LOG_TEXT_EVENT,
	User = EET_USER_EVENT
};

} // end namespace IrrlichtLime