#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

[Flags]
public enum class GUIMessageBoxFlag
{
	OK = EMBF_OK,
	Cancel = EMBF_CANCEL,
	Yes = EMBF_YES,
	No = EMBF_NO
};

} // end namespace GUI
} // end namespace IrrlichtLime