#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIFontType
{
	Bitmap = EGFT_BITMAP,
	Vector = EGFT_VECTOR,
	OS = EGFT_OS,
	Custom = EGFT_CUSTOM
};

} // end namespace GUI
} // end namespace IrrlichtLime