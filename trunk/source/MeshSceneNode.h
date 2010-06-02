#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class Mesh;

public ref class MeshSceneNode : SceneNode
{
public:

	property Scene::Mesh^ Mesh { Scene::Mesh^ get(); void set(Scene::Mesh^ value); }
	property bool ReadOnlyMeterials { bool get(); void set(bool value); }

internal:

	static MeshSceneNode^ Wrap(scene::IMeshSceneNode* ref);
	MeshSceneNode(scene::IMeshSceneNode* ref);

	scene::IMeshSceneNode* m_MeshSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime