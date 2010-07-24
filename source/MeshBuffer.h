#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Material; }
namespace Scene {

public ref class MeshBuffer : ReferenceCounted
{
public:

	void Append(MeshBuffer^ other);
	//void Append(const void *const vertices, u32 numVertices, const u16 *const indices, u32 numIndices);

	//u16* getIndices();
	//void* getVertices();

	Vector3Df^ GetNormal(int vertexIndex);
	Vector3Df^ GetPosition(int vertexIndex);
	Vector2Df^ GetTCoords(int vertexIndex);

	void RecalculateBoundingBox();

	void SetDirty(HardwareBufferType buffer);
	void SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer);

	property AABBox^ BoundingBox { AABBox^ get(); void set(AABBox^ value); }
	property HardwareMappingHint HardwareMappingHintForIndex { HardwareMappingHint get(); }
	property HardwareMappingHint HardwareMappingHintForVertex { HardwareMappingHint get(); }
	property int IndexCount { int get(); }
	property Video::IndexType IndexType { Video::IndexType get(); }
	property Video::Material^ Material { Video::Material^ get(); }
	property int VertexCount { int get(); }
	property Video::VertexType VertexType { Video::VertexType get(); }

	virtual String^ ToString() override;

internal:

	static MeshBuffer^ Wrap(scene::IMeshBuffer* ref);
	MeshBuffer(scene::IMeshBuffer* ref);

	scene::IMeshBuffer* m_MeshBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime