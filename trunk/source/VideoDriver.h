#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class Texture;

public ref class VideoDriver
{
public:

	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color);
	bool BeginScene(bool backBuffer, bool zBuffer);
	bool BeginScene(bool backBuffer);
	bool BeginScene();

	bool EndScene();

	Texture^ GetTexture(String^ filename);

	property Dimension2Du^ CurrentRenderTargetSize { Dimension2Du^ get(); }
	property Video::DriverType DriverType { Video::DriverType get(); }
	property UInt32 DynamicLightCount { UInt32 get(); }
	property Int32 FPS { Int32 get(); }
	property UInt32 MaterialRendererCount { UInt32 get(); }
	property UInt32 MaximalDynamicLightAmount { UInt32 get(); }
	property UInt32 MaximalPrimitiveCount { UInt32 get(); }
	property Dimension2Du^ MaxTextureSize { Dimension2Du^ get(); }
	property String^ Name { String^ get(); }
	property UInt32 PrimitiveCountDrawn { UInt32 get(); }
	property Dimension2Du^ ScreenSize { Dimension2Du^ get(); }
	property String^ VendorInfo { String^ get(); }
	property Recti^ ViewPort { Recti^ get(); void set(Recti^ value); }

	virtual String^ ToString() override;

internal:

	VideoDriver(video::IVideoDriver* videoDriver);

	video::IVideoDriver* m_VideoDriver;
};

} // end namespace Video
} // end namespace IrrlichtLime