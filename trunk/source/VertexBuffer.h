#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

public ref class VertexBuffer : ReferenceCounted
{
public:

	void AddVertex(Video::Vertex3D^ vertex);
	Video::Vertex3D^ GetValue(int index);
	void SetDirty();
	void SetValue(int index, Video::Vertex3D^ value);

	property int AllocatedSize { int get(); }
	property Scene::HardwareMappingHint HardwareMappingHint { Scene::HardwareMappingHint get(); void set(Scene::HardwareMappingHint value); }
	property Video::VertexType Type { Video::VertexType get(); void set(Video::VertexType value); }
	property int VertexCount { int get(); }

	virtual String^ ToString() override;

internal:

	static VertexBuffer^ Wrap(scene::IVertexBuffer* ref);
	VertexBuffer(scene::IVertexBuffer* ref);

	scene::IVertexBuffer* m_VertexBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime