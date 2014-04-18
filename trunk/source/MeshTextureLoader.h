#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"


using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace IO { ref class ReadFile; }
namespace Scene {


public ref class MeshTextureLoader : ReferenceCounted
{
public:

	Video::Texture^ GetTexture(String^ textureName);
	void SetMaterialFile(IO::ReadFile^ materialFile);
	void SetMeshFile(IO::ReadFile^ meshFile);

	property String^ TexturePath { String^ get(); void set(String^ value); } 

internal:

	static MeshTextureLoader^ Wrap(scene::IMeshTextureLoader* ref);
	MeshTextureLoader(scene::IMeshTextureLoader* ref);

	scene::IMeshTextureLoader* m_MeshTextureLoader;
};

} // end namespace Scene
} // end namespace IrrlichtLime
