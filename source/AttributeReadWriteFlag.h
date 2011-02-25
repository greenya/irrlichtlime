#pragma once
#include "stdafx.h"

using namespace irr;
using namespace io;
using namespace System;

namespace IrrlichtLime {
namespace IO {

[Flags]
public enum class AttributeReadWriteFlag
{
	ForFile = EARWF_FOR_FILE,
	ForEditor = EARWF_FOR_EDITOR,
	UseRelativePaths = EARWF_USE_RELATIVE_PATHS
};

} // end namespace IO
} // end namespace IrrlichtLime