#include "stdafx.h"
#include "MeshTextureLoader.h"
#include "Texture.h"
#include "ReadFile.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshTextureLoader^ MeshTextureLoader::Wrap(scene::IMeshTextureLoader* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew MeshTextureLoader(ref);
}

MeshTextureLoader::MeshTextureLoader(scene::IMeshTextureLoader* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_MeshTextureLoader = ref;
}

Video::Texture^ MeshTextureLoader::GetTexture(String^ textureName)
{
	LIME_ASSERT(textureName != nullptr);

	video::ITexture* t = m_MeshTextureLoader->getTexture(Lime::StringToPath(textureName));
	return Video::Texture::Wrap(t);
}

void MeshTextureLoader::SetMaterialFile(IO::ReadFile^ materialFile)
{
	LIME_ASSERT(materialFile != nullptr);
	m_MeshTextureLoader->setMaterialFile(LIME_SAFEREF(materialFile, m_ReadFile));
}

void MeshTextureLoader::SetMeshFile(IO::ReadFile^ meshFile)
{
	LIME_ASSERT(meshFile != nullptr);
	m_MeshTextureLoader->setMeshFile(LIME_SAFEREF(meshFile, m_ReadFile));
}

String^ MeshTextureLoader::TexturePath::get()
{
	return gcnew String(m_MeshTextureLoader->getTexturePath().c_str());
}

void MeshTextureLoader::TexturePath::set(String^ value)
{
	LIME_ASSERT(value != nullptr);
	m_MeshTextureLoader->setTexturePath(Lime::StringToPath(value));
}

} // end namespace Scene
} // end namespace IrrlichtLime