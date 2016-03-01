#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class ColorFormat
{
	A1R5G5B5 = ECF_A1R5G5B5,
	R5G6B5 = ECF_R5G6B5,
	R8G8B8 = ECF_R8G8B8,
	A8R8G8B8 = ECF_A8R8G8B8,
	DXT1 = ECF_DXT1,
	DXT2 = ECF_DXT2,
	DXT3 = ECF_DXT3,
	DXT4 = ECF_DXT4,
	DXT5 = ECF_DXT5,
	PVRTC_RGB2 = ECF_PVRTC_RGB2,
	PVRTC_ARGB2 = ECF_PVRTC_ARGB2,
	PVRTC_RGB4 = ECF_PVRTC_RGB4,
	PVRTC_ARGB4 = ECF_PVRTC_ARGB4,
	PVRTC2_ARGB2 = ECF_PVRTC2_ARGB2,
	PVRTC2_ARGB4 = ECF_PVRTC2_ARGB4,
	ETC1 = ECF_ETC1,
	ETC2_RGB = ECF_ETC2_RGB,
	ETC2_ARGB = ECF_ETC2_ARGB,
	D16 = ECF_D16,
	D32 = ECF_D32,
	D24S8 = ECF_D24S8,
	R8 = ECF_R8,
	R8G8 = ECF_R8G8,
	R16 = ECF_R16,
	R16G16 = ECF_R16G16,
	R16F = ECF_R16F,
	G16R16F = ECF_G16R16F,
	A16B16G16R16F = ECF_A16B16G16R16F,
	R32F = ECF_R32F,
	G32R32F = ECF_G32R32F,
	A32B32G32R32F = ECF_A32B32G32R32F,
	Unknown = ECF_UNKNOWN
};

} // end namespace Video
} // end namespace IrrlichtLime