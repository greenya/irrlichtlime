#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public interface class IShaderConstant
{
	//may write a maximum of 16 bytes
	//returns the number of written bytes
	int GetData(float* data);
};

} // end namespace Video
} // end namespace IrrlichtLime