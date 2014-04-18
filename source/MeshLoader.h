#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace IO { ref class ReadFile; }
namespace Scene {

ref class AnimatedMesh;
ref class MeshTextureLoader;

public ref class MeshLoader : ReferenceCounted
{
public:

	AnimatedMesh^ CreateMesh(IO::ReadFile^ file);
	bool IsALoadableFileExtension(String^ filename);

	property Scene::MeshTextureLoader^ MeshTextureLoader { Scene::MeshTextureLoader^ get(); void set(Scene::MeshTextureLoader^ value); }

internal:

	static MeshLoader^ Wrap(scene::IMeshLoader* ref);
	MeshLoader(scene::IMeshLoader* ref);

	scene::IMeshLoader* m_MeshLoader;
};

} // end namespace Scene
} // end namespace IrrlichtLime