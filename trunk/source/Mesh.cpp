#include "stdafx.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

Mesh^ Mesh::Wrap(scene::IMesh* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew Mesh(ref);
}

Mesh::Mesh(scene::IMesh* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_Mesh = ref;
}

MeshBuffer^ Mesh::GetMeshBuffer(Video::Material^ material)
{
	LIME_ASSERT(material != nullptr);
	
	scene::IMeshBuffer* b = m_Mesh->getMeshBuffer(*material->m_NativeValue);
	return MeshBuffer::Wrap(b);
}

MeshBuffer^ Mesh::GetMeshBuffer(unsigned int index)
{
	LIME_ASSERT(index < MeshBufferCount);
	
	scene::IMeshBuffer* b = m_Mesh->getMeshBuffer(index);
	return MeshBuffer::Wrap(b);
}

void Mesh::SetDirty(HardwareBufferType buffer)
{
	m_Mesh->setDirty((scene::E_BUFFER_TYPE)buffer);
}

void Mesh::SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer)
{
	m_Mesh->setHardwareMappingHint((scene::E_HARDWARE_MAPPING)mappingHint, (scene::E_BUFFER_TYPE)buffer);
}

void Mesh::SetMaterialFlag(Video::MaterialFlag flag, bool newvalue)
{
	m_Mesh->setMaterialFlag((video::E_MATERIAL_FLAG)flag, newvalue);
}

AABBox^ Mesh::BoundingBox::get()
{
	return gcnew AABBox(m_Mesh->getBoundingBox());
}

void Mesh::BoundingBox::set(AABBox^ value)
{
	LIME_ASSERT(value != nullptr);
	m_Mesh->setBoundingBox(*value->m_NativeValue);
}

unsigned int Mesh::MeshBufferCount::get()
{
	return m_Mesh->getMeshBufferCount();
}

} // end namespace Scene
} // end namespace IrrlichtLime