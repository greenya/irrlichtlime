#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class VideoDriverFeature
{
	RenderToTarget = EVDF_RENDER_TO_TARGET,
	HardwareTL = EVDF_HARDWARE_TL,
	Multitexture = EVDF_MULTITEXTURE,
	BilinearFilter = EVDF_BILINEAR_FILTER,
	Mipmap = EVDF_MIP_MAP,
	MipmapAutoUpdate = EVDF_MIP_MAP_AUTO_UPDATE,
	StencilBuffer = EVDF_STENCIL_BUFFER,
	VertexShader_1_1 = EVDF_VERTEX_SHADER_1_1,
	VertexShader_2_0 = EVDF_VERTEX_SHADER_2_0,
	VertexShader_3_0 = EVDF_VERTEX_SHADER_3_0,
	PixelShader_1_1 = EVDF_PIXEL_SHADER_1_1,
	PixelShader_1_2 = EVDF_PIXEL_SHADER_1_2,
	PixelShader_1_3 = EVDF_PIXEL_SHADER_1_3,
	PixelShader_1_4 = EVDF_PIXEL_SHADER_1_4,
	PixelShader_2_0 = EVDF_PIXEL_SHADER_2_0,
	PixelShader_3_0 = EVDF_PIXEL_SHADER_3_0,
	ARB_VertexProgram_1 = EVDF_ARB_VERTEX_PROGRAM_1,
	ARB_FragmentProgram_1 = EVDF_ARB_FRAGMENT_PROGRAM_1,
	ARB_GLSL = EVDF_ARB_GLSL,
	HLSL = EVDF_HLSL,
	TextureNonSquare = EVDF_TEXTURE_NSQUARE,
	TextureNonPOT = EVDF_TEXTURE_NPOT,
	FrameBufferObject = EVDF_FRAMEBUFFER_OBJECT,
	VertexBufferObject = EVDF_VERTEX_BUFFER_OBJECT,
	AlphaToCoverage = EVDF_ALPHA_TO_COVERAGE,
	ColorMask = EVDF_COLOR_MASK,
	MultipleRenderTargets = EVDF_MULTIPLE_RENDER_TARGETS,
	MRT_Blend = EVDF_MRT_BLEND,
	MRT_ColorMask = EVDF_MRT_COLOR_MASK,
	MRT_BlendFunc = EVDF_MRT_BLEND_FUNC,
	GeomertyShader = EVDF_GEOMETRY_SHADER,
	OcclusionQuery = EVDF_OCCLUSION_QUERY
};

} // end namespace Video
} // end namespace IrrlichtLime