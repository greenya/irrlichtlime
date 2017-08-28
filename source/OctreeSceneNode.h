#pragma once

#include "stdafx.h"
#include "MeshSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class OctreeSceneNode : MeshSceneNode
{
public:

	property OctreePolygonChecks PolygonChecks { OctreePolygonChecks get(); void set(OctreePolygonChecks value); }
	property OctreeVBO UseVBO { OctreeVBO get(); void set(OctreeVBO value); }

internal:

	static OctreeSceneNode^ Wrap(scene::IOctreeSceneNode* ref);
	OctreeSceneNode(scene::IOctreeSceneNode* ref);

	scene::IOctreeSceneNode* m_OctreeSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime