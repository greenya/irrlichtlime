#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class VertexPrimitive
{
public:

	VertexPrimitive(Scene::PrimitiveType primitiveType, Video::VertexType vertexType, int vertexCount, Video::IndexType indexType, int indexCount);

	void Draw(VideoDriver^ driver);
	void Draw(VideoDriver^ driver, int overridePrimitiveCount);
	void Draw(VideoDriver^ driver, int overridePrimitiveCount, Scene::PrimitiveType overridePrimitiveType);

	void Drop();

	int GetIndex(int i);
	void SetIndex(int i, int index);
	void SetIndicesSequence();

	Object^ GetVertex(int i);
	void SetVertex(int i, Object^ vertex);
	void SetVertexColor(int i, Color^ color);
	void SetVertexColor(int i, unsigned int argb);
	void SetVertexNormal(int i, Vector3Df^ normal);
	void SetVertexNormal(int i, float x, float y, float z);
	void SetVertexPosition(int i, Vector3Df^ position);
	void SetVertexPosition(int i, float x, float y, float z);
	void SetVertexTCoords(int i, Vector2Df^ tcoords);
	void SetVertexTCoords(int i, float u, float v);

	property int IndexCount { int get(); }
	property Video::IndexType IndexType { Video::IndexType get(); }
	property int PrimitiveCount { int get(); }
	property Scene::PrimitiveType PrimitiveType { Scene::PrimitiveType get(); }
	property unsigned long TotalBytesAllocated { unsigned long get(); }
	property int VertexCount { int get(); }
	property Video::VertexType VertexType { Video::VertexType get(); }

	virtual String^ ToString() override;

private:

	scene::E_PRIMITIVE_TYPE m_primitiveType;
	int m_primitiveCount;

	video::E_VERTEX_TYPE m_vertexType;
	int m_vertexCount;
	void* m_vertices;

	video::E_INDEX_TYPE m_indexType;
	int m_indexCount;
	void* m_indices;
};

} // end namespace Video
} // end namespace IrrlichtLime