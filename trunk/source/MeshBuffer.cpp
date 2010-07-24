#include "stdafx.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshBuffer^ MeshBuffer::Wrap(scene::IMeshBuffer* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew MeshBuffer(ref);
}

MeshBuffer::MeshBuffer(scene::IMeshBuffer* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_MeshBuffer = ref;
}

void MeshBuffer::Append(MeshBuffer^ other)
{
	m_MeshBuffer->append(LIME_SAFEREF(other, m_MeshBuffer));
}

Vector3Df^ MeshBuffer::GetNormal(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return gcnew Vector3Df(m_MeshBuffer->getNormal(vertexIndex));
}

Vector3Df^ MeshBuffer::GetPosition(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return gcnew Vector3Df(m_MeshBuffer->getPosition(vertexIndex));
}

Vector2Df^ MeshBuffer::GetTCoords(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return gcnew Vector2Df(m_MeshBuffer->getTCoords(vertexIndex));
}

void MeshBuffer::RecalculateBoundingBox()
{
	m_MeshBuffer->recalculateBoundingBox();
}

void MeshBuffer::SetDirty(HardwareBufferType buffer)
{
	m_MeshBuffer->setDirty((scene::E_BUFFER_TYPE)buffer);
}

void MeshBuffer::SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer)
{
	m_MeshBuffer->setHardwareMappingHint((scene::E_HARDWARE_MAPPING)mappingHint, (scene::E_BUFFER_TYPE)buffer);
}

AABBox^ MeshBuffer::BoundingBox::get()
{
	return gcnew AABBox(m_MeshBuffer->getBoundingBox());
}

void MeshBuffer::BoundingBox::set(AABBox^ value)
{
	LIME_ASSERT(value != nullptr);
	m_MeshBuffer->setBoundingBox(*value->m_NativeValue);
}

HardwareMappingHint MeshBuffer::HardwareMappingHintForIndex::get()
{
	return (HardwareMappingHint)m_MeshBuffer->getHardwareMappingHint_Index();
}

HardwareMappingHint MeshBuffer::HardwareMappingHintForVertex::get()
{
	return (HardwareMappingHint)m_MeshBuffer->getHardwareMappingHint_Vertex();
}

int MeshBuffer::IndexCount::get()
{
	return m_MeshBuffer->getIndexCount();
}

Video::IndexType MeshBuffer::IndexType::get()
{
	return (Video::IndexType)m_MeshBuffer->getIndexType();
}

Video::Material^ MeshBuffer::Material::get()
{
	return Video::Material::Wrap(&m_MeshBuffer->getMaterial());
}

int MeshBuffer::VertexCount::get()
{
	return m_MeshBuffer->getVertexCount();
}

Video::VertexType MeshBuffer::VertexType::get()
{
	return (Video::VertexType)m_MeshBuffer->getVertexType();
}

String^ MeshBuffer::ToString()
{
	return String::Format("MeshBuffer: VertexCount={0}; IndexCount={1}", VertexCount, IndexCount);
}

} // end namespace Scene
} // end namespace IrrlichtLime