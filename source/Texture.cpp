#pragma once

#include "stdafx.h"
#include "Texture.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

Texture::Texture(video::ITexture* texture)
{
	LIME_ASSERT(texture != nullptr);
	m_Texture = texture;
}

} // end namespace Video
} // end namespace IrrlichtLime