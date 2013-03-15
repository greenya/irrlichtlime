#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class VertexPrimitive
{
public:

	VertexPrimitive(int vertexCount, int indexCount, Scene::PrimitiveType primitiveType);

	void Draw(VideoDriver^ driver);
	void Draw(VideoDriver^ driver, int overridePrimitiveCount);
	void Draw(VideoDriver^ driver, int overridePrimitiveCount, Scene::PrimitiveType overridePrimitiveType);

	void Drop();

	int GetIndex(int i);
	void SetIndex(int i, int index);

	Vertex3D^ GetVertex(int i);
	void SetVertex(int i, Vertex3D^ vertex);
	void SetVertexColor(int i, Color^ color);
	void SetVertexColor(int i, unsigned int argb);
	void SetVertexPosition(int i, Vector3Df^ position);
	void SetVertexPosition(int i, float x, float y, float z);

	property int IndexCount { int get(); }
	property Scene::PrimitiveType PrimitiveType { Scene::PrimitiveType get(); }
	property int VertexCount { int get(); }

	virtual String^ ToString() override;

private:

	scene::E_PRIMITIVE_TYPE m_primitiveType;
	int m_primitiveCount;

	video::S3DVertex* m_vertices;
	int m_vertexCount;

	u16* m_indices;
	int m_indexCount;
};

} // end namespace Video
} // end namespace IrrlichtLime