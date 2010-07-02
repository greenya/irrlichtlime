#include "stdafx.h"
#include "ReferenceCounted.h"
#include "VertexBuffer.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

VertexBuffer^ VertexBuffer::Wrap(scene::IVertexBuffer* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew VertexBuffer(ref);
}

VertexBuffer::VertexBuffer(scene::IVertexBuffer* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_VertexBuffer = ref;
}

void VertexBuffer::AddVertex(Video::Vertex3D^ vertex)
{
	LIME_ASSERT(vertex != nullptr);
	m_VertexBuffer->push_back(*vertex->m_NativeValue);
}

Video::Vertex3D^ VertexBuffer::GetValue(int index)
{
	LIME_ASSERT(index >= 0);
	return gcnew Video::Vertex3D((*m_VertexBuffer)[index]);
}

void VertexBuffer::SetDirty()
{
	m_VertexBuffer->setDirty();
}

void VertexBuffer::SetValue(int index, Video::Vertex3D^ value)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(value != nullptr);

	(*m_VertexBuffer)[index] = *value->m_NativeValue;
}

int VertexBuffer::AllocatedSize::get()
{
	return m_VertexBuffer->allocated_size();
}

Scene::HardwareMappingHint VertexBuffer::HardwareMappingHint::get()
{
	return (Scene::HardwareMappingHint)m_VertexBuffer->getHardwareMappingHint();
}

void VertexBuffer::HardwareMappingHint::set(Scene::HardwareMappingHint value)
{
	m_VertexBuffer->setHardwareMappingHint((scene::E_HARDWARE_MAPPING)value);
}

Video::VertexType VertexBuffer::Type::get()
{
	return (Video::VertexType)m_VertexBuffer->getType();
}

void VertexBuffer::Type::set(Video::VertexType value)
{
	m_VertexBuffer->setType((video::E_VERTEX_TYPE)value);
}

int VertexBuffer::VertexCount::get()
{
	return m_VertexBuffer->size();
}

String^ VertexBuffer::ToString()
{
	return String::Format("VertexBuffer: VertexCount={0}", VertexCount);
}

} // end namespace Scene
} // end namespace IrrlichtLime