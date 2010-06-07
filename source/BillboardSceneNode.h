#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class BillboardSceneNode : SceneNode
{
public:

	property Dimension2Df^ Size { Dimension2Df^ get(); void set(Dimension2Df^ value); }

internal:

	static BillboardSceneNode^ Wrap(scene::IBillboardSceneNode* ref);
	BillboardSceneNode(scene::IBillboardSceneNode* ref);

	scene::IBillboardSceneNode* m_BillboardSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime