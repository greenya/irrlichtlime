#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

[Flags]
public enum class GUISpinBoxValidation
{
	Never = EGUI_SBV_NEVER,
	Change = EGUI_SBV_CHANGE,
	Enter = EGUI_SBV_ENTER,
	LoseFocus = EGUI_SBV_LOSE_FOCUS
};

} // end namespace GUI
} // end namespace IrrlichtLime