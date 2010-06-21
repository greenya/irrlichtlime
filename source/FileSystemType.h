#pragma once

#include "stdafx.h"

using namespace irr;
using namespace io;
using namespace System;

namespace IrrlichtLime {
namespace IO {

public enum class FileSystemType
{
	Native = FILESYSTEM_NATIVE,
	Virtual = FILESYSTEM_VIRTUAL
};

} // end namespace IO
} // end namespace IrrlichtLime