#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public interface class IVertex3D
{
	property VertexType Type { VertexType get(); }
	operator video::S3DVertex();
};


[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Vertex3D : IVertex3D
{

#define _REFCLASS_ Vertex3D
#define _WRAPCLASS_ video::S3DVertex
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	Vertex3D(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv)
	{
	}

	Vertex3D(float x, float y, float z, float nx, float ny, float nz, Video::Color c)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c)
	{
	}

	Vertex3D(float x, float y, float z, float nx, float ny, float nz)
		: Position(x, y, z), Normal(nx, ny, nz)
	{
	}

	Vertex3D(float x, float y, float z)
		: Position(x, y, z)
	{
	}

	Vertex3D(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords)
	{
	}

	Vertex3D(Vector3Df pos, Vector3Df normal, Video::Color color)
		: Position(pos), Normal(normal), Color(color)
	{
	}

	Vertex3D(Vector3Df pos, Vector3Df normal)
		: Position(pos), Normal(normal)
	{
	}

	Vertex3D(Vector3Df pos)
		: Position(pos)
	{
	}

	Vertex3D GetInterpolated(Vertex3D other, float d)
	{
		LIME_ASSERT(d >= 0.0f && d <= 1.0f);
		return Vertex3D(Position.GetInterpolated(other.Position, d),
				Normal.GetInterpolated(other.Normal, d),
				Color.GetInterpolated(other.Color, d),
				TCoords.GetInterpolated(other.TCoords, d));
	}

	property VertexType Type
	{
		virtual VertexType get() { return VertexType::Standard; } 
	}

	virtual operator video::S3DVertex()
	{
		return S3DVertex(Position.ToNative(), Normal.ToNative(), Color.ToNative(), TCoords.ToNative());
	}

internal:

	Vertex3D(const S3DVertex& other)
	{
		Position = Vector3Df(other.Pos);
		Normal = Vector3Df(other.Normal);
		Color = Video::Color(other.Color);
		TCoords = Vector2Df(other.TCoords);
	}

	video::S3DVertex ToNative()
	{
		return (S3DVertex)*this;
	}

};

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Vertex3DTTCoords : IVertex3D
{

#define _REFCLASS_ Vertex3DTTCoords
#define _WRAPCLASS_ video::S3DVertex2TCoords
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	Vector2Df TCoords2;

	Vertex3DTTCoords(Vertex3D other)
	{
		Position = other.Position;
		Normal = other.Normal;
		Color = other.Color;
		TCoords = other.TCoords;
	}

	Vertex3DTTCoords(float x, float y, float z, Video::Color c, float tu, float tv, float tu2, float tv2)
		: Position(x, y, z), Color(c), TCoords(tu, tv), TCoords2(tu2, tv2)
	{
	}

	Vertex3DTTCoords(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv, float tu2, float tv2)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv), TCoords2(tu2, tv2)
	{
	}

	Vertex3DTTCoords(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv)
	{
	}

	Vertex3DTTCoords(Vector3Df pos, Video::Color color, Vector2Df tcoords, Vector2Df tcoords2)
		: Position(pos), Color(color), TCoords(tcoords), TCoords2(tcoords2)
	{
	}

	Vertex3DTTCoords(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords, Vector2Df tcoords2)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords), TCoords2(tcoords2)
	{
	}

	Vertex3DTTCoords(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords)
	{
	}

		
	Vertex3DTTCoords GetInterpolated(Vertex3DTTCoords other, float d)
	{
		LIME_ASSERT(d >= 0.0f && d <= 1.0f);
		return Vertex3DTTCoords(Position.GetInterpolated(other.Position, d),
				Normal.GetInterpolated(other.Normal, d),
				Color.GetInterpolated(other.Color, d),
				TCoords.GetInterpolated(other.TCoords, d),
				TCoords2.GetInterpolated(other.TCoords2, d));
	}

	property VertexType Type
	{
		virtual VertexType get() { return VertexType::TTCoords; }
	}

	virtual operator video::S3DVertex()
	{
		return S3DVertex2TCoords(Position.ToNative(), Normal.ToNative(), Color.ToNative(), TCoords.ToNative(), TCoords2.ToNative());
	}

internal:

	Vertex3DTTCoords(const S3DVertex2TCoords& other)
	{
		Position = Vector3Df(other.Pos);
		Normal = Vector3Df(other.Normal);
		Color = Video::Color(other.Color);
		TCoords = Vector2Df(other.TCoords);
		TCoords2 = Vector2Df(other.TCoords2);
	}

	video::S3DVertex2TCoords ToNative()
	{
		return S3DVertex2TCoords(Position.ToNative(), Normal.ToNative(), Color.ToNative(), TCoords.ToNative(), TCoords2.ToNative());
	}
};

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class Vertex3DTangents : IVertex3D
{

#define _REFCLASS_ Vertex3DTangents
#define _WRAPCLASS_ video::S3DVertexTangents
#include "Vertex_template.h"
#undef _WRAPCLASS_
#undef _REFCLASS_

public:

	Vector3Df Tangent;
	Vector3Df Binormal;

	Vertex3DTangents(Vertex3D other)
	{
		Position = other.Position;
		Normal = other.Normal;
		Color = other.Color;
		TCoords = other.TCoords;
	}

	Vertex3DTangents(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv, float tanx, float tany, float tanz, float binx, float biny, float binz)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv), Tangent(tanx, tany, tanz), Binormal(binx, biny, binz)
	{
	}

	Vertex3DTangents(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv, float tanx, float tany, float tanz)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv), Tangent(tanx, tany, tanz)
	{
	}

	Vertex3DTangents(float x, float y, float z, float nx, float ny, float nz, Video::Color c, float tu, float tv)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv)
	{
	}

	Vertex3DTangents(float x, float y, float z, float nx, float ny, float nz, Video::Color c)
		: Position(x, y, z), Normal(nx, ny, nz), Color(c)
	{
	}

	Vertex3DTangents(float x, float y, float z, float nx, float ny, float nz)
		: Position(x, y, z), Normal(nx, ny, nz)
	{
	}

	Vertex3DTangents(float x, float y, float z)
		: Position(x, y, z)
	{
	}

	Vertex3DTangents(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords, Vector3Df tangent, Vector3Df binormal)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords), Tangent(tangent), Binormal(binormal)
	{
	}

	Vertex3DTangents(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords, Vector3Df tangent)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords), Tangent(tangent)
	{
	}

	Vertex3DTangents(Vector3Df pos, Vector3Df normal, Video::Color color, Vector2Df tcoords)
		: Position(pos), Normal(normal), Color(color), TCoords(tcoords)
	{
	}

	Vertex3DTangents GetInterpolated(Vertex3DTangents other, float d)
	{
		LIME_ASSERT(d >= 0.0f && d <= 1.0f);
		return Vertex3DTangents(Position.GetInterpolated(other.Position, d),
				Normal.GetInterpolated(other.Normal, d),
				Color.GetInterpolated(other.Color, d),
				TCoords.GetInterpolated(other.TCoords, d),
				Tangent.GetInterpolated(other.Tangent, d),
				Binormal.GetInterpolated(other.Binormal, d));
	}

	property VertexType Type
	{
		virtual VertexType get() { return VertexType::Tangents; }
	}

	virtual operator video::S3DVertex()
	{
		return S3DVertexTangents(Position.ToNative(), Normal.ToNative(), Color.ToNative(), TCoords.ToNative(), Tangent.ToNative(), Binormal.ToNative());
	}

internal:

	Vertex3DTangents(const S3DVertexTangents& other)
	{
		Position = Vector3Df(other.Pos);
		Normal = Vector3Df(other.Normal);
		Color = Video::Color(other.Color);
		TCoords = Vector2Df(other.TCoords);
		Tangent = Vector3Df(other.Tangent);
		Binormal = Vector3Df(other.Binormal);
	}

	video::S3DVertexTangents ToNative()
	{
		return S3DVertexTangents(Position.ToNative(), Normal.ToNative(), Color.ToNative(), TCoords.ToNative(), Tangent.ToNative(), Binormal.ToNative());
	}
};

} // end namespace Video
} // end namespace IrrlichtLime