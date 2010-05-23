#include "stdafx.h"
#include "ReferenceCounted.h"
#include "Texture.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

Texture::Texture(video::ITexture* texture)
	: ReferenceCounted(texture)
{
	LIME_ASSERT(texture != nullptr);
	m_Texture = texture;
}

} // end namespace Video
} // end namespace IrrlichtLime