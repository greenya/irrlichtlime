#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

public enum class LogLevel
{
	Debug = ELL_DEBUG,
	Information = ELL_INFORMATION,
	Warning = ELL_WARNING,
	Error = ELL_ERROR,
	None = ELL_NONE
};

} // end namespace IrrlichtLime