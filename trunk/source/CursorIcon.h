#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class CursorIcon
{
	Normal = ECI_NORMAL,
	Cross = ECI_CROSS,
	Hand = ECI_HAND,
	Help = ECI_HELP,
	IBeam = ECI_IBEAM,
	No = ECI_NO,
	Wait = ECI_WAIT,
	SizeAll = ECI_SIZEALL,
	SizeNESW = ECI_SIZENESW,
	SizeNWSE = ECI_SIZENWSE,
	SizeNS = ECI_SIZENS,
	SizeWE = ECI_SIZEWE,
	Up = ECI_UP,
};

} // end namespace GUI
} // end namespace IrrlichtLime
