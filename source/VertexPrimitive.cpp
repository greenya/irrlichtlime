#include "stdafx.h"
#include "VertexPrimitive.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

VertexPrimitive::VertexPrimitive(int vertexCount, int indexCount, Scene::PrimitiveType primitiveType)
{
	LIME_ASSERT(vertexCount > 0 && vertexCount <= 65536);
	LIME_ASSERT(indexCount > 0);

	m_primitiveType = (scene::E_PRIMITIVE_TYPE)primitiveType;

	m_primitiveCount = VideoDriver::calculatePrimitiveCount(indexCount, primitiveType);

	m_vertices = new S3DVertex[vertexCount];
	m_vertexCount = vertexCount;

	m_indices = new u16[indexCount];
	m_indexCount = indexCount;
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
		video::EVT_STANDARD,
		m_primitiveType,
		video::EIT_16BIT);
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
		video::EVT_STANDARD,
		m_primitiveType,
		video::EIT_16BIT);
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
	int maxPrimitiveCount = VideoDriver::calculatePrimitiveCount(m_indexCount, overridePrimitiveType);
	LIME_ASSERT(maxPrimitiveCount > 0);
	LIME_ASSERT(overridePrimitiveCount <= maxPrimitiveCount);
#endif

	driver->m_VideoDriver->drawVertexPrimitiveList(
		m_vertices,
		m_vertexCount,
		m_indices,
		overridePrimitiveCount,
		video::EVT_STANDARD,
		(scene::E_PRIMITIVE_TYPE)overridePrimitiveType,
		video::EIT_16BIT);
}

void VertexPrimitive::Drop()
{
	m_primitiveCount = 0;

	delete[] m_vertices;
	m_vertices = nullptr;
	m_vertexCount = 0;

	delete[] m_indices;
	m_indices = nullptr;
	m_indexCount = 0;
}

int VertexPrimitive::GetIndex(int i)
{
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_indexCount);

	return m_indices[i];
}

void VertexPrimitive::SetIndex(int i, int index)
{
	LIME_ASSERT(m_indices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_indexCount);
	LIME_ASSERT(index >= 0 && index <= 65535);

	m_indices[i] = (u16)index;
}

Vertex3D^ VertexPrimitive::GetVertex(int i)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	Vertex3D^ v = gcnew Vertex3D(m_vertices[i]);
	return v;
}

void VertexPrimitive::SetVertex(int i, Vertex3D^ vertex)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(vertex != nullptr);

	m_vertices[i] = *vertex->m_NativeValue;
}

void VertexPrimitive::SetVertexColor(int i, Color^ color)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(color != nullptr);

	m_vertices[i].Color = *color->m_NativeValue;
}

void VertexPrimitive::SetVertexColor(int i, unsigned int argb)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	m_vertices[i].Color.color = argb;
}

void VertexPrimitive::SetVertexPosition(int i, Vector3Df^ position)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);
	LIME_ASSERT(position != nullptr);

	m_vertices[i].Pos = *position->m_NativeValue;
}

void VertexPrimitive::SetVertexPosition(int i, float x, float y, float z)
{
	LIME_ASSERT(m_vertices != nullptr);
	LIME_ASSERT(i >= 0 && i < m_vertexCount);

	m_vertices[i].Pos.set(x, y, z);
}

int VertexPrimitive::IndexCount::get()
{
	return m_indexCount;
}

Scene::PrimitiveType VertexPrimitive::PrimitiveType::get()
{
	return (Scene::PrimitiveType)m_primitiveType;
}

int VertexPrimitive::VertexCount::get()
{
	return m_vertexCount;
}

String^ VertexPrimitive::ToString()
{
	return String::Format("VertexPrimitive: PrimitiveType={0}; IndexCount={1}; VertexCount={2}", PrimitiveType, IndexCount, VertexCount);
}

} // end namespace Video
} // end namespace IrrlichtLime