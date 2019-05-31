#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public enum class RenderTarget
{
	FrameBuffer = ERT_FRAME_BUFFER,
	RenderTexture = ERT_RENDER_TEXTURE,
	MultiRenderTexture = ERT_MULTI_RENDER_TEXTURES,
	StereoLeftBuffer = ERT_STEREO_LEFT_BUFFER,
	StereoRightBuffer = ERT_STEREO_RIGHT_BUFFER,
	StereoBothBuffers = ERT_STEREO_BOTH_BUFFERS,
	AuxBuffer0 = ERT_AUX_BUFFER0,
	AuxBuffer1 = ERT_AUX_BUFFER1,
	AuxBuffer2 = ERT_AUX_BUFFER2,
	AuxBuffer3 = ERT_AUX_BUFFER3,
	AuxBuffer4 = ERT_AUX_BUFFER4
};

} // end namespace Video
} // end namespace IrrlichtLime