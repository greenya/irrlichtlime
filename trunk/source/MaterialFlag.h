#pragma once
#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class MaterialFlag
{
	Wireframe = EMF_WIREFRAME,
	PointCloud = EMF_POINTCLOUD,
	GouraudShading = EMF_GOURAUD_SHADING,
	Lighting = EMF_LIGHTING,
	ZBuffer = EMF_ZBUFFER,
	ZWrite = EMF_ZWRITE_ENABLE,
	BackFaceCulling = EMF_BACK_FACE_CULLING,
	FrontFaceCulling = EMF_FRONT_FACE_CULLING,
	BilinearFilter = EMF_BILINEAR_FILTER,
	TrilinearFilter = EMF_TRILINEAR_FILTER,
	AnisotropicFilter = EMF_ANISOTROPIC_FILTER,
	Fog = EMF_FOG_ENABLE,
	NormalizeNormals = EMF_NORMALIZE_NORMALS,
	TextureWrap = EMF_TEXTURE_WRAP,
	AntiAliasing = EMF_ANTI_ALIASING,
	ColorMask = EMF_COLOR_MASK,
	ColorMaterial = EMF_COLOR_MATERIAL,
	Mipmaps = EMF_USE_MIP_MAPS
};

} // end namespace Video
} // end namespace IrrlichtLime