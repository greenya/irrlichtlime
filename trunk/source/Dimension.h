#pragma once

#if defined(_REFCLASS_) || defined(_WRAPCLASS_) || defined(_WRAPTYPE_)
#error _REFCLASS_, _WRAPCLASS_ and _WRAPTYPE_ must be undefined for this file to process.
#endif

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Core {

// this type currently used only in GUIImageList.ImageSize,
// maybe remove it and use "u" version instead.
#define _REFCLASS_ Dimension2Di
#define _WRAPCLASS_ core::dimension2di
#define _WRAPTYPE_ int
#include "Dimension2D_template.h"
#undef _WRAPTYPE_
#undef _WRAPCLASS_
#undef _REFCLASS_

#define _REFCLASS_ Dimension2Du
#define _WRAPCLASS_ core::dimension2du
#define _WRAPTYPE_ unsigned int
#include "Dimension2D_template.h"
#undef _WRAPTYPE_
#undef _WRAPCLASS_
#undef _REFCLASS_

#define _REFCLASS_ Dimension2Df
#define _WRAPCLASS_ core::dimension2df
#define _WRAPTYPE_ float
#include "Dimension2D_template.h"
#undef _WRAPTYPE_
#undef _WRAPCLASS_
#undef _REFCLASS_

} // end namespace Core
} // end namespace IrrlichtLime