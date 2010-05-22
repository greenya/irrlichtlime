#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class Material;
ref class Texture;

public ref class VideoDriver
{
public:

	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData, Recti^ sourceRect);
	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData);
	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color);
	bool BeginScene(bool backBuffer, bool zBuffer);
	bool BeginScene(bool backBuffer);
	bool BeginScene();

	bool CheckDriverReset();
	void DisableFeature(VideoDriverFeature feature, bool flag);
	void DisableFeature(VideoDriverFeature feature);
	bool EndScene();
	ExposedVideoData^ GetExposedVideoData();
	Texture^ GetTexture(String^ filename);
	Texture^ GetTextureByIndex(unsigned int index);
	Matrix4f^ GetTransform(TransformationState state);
	bool QueryFeature(VideoDriverFeature feature);
	void RenameTexture(Texture^ texture, String^ newName);
	void SetMaterial(Material^ material);
	void SetTransform(TransformationState state, Matrix4f^ mat);

	property Dimension2Du^ CurrentRenderTargetSize { Dimension2Du^ get(); }
	property Video::DriverType DriverType { Video::DriverType get(); }
	property unsigned int DynamicLightCount { unsigned int get(); }
	property int FPS { int get(); }
	property unsigned int MaterialRendererCount { unsigned int get(); }
	property unsigned int MaximalDynamicLightAmount { unsigned int get(); }
	property unsigned int MaximalPrimitiveCount { unsigned int get(); }
	property Dimension2Du^ MaxTextureSize { Dimension2Du^ get(); }
	property String^ Name { String^ get(); }
	property unsigned int PrimitiveCountDrawn { unsigned int get(); }
	property Dimension2Du^ ScreenSize { Dimension2Du^ get(); }
	property unsigned int TextureCount { unsigned int get(); }
	property String^ VendorInfo { String^ get(); }
	property Recti^ ViewPort { Recti^ get(); void set(Recti^ value); }

	virtual String^ ToString() override;

internal:

	VideoDriver(video::IVideoDriver* videoDriver);

	video::IVideoDriver* m_VideoDriver;
};

} // end namespace Video
} // end namespace IrrlichtLime