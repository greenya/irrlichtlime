#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIContextMenuClose
{
	Ignore = ECMC_IGNORE,
	Remove = ECMC_REMOVE,
	Hide = ECMC_HIDE
};

} // end namespace GUI
} // end namespace IrrlichtLime