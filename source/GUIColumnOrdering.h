#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIColumnOrdering
{
	None = EGCO_NONE,
	Custom = EGCO_CUSTOM,
	Ascending = EGCO_ASCENDING,
	Descending = EGCO_DESCENDING,
	FlipAscendingDescending = EGCO_FLIP_ASCENDING_DESCENDING
};

} // end namespace GUI
} // end namespace IrrlichtLime