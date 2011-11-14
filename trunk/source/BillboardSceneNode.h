#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class BillboardSceneNode : SceneNode
{
	// Small Notes:
	// - we use naming "top" (for "top edge" and "end edge") and "bottom" (for "bottom edge" and "start edge", accordingly to native interface) for widths and colors;
	// - we allow reading and writing single props for better debugging (native interface allows reading and writing by pairs only);
	// - we replaced Size property with single float Height;

public:

	void SetShape(float bottomWidth, float topWidth, float height);

	property Video::Color^ BottomColor { Video::Color^ get(); void set(Video::Color^ value); }
	property float BottomWidth { float get(); void set(float value); }
	property float Height { float get(); void set(float value); }
	property Video::Color^ TopColor { Video::Color^ get(); void set(Video::Color^ value); }
	property float TopWidth { float get(); void set(float value); }

internal:

	static BillboardSceneNode^ Wrap(scene::IBillboardSceneNode* ref);
	BillboardSceneNode(scene::IBillboardSceneNode* ref);

	scene::IBillboardSceneNode* m_BillboardSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime