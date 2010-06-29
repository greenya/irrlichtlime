#include "stdafx.h"
#include "DynamicMeshBuffer.h"
#include "IndexBuffer.h"
#include "MeshBuffer.h"
#include "VertexBuffer.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

DynamicMeshBuffer^ DynamicMeshBuffer::Wrap(scene::IDynamicMeshBuffer* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew DynamicMeshBuffer(ref);
}

DynamicMeshBuffer::DynamicMeshBuffer(scene::IDynamicMeshBuffer* ref)
	: MeshBuffer(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_DynamicMeshBuffer = ref;
}

Scene::IndexBuffer^ DynamicMeshBuffer::IndexBuffer::get()
{
	scene::IIndexBuffer* b = &m_DynamicMeshBuffer->getIndexBuffer();
	return Scene::IndexBuffer::Wrap(b);
}

void DynamicMeshBuffer::IndexBuffer::set(Scene::IndexBuffer^ value)
{
	m_DynamicMeshBuffer->setIndexBuffer(LIME_SAFEREF(value, m_IndexBuffer));
}

int DynamicMeshBuffer::IndexCount::get()
{
	return m_DynamicMeshBuffer->getIndexCount();
}

Scene::VertexBuffer^ DynamicMeshBuffer::VertexBuffer::get()
{
	scene::IVertexBuffer* b = &m_DynamicMeshBuffer->getVertexBuffer();
	return Scene::VertexBuffer::Wrap(b);
}

void DynamicMeshBuffer::VertexBuffer::set(Scene::VertexBuffer^ value)
{
	m_DynamicMeshBuffer->setVertexBuffer(LIME_SAFEREF(value, m_VertexBuffer));
}

int DynamicMeshBuffer::VertexCount::get()
{
	return m_DynamicMeshBuffer->getVertexCount();
}

} // end namespace Scene
} // end namespace IrrlichtLime