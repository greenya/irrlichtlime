#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene { ref class Mesh; ref class MeshBuffer; ref class SceneNode; }
namespace Video {

ref class Image;
ref class Material;
ref class Texture;

public ref class VideoDriver : ReferenceCounted
{
public:

	Texture^ AddRenderTargetTexture(Dimension2Du^ size, String^ name, ColorFormat format);
	Texture^ AddRenderTargetTexture(Dimension2Du^ size, String^ name);
	Texture^ AddRenderTargetTexture(Dimension2Du^ size);

	Texture^ AddTexture(Dimension2Du^ size, String^ name, ColorFormat format);
	Texture^ AddTexture(Dimension2Du^ size, String^ name);
	Texture^ AddTexture(String^ name, Image^ image); // 3rd argument "void* mipmapData=0" currently not supported

	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData, Recti^ sourceRect);
	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData);
	bool BeginScene(bool backBuffer, bool zBuffer, Coloru^ color);
	bool BeginScene(bool backBuffer, bool zBuffer);
	bool BeginScene(bool backBuffer);
	bool BeginScene();

	bool CheckDriverReset();

	void CreateOcclusionQuery(Scene::SceneNode^ node, Scene::Mesh^ mesh);
	void CreateOcclusionQuery(Scene::SceneNode^ node);

	void DisableFeature(VideoDriverFeature feature, bool flag);
	void DisableFeature(VideoDriverFeature feature);

	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices, Scene::PrimitiveType pType);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices, Scene::PrimitiveType pType);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices);

	bool EndScene();

	ExposedVideoData^ GetExposedVideoData();
	unsigned int GetOcclusionQueryResult(Scene::SceneNode^ node);
	Texture^ GetTexture(String^ filename);
	Texture^ GetTextureByIndex(unsigned int index);
	Matrix4f^ GetTransform(TransformationState state);

	void MakeColorKeyTexture(Texture^ texture, Coloru^ color, bool zeroTexels);
	void MakeColorKeyTexture(Texture^ texture, Coloru^ color);
	void MakeColorKeyTexture(Texture^ texture, Vector2Di^ colorKeyPixelPos, bool zeroTexels);
	void MakeColorKeyTexture(Texture^ texture, Vector2Di^ colorKeyPixelPos);
	void MakeNormalMapTexture(Texture^ texture, float amplitude);
	void MakeNormalMapTexture(Texture^ texture);

	bool QueryFeature(VideoDriverFeature feature);

	void RemoveAllHardwareBuffers();
	void RemoveAllOcclusionQueries();
	void RemoveAllTextures();
	void RemoveHardwareBuffer(Scene::MeshBuffer^ mb);
	void RemoveOcclusionQuery(Scene::SceneNode^ node);
	void RemoveTexture(Texture^ texture);

	void RenameTexture(Texture^ texture, String^ newName);

	void RunAllOcclusionQueries(bool visible);
	void RunAllOcclusionQueries();
	void RunOcclusionQuery(Scene::SceneNode^ node, bool visible);
	void RunOcclusionQuery(Scene::SceneNode^ node);

	void SetMaterial(Material^ material);
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer, Coloru^ color);
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer);
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer);
	bool SetRenderTarget(Texture^ texture);
	bool SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer, Coloru^ color);
	bool SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer);
	bool SetRenderTarget(RenderTarget target, bool clearTarget);
	bool SetRenderTarget(RenderTarget target);
	void SetTransform(TransformationState state, Matrix4f^ mat);

	void UpdateAllOcclusionQueries(bool block);
	void UpdateAllOcclusionQueries();
	void UpdateOcclusionQuery(Scene::SceneNode^ node, bool block);
	void UpdateOcclusionQuery(Scene::SceneNode^ node);

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

	static VideoDriver^ Wrap(video::IVideoDriver* ref);
	VideoDriver(video::IVideoDriver* ref);

	video::IVideoDriver* m_VideoDriver;

private:

	unsigned int calculatePrimitiveCount(unsigned int indexCount, Scene::PrimitiveType pType);
};

} // end namespace Video
} // end namespace IrrlichtLime