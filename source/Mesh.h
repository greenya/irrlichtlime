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

	MeshBuffer^ GetMeshBuffer(Video::Material^ material);
	MeshBuffer^ GetMeshBuffer(unsigned int index);
	void SetDirty(HardwareBufferType buffer);
	void SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer);
	void SetMaterialFlag(Video::MaterialFlag flag, bool newvalue);

	property AABBox3Df^ BoundingBox { AABBox3Df^ get(); void set(AABBox3Df^ value); }
	property unsigned int MeshBufferCount { unsigned int get(); }

internal:

	static Mesh^ Wrap(scene::IMesh* ref);
	Mesh(scene::IMesh* ref);

	scene::IMesh* m_Mesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime