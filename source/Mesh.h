#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Material; }
namespace Scene {

ref class MeshBuffer;

public ref class Mesh : ReferenceCounted
{
public:

	static Mesh^ Create();

	void AddMeshBuffer(MeshBuffer^ buffer);
	
	MeshBuffer^ GetMeshBuffer(Video::Material^ material);
	MeshBuffer^ GetMeshBuffer(int index);

	void RecalculateBoundingBox();

	void RemoveMeshBuffer(int index);
	void RemoveMeshBuffer(int index, int count);

	void SetDirty(HardwareBufferType buffer);
	void SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer);
	void SetMaterialFlag(Video::MaterialFlag flag, bool newvalue);

	property AABBox^ BoundingBox { AABBox^ get(); void set(AABBox^ value); }
	property int MeshBufferCount { int get(); }

	virtual String^ ToString() override;

internal:

	static Mesh^ Wrap(scene::IMesh* ref);
	Mesh(scene::IMesh* ref);

	scene::IMesh* m_Mesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime