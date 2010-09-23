#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class MaterialType
{
	Solid = EMT_SOLID,
	Solid2Layer = EMT_SOLID_2_LAYER,
	LightMap = EMT_LIGHTMAP,
	LightMapAdd = EMT_LIGHTMAP_ADD,
	LightMapM2 = EMT_LIGHTMAP_M2,
	LightMapM4 = EMT_LIGHTMAP_M4,
	LightMapLighting = EMT_LIGHTMAP_LIGHTING,
	LightMapLightingM2 = EMT_LIGHTMAP_LIGHTING_M2,
	LightMapLightingM4 = EMT_LIGHTMAP_LIGHTING_M4,
	DetailMap = EMT_DETAIL_MAP,
	SphereMap = EMT_SPHERE_MAP,
	Reflection2Layer = EMT_REFLECTION_2_LAYER,
	TransparentAddColor = EMT_TRANSPARENT_ADD_COLOR,
	TransparentAlphaChannel = EMT_TRANSPARENT_ALPHA_CHANNEL,
	TransparentAlphaChannelRef = EMT_TRANSPARENT_ALPHA_CHANNEL_REF,
	TransparentVertexAlpha = EMT_TRANSPARENT_VERTEX_ALPHA,
	TransparentReflection2Layer = EMT_TRANSPARENT_REFLECTION_2_LAYER,
	NormalMapSolid = EMT_NORMAL_MAP_SOLID,
	NormalMapTransparentAddColor = EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR,
	NormalMapTransparentVertexAlpha = EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA,
	ParallaxMapSolid = EMT_PARALLAX_MAP_SOLID,
	ParallaxMapTransparentAddColor = EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR,
	ParallaxMapTransparentVertexAlpha = EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA,
	OneTextureBlend = EMT_ONETEXTURE_BLEND
};

} // end namespace Video
} // end namespace IrrlichtLime