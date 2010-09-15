#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class Vertex3D : Lime::NativeValue<video::S3DVertex>
{

#define _REFCLASS_ Vertex3D
#define _WRAPCLASS_ video::S3DVertex
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	Vertex3D(float x, float y, float z, float nx, float ny, float nz, Video::Color^ c, float tu, float tv)
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		LIME_ASSERT(c != nullptr);

		m_NativeValue = new video::S3DVertex(
			x, y, z,
			nx, ny, nz,
			*c->m_NativeValue,
			tu, tv);
	}

	Vertex3D(Vector3Df^ pos, Vector3Df^ normal, Video::Color^ color, Vector2Df^ tcoords)
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		LIME_ASSERT(pos != nullptr);
		LIME_ASSERT(normal != nullptr);
		LIME_ASSERT(color != nullptr);
		LIME_ASSERT(tcoords != nullptr);

		m_NativeValue = new video::S3DVertex(
			*pos->m_NativeValue,
			*normal->m_NativeValue,
			*color->m_NativeValue,
			*tcoords->m_NativeValue);
	}
};

public ref class Vertex3DTTCoords : Lime::NativeValue<video::S3DVertex2TCoords>
{

#define _REFCLASS_ Vertex3DTTCoords
#define _WRAPCLASS_ video::S3DVertex2TCoords
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	Vertex3DTTCoords(float x, float y, float z, Video::Color^ c, float tu, float tv, float tu2, float tv2)
		: Lime::NativeValue<video::S3DVertex2TCoords>(true)
	{
		LIME_ASSERT(c != nullptr);

		m_NativeValue = new video::S3DVertex2TCoords(
			x, y, z,
			*c->m_NativeValue,
			tu, tv,
			tu2, tv2);
	}

	Vertex3DTTCoords(Vector3Df^ pos, Video::Color^ color, Vector2Df^ tcoords, Vector2Df^ tcoords2)
		: Lime::NativeValue<video::S3DVertex2TCoords>(true)
	{
		LIME_ASSERT(pos != nullptr);
		LIME_ASSERT(color != nullptr);
		LIME_ASSERT(tcoords != nullptr);
		LIME_ASSERT(tcoords2 != nullptr);

		m_NativeValue = new video::S3DVertex2TCoords(
			*pos->m_NativeValue,
			*color->m_NativeValue,
			*tcoords->m_NativeValue,
			*tcoords2->m_NativeValue);
	}
};

public ref class Vertex3DTangents : Lime::NativeValue<video::S3DVertexTangents>
{

#define _REFCLASS_ Vertex3DTangents
#define _WRAPCLASS_ video::S3DVertexTangents
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	// ...
};

} // end namespace Video
} // end namespace IrrlichtLime