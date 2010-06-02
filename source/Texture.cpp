#include "stdafx.h"
#include "ReferenceCounted.h"
#include "Texture.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

Texture^ Texture::Wrap(video::ITexture* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew Texture(ref);
}

Texture::Texture(video::ITexture* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_Texture = ref;
}

} // end namespace Video
} // end namespace IrrlichtLime