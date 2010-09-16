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

void MeshBuffer::Append(array<Video::Vertex3D^>^ vertices, array<unsigned short>^ indices)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Standard);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(indices != nullptr);

	int vc = vertices->Length;
	video::S3DVertex* va = new video::S3DVertex[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *vertices[i]->m_NativeValue;

	int ic = indices->Length;
	unsigned short* ia = new unsigned short[ic];
	for (int i = 0; i < ic; i++)
		ia[i] = indices[i];

	m_MeshBuffer->append(va, vc, ia, ic);

	delete ia;
	delete va;
}

void MeshBuffer::Append(array<Video::Vertex3DTTCoords^>^ vertices, array<unsigned short>^ indices)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::TTCoords);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(indices != nullptr);

	int vc = vertices->Length;
	video::S3DVertex* va = new video::S3DVertex2TCoords[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *vertices[i]->m_NativeValue;

	int ic = indices->Length;
	unsigned short* ia = new unsigned short[ic];
	for (int i = 0; i < ic; i++)
		ia[i] = indices[i];

	m_MeshBuffer->append(va, vc, ia, ic);

	delete ia;
	delete va;
}

void MeshBuffer::Append(array<Video::Vertex3DTangents^>^ vertices, array<unsigned short>^ indices)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Tangents);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(indices != nullptr);

	int vc = vertices->Length;
	video::S3DVertex* va = new video::S3DVertexTangents[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *vertices[i]->m_NativeValue;

	int ic = indices->Length;
	unsigned short* ia = new unsigned short[ic];
	for (int i = 0; i < ic; i++)
		ia[i] = indices[i];

	m_MeshBuffer->append(va, vc, ia, ic);

	delete ia;
	delete va;
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

void MeshBuffer::UpdateIndices(array<unsigned short>^ indices, int startIndex)
{
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(startIndex + indices->Length <= this->IndexCount);

	unsigned short* p = m_MeshBuffer->getIndices();

	for (int i = 0; i < indices->Length; i++)
		p[i + startIndex] = indices[i];
}

void MeshBuffer::UpdateVertices(array<Video::Vertex3D^>^ vertices, int startIndex)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Standard);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(startIndex + vertices->Length <= this->VertexCount);

	video::S3DVertex* p = (video::S3DVertex*)m_MeshBuffer->getVertices();

	for (int i = 0; i < vertices->Length; i++)
		p[i + startIndex] = *vertices[i]->m_NativeValue;
}

void MeshBuffer::UpdateVertices(array<Video::Vertex3DTTCoords^>^ vertices, int startIndex)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::TTCoords);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(startIndex + vertices->Length <= this->VertexCount);

	video::S3DVertex2TCoords* p = (video::S3DVertex2TCoords*)m_MeshBuffer->getVertices();

	for (int i = 0; i < vertices->Length; i++)
		p[i + startIndex] = *vertices[i]->m_NativeValue;
}

void MeshBuffer::UpdateVertices(array<Video::Vertex3DTangents^>^ vertices, int startIndex)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Tangents);
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(startIndex + vertices->Length <= this->VertexCount);

	video::S3DVertexTangents* p = (video::S3DVertexTangents*)m_MeshBuffer->getVertices();

	for (int i = 0; i < vertices->Length; i++)
		p[i + startIndex] = *vertices[i]->m_NativeValue;
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