#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class Texture
{
public:

internal:

	Texture(video::ITexture* texture);

	video::ITexture* m_Texture;
};

} // end namespace Video
} // end namespace IrrlichtLime