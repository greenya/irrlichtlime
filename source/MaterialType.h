#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class MaterialType : unsigned int
{
	Solid = EMT_SOLID,
	Solid2Layer = EMT_SOLID_2_LAYER,
	Lightmap = EMT_LIGHTMAP,
	LightmapAdd = EMT_LIGHTMAP_ADD,
	LightmapM2 = EMT_LIGHTMAP_M2,
	LightmapM4 = EMT_LIGHTMAP_M4,
	LightmapLighting = EMT_LIGHTMAP_LIGHTING,
	LightmapLightingM2 = EMT_LIGHTMAP_LIGHTING_M2,
	LightmapLightingM4 = EMT_LIGHTMAP_LIGHTING_M4,
	Detailmap = EMT_DETAIL_MAP,
	Spheremap = EMT_SPHERE_MAP,
	Reflection2Layer = EMT_REFLECTION_2_LAYER,
	TransparentAddColor = EMT_TRANSPARENT_ADD_COLOR,
	TransparentAlphaChannel = EMT_TRANSPARENT_ALPHA_CHANNEL,
	TransparentAlphaChannelRef = EMT_TRANSPARENT_ALPHA_CHANNEL_REF,
	TransparentVertexAlpha = EMT_TRANSPARENT_VERTEX_ALPHA,
	TransparentReflection2Layer = EMT_TRANSPARENT_REFLECTION_2_LAYER,
	NormalmapSolid = EMT_NORMAL_MAP_SOLID,
	NormalmapTransparentAddColor = EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR,
	NormalmapTransparentVertexAlpha = EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA,
	ParallaxmapSolid = EMT_PARALLAX_MAP_SOLID,
	ParallaxmapTransparentAddColor = EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR,
	ParallaxmapTransparentVertexAlpha = EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA,
	OneTextureBlend = EMT_ONETEXTURE_BLEND
};

} // end namespace Video
} // end namespace IrrlichtLime