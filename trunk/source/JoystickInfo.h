#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public ref class JoystickInfo
{
public:

	enum class PovHatPresence
	{
		Present = SJoystickInfo::POV_HAT_PRESENT,
		Absent = SJoystickInfo::POV_HAT_ABSENT,
		Unknown = SJoystickInfo::POV_HAT_UNKNOWN
	};

	unsigned int AxisCount;
	unsigned int ButtonCount;
	unsigned __int8 Joystick;
	String^ Name;
	PovHatPresence PovHat;

internal:
	
	JoystickInfo(const SJoystickInfo& copy)
		: AxisCount(copy.Axes)
		, ButtonCount(copy.Buttons)
		, Joystick(copy.Joystick)
		, Name(gcnew String(copy.Name.c_str()))
		, PovHat((PovHatPresence)copy.PovHat) {}
};

} // end namespace IrrlichtLime