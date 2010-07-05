#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

public ref class IndexBuffer : ReferenceCounted
{
public:

	void AddIndex(int index);
	int GetValue(int index);
	void SetDirty();
	void SetValue(int index, int value);

	property int AllocatedSize { int get(); }
	property Scene::HardwareMappingHint HardwareMappingHint { Scene::HardwareMappingHint get(); void set(Scene::HardwareMappingHint value); }
	property int IndexCount { int get(); }
	property Video::IndexType Type { Video::IndexType get(); void set(Video::IndexType value); }

	virtual String^ ToString() override;

internal:

	static IndexBuffer^ Wrap(scene::IIndexBuffer* ref);
	IndexBuffer(scene::IIndexBuffer* ref);

	scene::IIndexBuffer* m_IndexBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime