#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class JointUpdateOnRender
{
	None = EJUOR_NONE,
	Read = EJUOR_READ,
	Control = EJUOR_CONTROL
};

} // end namespace Scene
} // end namespace IrrlichtLime