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
	void Append(array<Video::Vertex3D^>^ vertices, array<unsigned short>^ indices);
	void Append(array<Video::Vertex3DTTCoords^>^ vertices, array<unsigned short>^ indices);
	void Append(array<Video::Vertex3DTangents^>^ vertices, array<unsigned short>^ indices);

	Vector3Df^ GetNormal(int vertexIndex);
	Vector3Df^ GetPosition(int vertexIndex);
	Vector2Df^ GetTCoords(int vertexIndex);

	void RecalculateBoundingBox();

	void SetDirty(HardwareBufferType buffer);
	void SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer);

	void UpdateIndices(array<unsigned short>^ indices, int startIndex);
	void UpdateVertices(array<Video::Vertex3D^>^ vertices, int startIndex);
	void UpdateVertices(array<Video::Vertex3DTTCoords^>^ vertices, int startIndex);
	void UpdateVertices(array<Video::Vertex3DTangents^>^ vertices, int startIndex);

	property AABBox^ BoundingBox { AABBox^ get(); void set(AABBox^ value); }
	property HardwareMappingHint HardwareMappingHintForIndex { HardwareMappingHint get(); }
	property HardwareMappingHint HardwareMappingHintForVertex { HardwareMappingHint get(); }
	property int IndexCount { int get(); }
	property Video::IndexType IndexType { Video::IndexType get(); }
	property Object^ Indices { Object^ get(); }
	property Video::Material^ Material { Video::Material^ get(); }
	property int VertexCount { int get(); }
	property Video::VertexType VertexType { Video::VertexType get(); }
	property Object^ Vertices { Object^ get(); }

	virtual String^ ToString() override;

internal:

	static MeshBuffer^ Wrap(scene::IMeshBuffer* ref);
	MeshBuffer(scene::IMeshBuffer* ref);

	scene::IMeshBuffer* m_MeshBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime