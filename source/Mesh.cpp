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

MeshBuffer^ Mesh::GetMeshBuffer(int index)
{
	LIME_ASSERT(index >= 0 && index < MeshBufferCount);
	
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

AnimatedMeshType Mesh::MeshType::get()
{
	return (AnimatedMeshType)m_Mesh->getMeshType();
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

//This class provides direct access to the mesh buffers of a mesh
//In debug builds, it performs range checks
private ref class MeshBufferArray sealed : public NativeArray<MeshBuffer^>
{

internal:

	MeshBufferArray(IMesh* mesh)
	{
		this->mesh = mesh;
	}

	virtual void* GetPointer() override sealed
	{
		return nullptr;
	}

public:

	property MeshBuffer^ default [int]
	{
		virtual MeshBuffer^ get(int index) override sealed
		{
			LIME_ASSERT(index >= 0 && index < Count);
			return MeshBuffer::Wrap(mesh->getMeshBuffer(index));
		}

#pragma warning (push)
#pragma warning (disable: 4100)
		virtual void set(int index, MeshBuffer^ value) override sealed
		{
			throw gcnew NotSupportedException();
		}
#pragma warning (pop)
	}

	property int Count
	{
		virtual int get() override sealed
		{
			return mesh->getMeshBufferCount();
		}
	}

	property bool IsReadOnly
	{
		virtual bool get() override sealed
		{
			return true;
		}
	}

internal:
	
	IMesh* mesh;
};

NativeArray<MeshBuffer^>^ Mesh::MeshBuffers::get()
{
	/*array<MeshBuffer^>^ l = gcnew array<MeshBuffer^>(m_Mesh->getMeshBufferCount());
	int li = 0;

	for (int i = 0; i < l->Length; i++)
	{
		scene::IMeshBuffer* buf = m_Mesh->getMeshBuffer(i);
		MeshBuffer^ mb = MeshBuffer::Wrap(buf);
		if (mb != nullptr)
			l[li++] = mb;
	}

	return l;*/
	return gcnew MeshBufferArray(m_Mesh);
}

String^ Mesh::ToString()
{
	unsigned int totalVertices = 0;
	unsigned int totalIndices = 0;
	for (unsigned int i = 0; i < m_Mesh->getMeshBufferCount(); i++)
	{
		scene::IMeshBuffer* mb = m_Mesh->getMeshBuffer(i);
		totalVertices += mb->getVertexCount();
		totalIndices += mb->getIndexCount();
	}
	
	return String::Format(
		"Mesh: {0} vertices and {1} indices in {2} mesh buffer(s)",
		totalVertices, totalIndices, m_Mesh->getMeshBufferCount());
}

} // end namespace Scene
} // end namespace IrrlichtLime