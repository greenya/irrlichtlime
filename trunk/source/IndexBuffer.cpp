#include "stdafx.h"
#include "IndexBuffer.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

IndexBuffer^ IndexBuffer::Wrap(scene::IIndexBuffer* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew IndexBuffer(ref);
}

IndexBuffer::IndexBuffer(scene::IIndexBuffer* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_IndexBuffer = ref;
}

void IndexBuffer::AddIndex(int index)
{
	LIME_ASSERT(index >= 0);
	m_IndexBuffer->push_back(index);
}

int IndexBuffer::GetValue(int index)
{
	LIME_ASSERT(index >= 0);
	return (*m_IndexBuffer)[index];
}

void IndexBuffer::SetDirty()
{
	m_IndexBuffer->setDirty();
}

void IndexBuffer::SetValue(int index, int value)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(value >= 0);

	m_IndexBuffer->setValue(index, value);
}

int IndexBuffer::AllocatedSize::get()
{
	return m_IndexBuffer->allocated_size();
}

Scene::HardwareMappingHint IndexBuffer::HardwareMappingHint::get()
{
	return (Scene::HardwareMappingHint)m_IndexBuffer->getHardwareMappingHint();
}

void IndexBuffer::HardwareMappingHint::set(Scene::HardwareMappingHint value)
{
	m_IndexBuffer->setHardwareMappingHint((scene::E_HARDWARE_MAPPING)value);
}

int IndexBuffer::IndexCount::get()
{
	return m_IndexBuffer->size();
}

Video::IndexType IndexBuffer::Type::get()
{
	return (Video::IndexType)m_IndexBuffer->getType();
}

void IndexBuffer::Type::set(Video::IndexType value)
{
	m_IndexBuffer->setType((video::E_INDEX_TYPE)value);
}

String^ IndexBuffer::ToString()
{
	return String::Format("IndexBuffer: IndexCount={0}", IndexCount);
}

} // end namespace Scene
} // end namespace IrrlichtLime