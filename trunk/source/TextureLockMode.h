#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class TextureLockMode
{
	ReadWrite = ETLM_READ_WRITE,
	ReadOnly = ETLM_READ_ONLY,
	WriteOnly = ETLM_WRITE_ONLY
};

} // end namespace Video
} // end namespace IrrlichtLime