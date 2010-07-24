#pragma once

#include "stdafx.h"

using namespace irr;
using namespace io;
using namespace System;

namespace IrrlichtLime {
namespace IO {

public enum class FileArchiveType
{
	ZIP = EFAT_ZIP,
	GZIP = EFAT_GZIP,
	Folder = EFAT_FOLDER,
	PAK = EFAT_PAK,
	NPK = EFAT_NPK,
	TAR = EFAT_TAR,
	WAD = EFAT_WAD,
	Unknown = EFAT_UNKNOWN
};

} // end namespace IO
} // end namespace IrrlichtLime