#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class Texture;

public ref class RenderTarget : ReferenceCounted
{
public:

	Texture^ GetDepthStencil();
	NativeArray<Texture^>^ GetTexture();
	void SetTexture(array<Texture^>^ textures, Texture^ depthStencil);
	void SetTexture(Texture^ texture, Texture^ depthStencil);

	property Video::DriverType DriverType { Video::DriverType get(); }

	virtual String^ ToString() override;

internal:

	static RenderTarget^ Wrap(video::IRenderTarget* ref);
	RenderTarget(video::IRenderTarget* ref);

	video::IRenderTarget* m_RenderTarget;
};

} // end namespace Video
} // end namespace IrrlichtLime