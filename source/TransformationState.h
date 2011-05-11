#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class TransformationState
{
	View = ETS_VIEW,
	World = ETS_WORLD,
	Projection = ETS_PROJECTION,
	Texture0 = ETS_TEXTURE_0,
	Texture1 = ETS_TEXTURE_1,
	Texture2 = ETS_TEXTURE_2,
	Texture3 = ETS_TEXTURE_3,
#if _IRR_MATERIAL_MAX_TEXTURES_>4
	Texture4 = ETS_TEXTURE_4,
#if _IRR_MATERIAL_MAX_TEXTURES_>5
	Texture5 = ETS_TEXTURE_5,
#if _IRR_MATERIAL_MAX_TEXTURES_>6
	Texture6 = ETS_TEXTURE_6,
#if _IRR_MATERIAL_MAX_TEXTURES_>7
	Texture7 = ETS_TEXTURE_7,
#endif
#endif
#endif
#endif
};

} // end namespace Video
} // end namespace IrrlichtLime