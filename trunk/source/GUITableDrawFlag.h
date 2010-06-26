#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

[Flags]
public enum class GUITableDrawFlag
{
	Rows = EGTDF_ROWS,
	Columns = EGTDF_COLUMNS,
	ActiveRow = EGTDF_ACTIVE_ROW
};

} // end namespace GUI
} // end namespace IrrlichtLime