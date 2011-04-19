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

Mesh^ Mesh::Create()
{
	scene::IMesh* m = new scene::SMesh();
	return gcnew Mesh(m);
}

void Mesh::AddMeshBuffer(MeshBuffer^ buffer)
{
	LIME_ASSERT(buffer != nullptr);

	scene::SMesh* m = (scene::SMesh*)m_Mesh; // !!! cast to SMesh*
	m->addMeshBuffer(buffer->m_MeshBuffer);
}

MeshBuffer^ Mesh::GetMeshBuffer(Video::Material^ material)
{
	LIME_ASSERT(material != nullptr);
	
	scene::IMeshBuffer* b = m_Mesh->getMeshBuffer(*material->m_NativeValue);
	return MeshBuffer::Wrap(b);
}

MeshBuffer^ Mesh::GetMeshBuffer(int index)
{
	LIME_ASSERT(index >= 0 && index < MeshBufferCount);
	
	scene::IMeshBuffer* b = m_Mesh->getMeshBuffer(index);
	return MeshBuffer::Wrap(b);
}

void Mesh::RecalculateBoundingBox()
{
	((scene::SMesh*)m_Mesh)->recalculateBoundingBox(); // !!! cast to SMesh*
}

void Mesh::RemoveMeshBuffer(int index)
{
	LIME_ASSERT(index >= 0 && index < MeshBufferCount);
	
	scene::SMesh* m = (scene::SMesh*)m_Mesh; // !!! cast to SMesh*
	m->MeshBuffers[index]->drop();
	m->MeshBuffers.erase(index);
}

void Mesh::RemoveMeshBuffer(int index, int count)
{
	LIME_ASSERT(index >= 0 && index < MeshBufferCount);
	LIME_ASSERT(count >= 1 && index + count <= MeshBufferCount);
	
	scene::SMesh* m = (scene::SMesh*)m_Mesh; // !!! cast to SMesh*

	for (int i = index; i < index + count; i++)
		m->MeshBuffers[i]->drop();

	m->MeshBuffers.erase(index, count);
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

int Mesh::MeshBufferCount::get()
{
	return m_Mesh->getMeshBufferCount();
}

String^ Mesh::ToString()
{
	return String::Format("Mesh: MeshBufferCount={0}", MeshBufferCount);
}

} // end namespace Scene
} // end namespace IrrlichtLime