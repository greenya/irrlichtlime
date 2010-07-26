#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene { ref class Mesh; ref class MeshBuffer; ref class MeshManipulator; ref class SceneNode; }
namespace Video {

ref class Image;
ref class ImageLoader;
ref class Light;
ref class Material;
ref class MaterialRenderer;
ref class Texture;

public ref class VideoDriver : ReferenceCounted
{
public:

	static property int MaxClipPlanes { int get() { return 6; } } // "6", because i don't know how detect real number of available clip planes
	// and doc says: "There are at least 6 clipping planes available for the user to set at will. The plane index must be between 0
	// and MaxUserClipPlanes" (MaxUserClipPlanes is a private variable and calculates from device caps internally).

	int AddDynamicLight(Light^ light);

	int AddMaterialRenderer(MaterialRenderer^ renderer, String^ name);
	int AddMaterialRenderer(MaterialRenderer^ renderer);

	Texture^ AddRenderTargetTexture(Dimension2Di^ size, String^ name, Video::ColorFormat format);
	Texture^ AddRenderTargetTexture(Dimension2Di^ size, String^ name);
	Texture^ AddRenderTargetTexture(Dimension2Di^ size);

	Texture^ AddTexture(Dimension2Di^ size, String^ name, Video::ColorFormat format);
	Texture^ AddTexture(Dimension2Di^ size, String^ name);
	Texture^ AddTexture(String^ name, Image^ image); // 3rd argument "void* mipmapData=0" currently not supported

	bool BeginScene(bool backBuffer, bool zBuffer, Color^ color, ExposedVideoData^ videoData, Recti^ sourceRect);
	bool BeginScene(bool backBuffer, bool zBuffer, Color^ color, ExposedVideoData^ videoData);
	bool BeginScene(bool backBuffer, bool zBuffer, Color^ color);
	bool BeginScene(bool backBuffer, bool zBuffer);
	bool BeginScene(bool backBuffer);
	bool BeginScene();

	bool CheckDriverReset();

	void ClearZBuffer();

	Image^ CreateImage(Texture^ texture, Vector2Di^ pos, Dimension2Di^ size);
	Image^ CreateImage(Image^ imageToCopy, Vector2Di^ pos, Dimension2Di^ size);
	Image^ CreateImage(Image^ imageToConvert, Video::ColorFormat format);
	Image^ CreateImage(Video::ColorFormat format, Dimension2Di^ size);
	Image^ CreateImage(String^ filename);

	void CreateOcclusionQuery(Scene::SceneNode^ node, Scene::Mesh^ mesh);
	void CreateOcclusionQuery(Scene::SceneNode^ node);

	Image^ CreateScreenShot();

	void DeleteAllDynamicLights();

	void DisableFeature(VideoDriverFeature feature, bool flag);
	void DisableFeature(VideoDriverFeature feature);

	void Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null, List<Color^>^ colors_or_null, bool useAlphaChannelOfTexture);
	void Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null, List<Color^>^ colors_or_null);
	void Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null);
	void Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect);
	void Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null, Color^ color, bool useAlphaChannelOfTexture);
	void Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null, Color^ color);
	void Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null);
	void Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect);
	void Draw2DImage(Texture^ texture, Vector2Di^ destPos);
	
	void Draw2DLine(int x1, int y1, int x2, int y2, Color^ color);
	void Draw2DLine(Vector2Di^ start, Vector2Di^ end, Color^ color);

	void Draw2DPolygon(Vector2Di^ center, float radius, Color^ color, int vertexCount);

	void Draw2DRectangle(Recti^ pos, Color^ colorLeftUp, Color^ colorRightUp, Color^ colorLeftDown, Color^ colorRightDown, Recti^ clip);
	void Draw2DRectangle(Recti^ pos, Color^ colorLeftUp, Color^ colorRightUp, Color^ colorLeftDown, Color^ colorRightDown);
	void Draw2DRectangle(Recti^ pos, Color^ color, Recti^ clip);
	void Draw2DRectangle(Recti^ pos, Color^ color);

	void Draw2DRectangleOutline(Recti^ pos, Color^ color);

	void Draw2DVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices, Scene::PrimitiveType pType);
	void Draw2DVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices);
	void Draw2DVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices, Scene::PrimitiveType pType);
	void Draw2DVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices);

	void Draw3DBox(AABBox^ box, Color^ color);

	void Draw3DLine(Vector3Df^ start, Vector3Df^ end, Color^ color);
	void Draw3DLine(Line3Df^ line, Color^ color);

	void Draw3DTriangle(Vector3Df^ pointA, Vector3Df^ pointB, Vector3Df^ pointC, Color^ color);
	void Draw3DTriangle(Triangle3Df^ triangle, Color^ color);

	void DrawMeshBuffer(Scene::MeshBuffer^ mb);

	void DrawPixel(int x, int y, Color^ color);

	void DrawStencilShadow(bool clearStencilBuffer, Color^ leftUpEdge, Color^ rightUpEdge, Color^ leftDownEdge, Color^ rightDownEdge);
	void DrawStencilShadow(bool clearStencilBuffer);
	void DrawStencilShadow();

	void DrawStencilShadowVolume(List<Vector3Df^>^ triangles, bool zfail);
	void DrawStencilShadowVolume(List<Vector3Df^>^ triangles);

	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices, Scene::PrimitiveType pType);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices, Scene::PrimitiveType pType);
	void DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices);

	void EnableClipPlane(int index, bool enable);
	void EnableClipPlane(int index);

	void EnableMaterial2D(bool enable);
	void EnableMaterial2D();

	bool EndScene();

	Texture^ FindTexture(String^ filename);

	Light^ GetDynamicLight(int index);

	ImageLoader^ GetImageLoader(int index);

	MaterialRenderer^ GetMaterialRenderer(int index);
	MaterialRenderer^ GetMaterialRenderer(MaterialType material);
	String^ GetMaterialRendererName(int index);
	String^ GetMaterialRendererName(MaterialType material);

	int GetOcclusionQueryResult(Scene::SceneNode^ node);

	Texture^ GetTexture(String^ filename);
	Texture^ GetTexture(int index);

	bool GetTextureCreationFlag(TextureCreationFlag flag);

	Matrix^ GetTransform(TransformationState state);

	void MakeColorKeyTexture(Texture^ texture, Color^ color, bool zeroTexels);
	void MakeColorKeyTexture(Texture^ texture, Color^ color);
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

	bool SetClipPlane(int index, Plane3Df^ plane, bool enable);
	bool SetClipPlane(int index, Plane3Df^ plane);

	void SetMaterial(Material^ material);

	void SetMaterialRendererName(int index, String^ name);

	void SetMinHardwareBufferVertexCount(int count);

	//bool setRenderTarget (const core::array< video::IRenderTarget > &texture, bool clearBackBuffer=true, bool clearZBuffer=true, SColor color=video::SColor(0, 0, 0, 0));
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer, Color^ color);
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer);
	bool SetRenderTarget(Texture^ texture, bool clearBackBuffer);
	bool SetRenderTarget(Texture^ texture);
	bool SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer, Color^ color);
	bool SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer);
	bool SetRenderTarget(RenderTarget target, bool clearTarget);
	bool SetRenderTarget(RenderTarget target);

	void SetTextureCreationFlag(TextureCreationFlag flag, bool enabled);

	void SetTransform(TransformationState state, Matrix^ mat);

	void TurnLight(int index, bool turnOn);

	void UpdateAllOcclusionQueries(bool block);
	void UpdateAllOcclusionQueries();
	void UpdateOcclusionQuery(Scene::SceneNode^ node, bool block);
	void UpdateOcclusionQuery(Scene::SceneNode^ node);

	bool WriteImageToFile(Image^ image, String^ filename, unsigned int param);
	bool WriteImageToFile(Image^ image, String^ filename);

	property Video::ColorFormat ColorFormat { Video::ColorFormat get(); }
	property Dimension2Di^ CurrentRenderTargetSize { Dimension2Di^ get(); }
	property Video::DriverType DriverType { Video::DriverType get(); }
	property int DynamicLightCount { int get(); }
	property Video::ExposedVideoData^ ExposedVideoData { Video::ExposedVideoData^ get(); }
	property Video::Fog^ Fog { Video::Fog^ get(); void set(Video::Fog^ value); }
	property int FPS { int get(); }
	property int ImageLoaderCount { int get(); }
	property Material^ Material2D { Material^ get(); }
	property int MaterialRendererCount { int get(); }
	property int MaximalDynamicLightCount { int get(); }
	property int MaximalPrimitiveCount { int get(); }
	property Dimension2Di^ MaxTextureSize { Dimension2Di^ get(); }
	property Scene::MeshManipulator^ MeshManipulator { Scene::MeshManipulator^ get(); }
	property String^ Name { String^ get(); }
	property int PrimitiveCountDrawn { int get(); }
	property Dimension2Di^ ScreenSize { Dimension2Di^ get(); }
	property int TextureCount { int get(); }
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