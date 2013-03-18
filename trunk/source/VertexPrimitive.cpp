#include "stdafx.h"
#include "VertexPrimitive.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

VertexPrimitive::VertexPrimitive(Scene::PrimitiveType primitiveType, Video::VertexType vertexType, int vertexCount, Video::IndexType indexType, int indexCount)
{
	LIME_ASSERT(vertexCount > 0);
	LIME_ASSERT(indexCount > 0);

	m_primitiveType = (scene::E_PRIMITIVE_TYPE)primitiveType;
	m_vertexType = (video::E_VERTEX_TYPE)vertexType;
	m_vertexCount = vertexCount;
	m_indexType = (video::E_INDEX_TYPE)indexType;
	m_indexCount = indexCount;

	m_primitiveCount = VideoDriver::calculatePrimitiveCount(indexCount, primitiveType);

	// allocate vertices

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		m_vertices = new video::S3DVertex[vertexCount];
		break;

	case video::EVT_2TCOORDS:
		m_vertices = new video::S3DVertex2TCoords[vertexCount];
		break;

	case video::EVT_TANGENTS:
		m_vertices = new video::S3DVertexTangents[vertexCount];
		break;

	default:
		LIME_ASSERT2(false, "Unexpected vertexType: " + vertexType.ToString());
		break;
	}

	// allocate indices

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		LIME_ASSERT(vertexCount <= 65536);
		m_indices = new u16[indexCount];
		break;

	case video::EIT_32BIT:
		m_indices = new u32[indexCount];
		break;

	default:
		LIME_ASSERT2(false, "Unexpected indexType: " + indexType.ToString());
		break;
	}
}

void VertexPrimitive::Draw(VideoDriver^ driver)
{
	LIME_ASSERT(driver != nullptr);
	LIME_ASSERT(m_primitiveCount > 0);
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(m_vertexCount > 0);
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(m_indexCount > 0);

	driver->m_VideoDriver->drawVertexPrimitiveList(
		m_vertices,
		m_vertexCount,
		m_indices,
		m_primitiveCount,
		m_vertexType,
		m_primitiveType,
		m_indexType);
}

void VertexPrimitive::Draw(VideoDriver^ driver, int overridePrimitiveCount)
{
	LIME_ASSERT(driver != nullptr);
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(m_vertexCount > 0);
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(m_indexCount > 0);

	if (overridePrimitiveCount < 1)
		return;

	LIME_ASSERT(m_primitiveCount > 0);
	LIME_ASSERT(overridePrimitiveCount <= m_primitiveCount);

	driver->m_VideoDriver->drawVertexPrimitiveList(
		m_vertices,
		m_vertexCount,
		m_indices,
		overridePrimitiveCount,
		m_vertexType,
		m_primitiveType,
		m_indexType);
}

void VertexPrimitive::Draw(VideoDriver^ driver, int overridePrimitiveCount, Scene::PrimitiveType overridePrimitiveType)
{
	LIME_ASSERT(driver != nullptr);
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(m_vertexCount > 0);
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(m_indexCount > 0);

	if (overridePrimitiveCount < 1)
		return;

#ifdef _DEBUG
	int maxPossiblePrimitiveCountWithOverridedType = VideoDriver::calculatePrimitiveCount(m_indexCount, overridePrimitiveType);
	LIME_ASSERT(maxPossiblePrimitiveCountWithOverridedType > 0);
	LIME_ASSERT(overridePrimitiveCount <= maxPossiblePrimitiveCountWithOverridedType);
#endif

	driver->m_VideoDriver->drawVertexPrimitiveList(
		m_vertices,
		m_vertexCount,
		m_indices,
		overridePrimitiveCount,
		m_vertexType,
		(scene::E_PRIMITIVE_TYPE)overridePrimitiveType,
		m_indexType);
}

void VertexPrimitive::Drop()
{
	m_primitiveCount = 0;

	// delete vertices

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		delete[] (video::S3DVertex*)m_vertices;
		break;

	case video::EVT_2TCOORDS:
		delete[] (video::S3DVertex2TCoords*)m_vertices;
		break;

	case video::EVT_TANGENTS:
		delete[] (video::S3DVertexTangents*)m_vertices;
		break;
	}

	m_vertices = nullptr;
	m_vertexCount = 0;

	// delete indices

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		delete[] (u16*)m_indices;
		break;

	case video::EIT_32BIT:
		delete[] (u32*)m_indices;
		break;
	}

	m_indices = nullptr;
	m_indexCount = 0;
}

int VertexPrimitive::GetIndex(int i)
{
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_indexCount);

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		return (int)(((u16*)m_indices)[i]);

	case video::EIT_32BIT:
		return (int)(((u32*)m_indices)[i]);
	}

	return -1;
}

void VertexPrimitive::SetIndex(int i, int index)
{
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_indexCount);
	LIME_ASSERT(index >= 0);

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		LIME_ASSERT(index <= 65536);
		((u16*)m_indices)[i] = (u16)index;
		return;

	case video::EIT_32BIT:
		((u32*)m_indices)[i] = (u32)index;
		return;
	}
}

void VertexPrimitive::SetIndicesSequence()
{
	LIME_ASSERT(m_indices != nullptr);

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		for (int i = 0; i < m_indexCount; i++)
			((u16*)m_indices)[i] = (u16)i;
		return;

	case video::EIT_32BIT:
		for (int i = 0; i < m_indexCount; i++)
			((u32*)m_indices)[i] = (u32)i;
		return;
	}
}

Object^ VertexPrimitive::GetVertex(int i)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		return gcnew Vertex3D(((video::S3DVertex*)m_vertices)[i]);

	case video::EVT_2TCOORDS:
		return gcnew Vertex3DTTCoords(((video::S3DVertex2TCoords*)m_vertices)[i]);

	case video::EVT_TANGENTS:
		return gcnew Vertex3DTangents(((video::S3DVertexTangents*)m_vertices)[i]);
	}

	return nullptr;
}

void VertexPrimitive::SetVertex(int i, Object^ vertex)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(vertex != nullptr);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		LIME_ASSERT(vertex->GetType() == Vertex3D::typeid);
		((video::S3DVertex*)m_vertices)[i] = *((Vertex3D^)vertex)->m_NativeValue;
		return;

	case video::EVT_2TCOORDS:
		LIME_ASSERT(vertex->GetType() == Vertex3DTTCoords::typeid);
		((video::S3DVertex2TCoords*)m_vertices)[i] = *((Vertex3DTTCoords^)vertex)->m_NativeValue;
		return;

	case video::EVT_TANGENTS:
		LIME_ASSERT(vertex->GetType() == Vertex3DTangents::typeid);
		((video::S3DVertexTangents*)m_vertices)[i] = *((Vertex3DTangents^)vertex)->m_NativeValue;
		return;
	}
}

void VertexPrimitive::SetVertexColor(int i, Color^ color)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(color != nullptr);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		((video::S3DVertex*)m_vertices)[i].Color = *color->m_NativeValue;
		return;

	case video::EVT_2TCOORDS:
		((video::S3DVertex2TCoords*)m_vertices)[i].Color = *color->m_NativeValue;
		return;

	case video::EVT_TANGENTS:
		((video::S3DVertexTangents*)m_vertices)[i].Color = *color->m_NativeValue;
		return;
	}
}

void VertexPrimitive::SetVertexColor(int i, unsigned int argb)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		((video::S3DVertex*)m_vertices)[i].Color.color = argb;
		return;

	case video::EVT_2TCOORDS:
		((video::S3DVertex2TCoords*)m_vertices)[i].Color.color = argb;
		return;

	case video::EVT_TANGENTS:
		((video::S3DVertexTangents*)m_vertices)[i].Color.color = argb;
		return;
	}
}

void VertexPrimitive::SetVertexPosition(int i, Vector3Df^ position)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(position != nullptr);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		((video::S3DVertex*)m_vertices)[i].Pos = *position->m_NativeValue;
		return;

	case video::EVT_2TCOORDS:
		((video::S3DVertex2TCoords*)m_vertices)[i].Pos = *position->m_NativeValue;
		return;

	case video::EVT_TANGENTS:
		((video::S3DVertexTangents*)m_vertices)[i].Pos = *position->m_NativeValue;
		return;
	}
}

void VertexPrimitive::SetVertexPosition(int i, float x, float y, float z)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	switch (m_vertexType)
	{
	case video::EVT_STANDARD:
		((video::S3DVertex*)m_vertices)[i].Pos.set(x, y, z);
		return;

	case video::EVT_2TCOORDS:
		((video::S3DVertex2TCoords*)m_vertices)[i].Pos.set(x, y, z);
		return;

	case video::EVT_TANGENTS:
		((video::S3DVertexTangents*)m_vertices)[i].Pos.set(x, y, z);
		return;
	}
}

int VertexPrimitive::IndexCount::get()
{
	return m_indexCount;
}

Video::IndexType VertexPrimitive::IndexType::get()
{
	return (Video::IndexType)m_indexType;
}

int VertexPrimitive::PrimitiveCount::get()
{
	return m_primitiveCount;
}

Scene::PrimitiveType VertexPrimitive::PrimitiveType::get()
{
	return (Scene::PrimitiveType)m_primitiveType;
}

unsigned long VertexPrimitive::TotalBytesAllocated::get()
{
	unsigned long t = 0;

	switch (m_indexType)
	{
	case video::EIT_16BIT:
		t += ((unsigned long)m_indexCount) * 2;
		break;

	case video::EIT_32BIT:
		t += ((unsigned long)m_indexCount) * 4;
		break;

	default:
		LIME_ASSERT2(false, "Unexpected IndexType: " + IndexType.ToString());
		break;
	}

	t += ((unsigned long)m_vertexCount) * video::getVertexPitchFromType(m_vertexType);

	return t;
}

int VertexPrimitive::VertexCount::get()
{
	return m_vertexCount;
}

Video::VertexType VertexPrimitive::VertexType::get()
{
	return (Video::VertexType)m_vertexType;
}

String^ VertexPrimitive::ToString()
{
	return String::Format(
		"VertexPrimitive: PrimitiveType={0}; PrimitiveCount={1}; IndexCount={2}; VertexCount={3}",
		PrimitiveType, PrimitiveCount, IndexCount, VertexCount);
}

} // end namespace Video
} // end namespace IrrlichtLime