#include "stdafx.h"
#include "Attributes.h"
#include "GPUProgrammingServices.h"
#include "Image.h"
#include "ImageLoader.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Material.h"
#include "MaterialRenderer.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "MeshManipulator.h"
#include "ReadFile.h"
#include "ReferenceCounted.h"
#include "RenderTarget.h"
#include "SceneNode.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VideoDriver.h"
#include "WriteFile.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

VideoDriver^ VideoDriver::Wrap(video::IVideoDriver* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew VideoDriver(ref);
}

VideoDriver::VideoDriver(video::IVideoDriver* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_VideoDriver = ref;
}

int VideoDriver::AddDynamicLight(Light^ light)
{
	LIME_ASSERT(DynamicLightCount + 1 < MaxDynamicLightCount);
	LIME_ASSERT(light != nullptr);

	return m_VideoDriver->addDynamicLight(*light->m_NativeValue);
}

MaterialType VideoDriver::AddMaterialRenderer(MaterialRenderer^ renderer, String^ name)
{
	return (MaterialType)m_VideoDriver->addMaterialRenderer(
		LIME_SAFEREF(renderer, m_MaterialRenderer),
		LIME_SAFESTRINGTOSTRINGC_C_STR(name));
}

MaterialType VideoDriver::AddMaterialRenderer(MaterialRenderer^ renderer)
{
	return (MaterialType)m_VideoDriver->addMaterialRenderer(
		LIME_SAFEREF(renderer, m_MaterialRenderer));
}

void VideoDriver::AddOcclusionQuery(Scene::SceneNode^ node, Scene::Mesh^ mesh)
{
	m_VideoDriver->addOcclusionQuery(LIME_SAFEREF(node, m_SceneNode), LIME_SAFEREF(mesh, m_Mesh));
}

void VideoDriver::AddOcclusionQuery(Scene::SceneNode^ node)
{
	m_VideoDriver->addOcclusionQuery(LIME_SAFEREF(node, m_SceneNode));
}

RenderTarget^ VideoDriver::AddRenderTarget()
{
	video::IRenderTarget* r = m_VideoDriver->addRenderTarget();
	return RenderTarget::Wrap(r);
}

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Di^ size, String^ name, Video::ColorFormat format)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);
	LIME_ASSERT(name != nullptr);

	video::ITexture* t = m_VideoDriver->addRenderTargetTexture(
		(core::dimension2du&) *size->m_NativeValue,
		Lime::StringToPath(name),
		(video::ECOLOR_FORMAT) format);

	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Di^ size, String^ name)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);
	LIME_ASSERT(name != nullptr);

	video::ITexture* t = m_VideoDriver->addRenderTargetTexture(
		(core::dimension2du&) *size->m_NativeValue,
		Lime::StringToPath(name));

	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Di^ size)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);

	video::ITexture* t = m_VideoDriver->addRenderTargetTexture((core::dimension2du&)*size->m_NativeValue);
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(Dimension2Di^ size, String^ name, Video::ColorFormat format)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(name->Length > 0);

	video::ITexture* t = m_VideoDriver->addTexture(
		(core::dimension2du&) *size->m_NativeValue,
		Lime::StringToPath(name),
		(video::ECOLOR_FORMAT) format);

	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(Dimension2Di^ size, String^ name)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(name->Length > 0);

	video::ITexture* t = m_VideoDriver->addTexture(
		(core::dimension2du&) *size->m_NativeValue,
		Lime::StringToPath(name));

	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(String^ name, Image^ image)
{
	LIME_ASSERT(name != nullptr);

	video::ITexture* t = m_VideoDriver->addTexture(Lime::StringToPath(name), LIME_SAFEREF(image, m_Image));
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTextureCubemap(String^ name, Image^ imagePosX, Image^ imageNegX, Image^ imagePosY, Image^ imageNegY, Image^ imagePosZ, Image^ imageNegZ)
{
	LIME_ASSERT(name != nullptr);

	video::ITexture* t = m_VideoDriver->addTextureCubemap(
		Lime::StringToPath(name),
		LIME_SAFEREF(imagePosX, m_Image),
		LIME_SAFEREF(imageNegX, m_Image),
		LIME_SAFEREF(imagePosY, m_Image),
		LIME_SAFEREF(imageNegY, m_Image),
		LIME_SAFEREF(imagePosZ, m_Image),
		LIME_SAFEREF(imageNegZ, m_Image));
	return Texture::Wrap(t);
}

#pragma warning (push)	//hide the deprecated warning
#pragma warning (disable: 4996)
bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Color color, Video::ExposedVideoData^ videoData, Nullable<Recti> sourceRect)
{
	LIME_ASSERT(videoData != nullptr);

	core::rect<s32>* sourceRectNP = nullptr;
	core::rect<s32> sourceRectN;
	if (sourceRect.HasValue)
	{
		sourceRectN = sourceRect.Value;
		sourceRectNP = &sourceRectN;
	}

	return m_VideoDriver->beginScene(backBuffer, zBuffer, color, *videoData->m_NativeValue, sourceRectNP);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Color color, Video::ExposedVideoData^ videoData)
{
	LIME_ASSERT(videoData != nullptr);

	return m_VideoDriver->beginScene(backBuffer, zBuffer, color, *videoData->m_NativeValue);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Color color)
{
	return m_VideoDriver->beginScene(backBuffer, zBuffer, color);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer)
{
	return m_VideoDriver->beginScene(backBuffer, zBuffer);
}
#pragma warning (pop)

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag, Color clearColor, float clearDepth, unsigned char clearStencil, Video::ExposedVideoData^ videoData, Nullable<Recti> sourceRect)
{
	LIME_ASSERT(videoData != nullptr);

	return m_VideoDriver->beginScene(
		(u16)clearFlag,
		clearColor,
		clearDepth,
		clearStencil,
		*videoData->m_NativeValue,
		LIME_NULLABLE(sourceRect));
}

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag, Color clearColor, float clearDepth, unsigned char clearStencil, Video::ExposedVideoData^ videoData)
{
	LIME_ASSERT(videoData != nullptr);

	return m_VideoDriver->beginScene(
		(u16)clearFlag,
		clearColor,
		clearDepth,
		clearStencil,
		*videoData->m_NativeValue);
}

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag, Color clearColor, float clearDepth, unsigned char clearStencil)
{
	return m_VideoDriver->beginScene(
		(u16)clearFlag,
		clearColor,
		clearDepth,
		clearStencil);
}

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag, Color clearColor, float clearDepth)
{
	return m_VideoDriver->beginScene(
		(u16)clearFlag,
		clearColor,
		clearDepth);
}

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag, Color clearColor)
{
	return m_VideoDriver->beginScene(
		(u16)clearFlag,
		clearColor);
}

bool VideoDriver::BeginScene(ClearBufferFlag clearFlag)
{
	return m_VideoDriver->beginScene(
		(u16)clearFlag);
}

bool VideoDriver::BeginScene()
{
	return m_VideoDriver->beginScene();
}

bool VideoDriver::CheckDriverReset()
{
	return m_VideoDriver->checkDriverReset();
}

void VideoDriver::ClearBuffers(ClearBufferFlag flag, Color color, float depth, unsigned char stencil)
{
	m_VideoDriver->clearBuffers(
		(u16)flag,
		color,
		depth,
		stencil);
}

void VideoDriver::ClearBuffers(ClearBufferFlag flag, Color color, float depth)
{
	m_VideoDriver->clearBuffers(
		(u16)flag,
		color,
		depth);
}

void VideoDriver::ClearBuffers(ClearBufferFlag flag, Color color)
{
	m_VideoDriver->clearBuffers(
		(u16)flag,
		color);
}

void VideoDriver::ClearBuffers(ClearBufferFlag flag)
{
	m_VideoDriver->clearBuffers(
		(u16)flag);
}

void VideoDriver::ClearBuffers(bool backBuffer, bool depthBuffer, bool stencilBuffer, Color color)
{
#pragma warning (push)
#pragma warning (disable: 4996)	//marked as deprecated, we use a ObsoleteAttribute, so warning here is disabled
	m_VideoDriver->clearBuffers(
		backBuffer,
		depthBuffer,
		stencilBuffer,
		color);
#pragma warning (pop)
}

void VideoDriver::ClearZBuffer()
{
#pragma warning (push)
#pragma warning (disable: 4996)	//marked as deprecated, we use a ObsoleteAttribute, so warning here is disabled
	m_VideoDriver->clearZBuffer();
#pragma warning (pop)
}

IO::Attributes^ VideoDriver::CreateAttributesFromMaterial(Material^ material)
{
	LIME_ASSERT(material != nullptr);

	io::IAttributes* a = m_VideoDriver->createAttributesFromMaterial(*material->m_NativeValue);
	return IO::Attributes::Wrap(a);
}

IO::Attributes^ VideoDriver::CreateAttributesFromMaterial(Material^ material, IO::AttributeReadWriteOptions^ options)
{
	LIME_ASSERT(material != nullptr);

	io::SAttributeReadWriteOptions* o = IO::AttributeReadWriteOptions::Allocate_SAttributeReadWriteOptions(options);
	io::IAttributes* a = m_VideoDriver->createAttributesFromMaterial(*material->m_NativeValue, o);
	IO::AttributeReadWriteOptions::Free_SAttributeReadWriteOptions(o);

	return IO::Attributes::Wrap(a);
}

Image^ VideoDriver::CreateImage(Texture^ texture, Vector2Di pos, Dimension2Di^ size)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width > 0);
	LIME_ASSERT(size->Height > 0);

	video::IImage* i = m_VideoDriver->createImage(
		LIME_SAFEREF(texture, m_Texture),
		pos,
		(core::dimension2du&)*size->m_NativeValue);

	return Image::Wrap(i);
}

Image^ VideoDriver::CreateImage(Texture^ texture)
{
	LIME_ASSERT(texture != nullptr);

	video::IImage* i = m_VideoDriver->createImage(
		LIME_SAFEREF(texture, m_Texture),
		core::vector2di(),
		(core::dimension2du&)*texture->Size->m_NativeValue);

	return Image::Wrap(i);
}

Image^ VideoDriver::CreateImage(Video::ColorFormat format, Dimension2Di^ size)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width > 0);
	LIME_ASSERT(size->Height > 0);

	video::IImage* i = m_VideoDriver->createImage(
		(video::ECOLOR_FORMAT)format,
		(core::dimension2du&)*size->m_NativeValue);

	return Image::Wrap(i);
}

Image^ VideoDriver::CreateImage(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	video::IImage* i = m_VideoDriver->createImageFromFile(Lime::StringToPath(filename));
	return Image::Wrap(i);
}

Image^ VideoDriver::CreateImage(IO::ReadFile^ file)
{
	LIME_ASSERT(file != nullptr);

	video::IImage* i = m_VideoDriver->createImageFromFile(LIME_SAFEREF(file, m_ReadFile));
	return Image::Wrap(i);
}

array<Image^>^ VideoDriver::CreateImagesFromFile(String^ filename, [Out] TextureType% type)
{
	LIME_ASSERT(filename != nullptr);

	E_TEXTURE_TYPE retType;

	core::array<IImage*> imagesNative = m_VideoDriver->createImagesFromFile(Lime::StringToPath(filename), &retType);
	type = (TextureType)retType;

	array<Image^>^ images = gcnew array<Image^>(imagesNative.size());
	for (unsigned int i = 0; i < imagesNative.size(); i++)
		images[i] = Image::Wrap(imagesNative[i]);

	return images;
}

array<Image^>^ VideoDriver::CreateImagesFromFile(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	core::array<IImage*> imagesNative = m_VideoDriver->createImagesFromFile(Lime::StringToPath(filename));

	array<Image^>^ images = gcnew array<Image^>(imagesNative.size());
	for (unsigned int i = 0; i < imagesNative.size(); i++)
		images[i] = Image::Wrap(imagesNative[i]);

	return images;
}

array<Image^>^ VideoDriver::CreateImagesFromFile(IO::ReadFile^ file, [Out] TextureType% type)
{
	LIME_ASSERT(file != nullptr);

	E_TEXTURE_TYPE retType;

	core::array<IImage*> imagesNative = m_VideoDriver->createImagesFromFile(file->m_ReadFile, &retType);
	type = (TextureType)retType;

	array<Image^>^ images = gcnew array<Image^>(imagesNative.size());
	for (unsigned int i = 0; i < imagesNative.size(); i++)
		images[i] = Image::Wrap(imagesNative[i]);

	return images;
}

array<Image^>^ VideoDriver::CreateImagesFromFile(IO::ReadFile^ file)
{
	LIME_ASSERT(file != nullptr);

	core::array<IImage*> imagesNative = m_VideoDriver->createImagesFromFile(file->m_ReadFile);

	array<Image^>^ images = gcnew array<Image^>(imagesNative.size());
	for (unsigned int i = 0; i < imagesNative.size(); i++)
		images[i] = Image::Wrap(imagesNative[i]);

	return images;
}

Image^ VideoDriver::CreateScreenShot()
{
	video::IImage* i = m_VideoDriver->createScreenShot();
	return Image::Wrap(i);
}

Image^ VideoDriver::CreateScreenShot(Video::ColorFormat format)
{
	video::IImage* i = m_VideoDriver->createScreenShot(
		(video::ECOLOR_FORMAT)format);

	return Image::Wrap(i);
}

Image^ VideoDriver::CreateScreenShot(Video::ColorFormat format, Video::RenderTargetType target)
{
	video::IImage* i = m_VideoDriver->createScreenShot(
		(video::ECOLOR_FORMAT)format,
		(video::E_RENDER_TARGET)target);

	return Image::Wrap(i);
}

void VideoDriver::DeleteAllDynamicLights()
{
	m_VideoDriver->deleteAllDynamicLights();
}

void VideoDriver::DisableFeature(VideoDriverFeature feature, bool flag)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature, flag);
}

void VideoDriver::DisableFeature(VideoDriverFeature feature)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature);
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti destRect, Recti sourceRect, Nullable<Recti> clipRect, List<Color>^ colors, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(texture != nullptr);

	video::SColor* colorList = nullptr;
	if (colors != nullptr)
	{
		LIME_ASSERT(colors->Count == 4);
		colorList = new video::SColor[4];
		for (int i = 0; i < 4; i++)
			colorList[i] = colors[i];
	}
	
	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destRect,
		sourceRect,
		LIME_NULLABLE(clipRect),
		colorList,
		useAlphaChannelOfTexture);

	if (colorList != nullptr)
		delete[] colorList;
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti destRect, Recti sourceRect, Nullable<Recti> clipRect, List<Color>^ colors)
{
	LIME_ASSERT(texture != nullptr);

	video::SColor* colorList = nullptr;
	if (colors != nullptr)
	{
		LIME_ASSERT(colors->Count == 4);
		colorList = new video::SColor[4];
		for (int i = 0; i < 4; i++)
			colorList[i] = colors[i];
	}

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destRect,
		sourceRect,
		LIME_NULLABLE(clipRect),
		colorList);

	if (colorList != nullptr)
		delete[] colorList;
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti destRect, Recti sourceRect, Nullable<Recti> clipRect)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destRect,
		sourceRect,
		LIME_NULLABLE(clipRect));
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti destRect, Recti sourceRect)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destRect,
		sourceRect);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di destPos, Recti sourceRect, Nullable<Recti> clipRect, Color color, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destPos,
		sourceRect,
		LIME_NULLABLE(clipRect),
		color,
		useAlphaChannelOfTexture);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di destPos, Recti sourceRect, Nullable<Recti> clipRect, Color color)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destPos,
		sourceRect,
		LIME_NULLABLE(clipRect),
		color);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di destPos, Recti sourceRect, Nullable<Recti> clipRect)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destPos,
		sourceRect,
		LIME_NULLABLE(clipRect));
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di destPos, Recti sourceRect)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destPos,
		sourceRect);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di destPos)
{
	LIME_ASSERT(texture != nullptr);

	m_VideoDriver->draw2DImage(
		texture->m_Texture,
		destPos);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, List<Vector2Di>^ positions, List<Recti>^ sourceRects, Nullable<Recti> clipRect,
	Color color, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(positions != nullptr);
	LIME_ASSERT(positions->Count > 0);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(positions->Count == sourceRects->Count);

	core::array<core::vector2di> p;
	for (int i = 0; i < positions->Count; i++)
	{
		p.push_back(positions[i]);
	}

	core::array<core::recti> s;
	for (int i = 0; i < sourceRects->Count; i++)
	{
		s.push_back(sourceRects[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		p,
		s,
		LIME_NULLABLE(clipRect),
		color,
		useAlphaChannelOfTexture);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, List<Vector2Di>^ positions, List<Recti>^ sourceRects, Nullable<Recti> clipRect,
	Color color)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(positions != nullptr);
	LIME_ASSERT(positions->Count > 0);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(positions->Count == sourceRects->Count);

	core::array<core::vector2di> p;
	for (int i = 0; i < positions->Count; i++)
	{
		p.push_back(positions[i]);
	}

	core::array<core::recti> s;
	for (int i = 0; i < sourceRects->Count; i++)
	{
		s.push_back(sourceRects[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		p,
		s,
		LIME_NULLABLE(clipRect),
		color);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, List<Vector2Di>^ positions, List<Recti>^ sourceRects, Nullable<Recti> clipRect)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(positions != nullptr);
	LIME_ASSERT(positions->Count > 0);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(positions->Count == sourceRects->Count);

	core::array<core::vector2di> p;
	for (int i = 0; i < positions->Count; i++)
	{
		p.push_back(positions[i]);
	}

	core::array<core::recti> s;
	for (int i = 0; i < sourceRects->Count; i++)
	{
		s.push_back(sourceRects[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		p,
		s,
		LIME_NULLABLE(clipRect));
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, List<Vector2Di>^ positions, List<Recti>^ sourceRects)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(positions != nullptr);
	LIME_ASSERT(positions->Count > 0);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(positions->Count == sourceRects->Count);

	core::array<core::vector2di> p;
	for (int i = 0; i < positions->Count; i++)
	{
		p.push_back(positions[i]);
	}

	core::array<core::recti> s;
	for (int i = 0; i < sourceRects->Count; i++)
	{
		s.push_back(sourceRects[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		p,
		s);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, Vector2Di position, List<Recti>^ sourceRects, List<int>^ indices,
	int kerningWidth, Nullable<Recti> clipRect, Color color, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	int sc = sourceRects->Count;

	core::array<core::recti> s;
	for (int i = 0; i < sc; i++)
	{
		s.push_back(sourceRects[i]);
	}

	core::array<s32> j;
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] < sc);
		j.push_back(indices[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		position,
		s,
		j,
		kerningWidth,
		LIME_NULLABLE(clipRect),
		color,
		useAlphaChannelOfTexture);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, Vector2Di position, List<Recti>^ sourceRects, List<int>^ indices,
	int kerningWidth, Nullable<Recti> clipRect, Color color)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	int sc = sourceRects->Count;

	core::array<core::recti> s;
	for (int i = 0; i < sc; i++)
	{
		s.push_back(sourceRects[i]);
	}

	core::array<s32> j;
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] < sc);
		j.push_back(indices[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		position,
		s,
		j,
		kerningWidth,
		LIME_NULLABLE(clipRect),
		color);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, Vector2Di position, List<Recti>^ sourceRects, List<int>^ indices,
	int kerningWidth, Nullable<Recti> clipRect)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	int sc = sourceRects->Count;

	core::array<core::recti> s;
	for (int i = 0; i < sc; i++)
	{
		s.push_back(sourceRects[i]);
	}

	core::array<s32> j;
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] < sc);
		j.push_back(indices[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		position,
		s,
		j,
		kerningWidth,
		LIME_NULLABLE(clipRect));
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, Vector2Di position, List<Recti>^ sourceRects, List<int>^ indices,
	int kerningWidth)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	int sc = sourceRects->Count;

	core::array<core::recti> s;
	for (int i = 0; i < sc; i++)
	{
		s.push_back(sourceRects[i]);
	}

	core::array<s32> j;
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] < sc);
		j.push_back(indices[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		position,
		s,
		j,
		kerningWidth);
}

void VideoDriver::Draw2DImageBatch(Texture^ texture, Vector2Di position, List<Recti>^ sourceRects, List<int>^ indices)
{
	LIME_ASSERT(texture != nullptr);
	LIME_ASSERT(sourceRects != nullptr);
	LIME_ASSERT(sourceRects->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	int sc = sourceRects->Count;

	core::array<core::recti> s;
	for (int i = 0; i < sc; i++)
	{
		s.push_back(sourceRects[i]);
	}

	core::array<s32> j;
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] < sc);
		j.push_back(indices[i]);
	}

	m_VideoDriver->draw2DImageBatch(
		texture->m_Texture,
		position,
		s,
		j);
}

void VideoDriver::Draw2DLine(int x1, int y1, int x2, int y2, Color color)
{
	m_VideoDriver->draw2DLine(
		core::vector2di(x1, y1),
		core::vector2di(x2, y2),
		color);
}

void VideoDriver::Draw2DLine(Vector2Di start, Vector2Di end, Color color)
{
	m_VideoDriver->draw2DLine(
		start,
		end,
		color);
}

void VideoDriver::Draw2DPolygon(int x, int y, float radius, Color color, int vertexCount)
{
	LIME_ASSERT(vertexCount >= 2);

	m_VideoDriver->draw2DPolygon(
		core::vector2di(x, y),
		radius,
		color,
		vertexCount);
}

void VideoDriver::Draw2DPolygon(Vector2Di center, float radius, Color color, int vertexCount)
{
	LIME_ASSERT(vertexCount >= 2);

	m_VideoDriver->draw2DPolygon(
		center,
		radius,
		color,
		vertexCount);
}

void VideoDriver::Draw2DRectangle(Recti pos, Color colorLeftUp, Color colorRightUp, Color colorLeftDown, Color colorRightDown, Nullable<Recti> clip)
{
	m_VideoDriver->draw2DRectangle(
		pos,
		colorLeftUp,
		colorRightUp,
		colorLeftDown,
		colorRightDown,
		LIME_NULLABLE(clip));
}

void VideoDriver::Draw2DRectangle(Recti pos, Color colorLeftUp, Color colorRightUp, Color colorLeftDown, Color colorRightDown)
{
	m_VideoDriver->draw2DRectangle(
		pos,
		colorLeftUp,
		colorRightUp,
		colorLeftDown,
		colorRightDown);
}

void VideoDriver::Draw2DRectangle(Recti pos, Color color, Nullable<Recti> clip)
{
	m_VideoDriver->draw2DRectangle(
		color,
		pos,
		LIME_NULLABLE(clip));
}

void VideoDriver::Draw2DRectangle(Recti pos, Color color)
{
	m_VideoDriver->draw2DRectangle(
		color,
		pos);
}

void VideoDriver::Draw2DRectangle(int x1, int y1, int x2, int y2, Color color)
{
	m_VideoDriver->draw2DRectangle(
		color,
		core::recti(x1, y1, x2, y2));
}

void VideoDriver::Draw2DRectangleOutline(Recti pos, Color color)
{
	m_VideoDriver->draw2DRectangleOutline(
		pos,
		color);
}

void VideoDriver::Draw2DRectangleOutline(int x1, int y1, int x2, int y2, Color color)
{
	m_VideoDriver->draw2DRectangleOutline(
		core::recti(x1, y1, x2, y2),
		color);
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::Draw2DVertexPrimitiveList(array<T>^ vertices, array<unsigned short>^ indices16bit, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(vertices->Length <= 0xFFFF);
	LIME_ASSERT(indices16bit != nullptr);

	if (vertices->Length == 0 || indices16bit->Length == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(indices16bit->Length, pType);

	pin_ptr<void> vertexList = &vertices[0];
	VertexType type = vertices->Length > 0 ? vertices[0]->Type : VertexType::Standard;
	/*S3DVertex* vertexList = new S3DVertex[vertices->Length];
	for (int i = 0; i < vertices->Length; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}*/

	pin_ptr<u16> indexList = &indices16bit[0];
	//u16* indexList = new u16[indices16bit->Length];
	//Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(indexList), indices16bit->Length);

	m_VideoDriver->draw2DVertexPrimitiveList(
		vertexList,
		vertices->Length,
		indexList,
		primCount,
		(E_VERTEX_TYPE)type,
		(scene::E_PRIMITIVE_TYPE)pType,
		EIT_16BIT);

	//delete[] indexList;
	//delete[] vertexList;
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::Draw2DVertexPrimitiveList(array<T>^ vertices, array<unsigned short>^ indices16bit)
{
	Draw2DVertexPrimitiveList(vertices, indices16bit, Scene::PrimitiveType::Triangles);
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::Draw2DVertexPrimitiveList(array<T>^ vertices, array<unsigned int>^ indices32bit, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(indices32bit != nullptr);

	if (vertices->Length == 0 || indices32bit->Length == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(indices32bit->Length, pType);

	pin_ptr<void> vertexList = &vertices[0];
	VertexType type = vertices->Length > 0 ? vertices[0]->Type : VertexType::Standard;
	/*S3DVertex* vertexList = new S3DVertex[vertices->Length];
	for (int i = 0; i < vertices->Length; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}*/

	pin_ptr<u32> indexList = &indices32bit[0];
	//u32* indexList = new u32[indices32bit->Length];
	//Marshal::Copy((array<int>^)indices32bit, 0, IntPtr(indexList), indices32bit->Length);

	m_VideoDriver->draw2DVertexPrimitiveList(
		vertexList,
		vertices->Length,
		indexList,
		primCount,
		(E_VERTEX_TYPE)type,
		(scene::E_PRIMITIVE_TYPE)pType,
		EIT_32BIT);

	//delete[] indexList;
	//delete[] vertexList;
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::Draw2DVertexPrimitiveList(array<T>^ vertices, array<unsigned int>^ indices32bit)
{
	Draw2DVertexPrimitiveList(vertices, indices32bit, Scene::PrimitiveType::Triangles);
}

void VideoDriver::Draw2DVertexPrimitiveList(Scene::VertexBuffer^ vertexBuffer, Scene::IndexBuffer^ indexBuffer, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertexBuffer != nullptr);
	LIME_ASSERT(indexBuffer != nullptr);

	scene::IVertexBuffer* vb = vertexBuffer->m_VertexBuffer;
	scene::IIndexBuffer* ib = indexBuffer->m_IndexBuffer;

	if (vb->size() == 0 || ib->size() == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(ib->size(), pType);

	m_VideoDriver->draw2DVertexPrimitiveList(
		vb->pointer(),
		vb->size(),
		ib->pointer(),
		primCount,
		vb->getType(),
		(scene::E_PRIMITIVE_TYPE)pType,
		ib->getType());
}

void VideoDriver::Draw2DVertexPrimitiveList(Scene::VertexBuffer^ vertexBuffer, Scene::IndexBuffer^ indexBuffer)
{
	Draw2DVertexPrimitiveList(vertexBuffer, indexBuffer, Scene::PrimitiveType::Triangles);
}

void VideoDriver::Draw3DBox(AABBox^ box, Color color)
{
	LIME_ASSERT(box != nullptr);

	m_VideoDriver->draw3DBox(
		*box->m_NativeValue,
		color);
}

void VideoDriver::Draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2, Color color)
{
	m_VideoDriver->draw3DLine(
		core::vector3df(x1, y1, z1),
		core::vector3df(x2, y2, z2),
		color);
}

void VideoDriver::Draw3DLine(Vector3Df start, Vector3Df end, Color color)
{
	m_VideoDriver->draw3DLine(
		start,
		end,
		color);
}

void VideoDriver::Draw3DLine(Line3Df line, Color color)
{
	m_VideoDriver->draw3DLine(
		line.Start,
		line.End,
		color);
}

void VideoDriver::Draw3DTriangle(Vector3Df pointA, Vector3Df pointB, Vector3Df pointC, Color color)
{
	m_VideoDriver->draw3DTriangle(
		core::triangle3df(pointA, pointB, pointC),
		color);
}

void VideoDriver::Draw3DTriangle(Triangle3Df triangle, Color color)
{
	m_VideoDriver->draw3DTriangle(
		triangle,
		color);
}

void VideoDriver::DrawMeshBuffer(Scene::MeshBuffer^ mb)
{
	m_VideoDriver->drawMeshBuffer(LIME_SAFEREF(mb, m_MeshBuffer));
}

void VideoDriver::DrawMeshBufferNormals(Scene::MeshBuffer^ mb, float length, Color color)
{
	m_VideoDriver->drawMeshBufferNormals(
		LIME_SAFEREF(mb, m_MeshBuffer),
		length,
		color);
}

void VideoDriver::DrawMeshBufferNormals(Scene::MeshBuffer^ mb, float length)
{
	m_VideoDriver->drawMeshBufferNormals(
		LIME_SAFEREF(mb, m_MeshBuffer),
		length);
}

void VideoDriver::DrawMeshBufferNormals(Scene::MeshBuffer^ mb)
{
	m_VideoDriver->drawMeshBufferNormals(LIME_SAFEREF(mb, m_MeshBuffer));
}

void VideoDriver::DrawPixel(int x, int y, Color color)
{
	LIME_ASSERT(x >= 0 && x < CurrentRenderTargetSize->Width);
	LIME_ASSERT(y >= 0 && y < CurrentRenderTargetSize->Height);

	m_VideoDriver->drawPixel((unsigned int)x, (unsigned int)y, color);
}

void VideoDriver::DrawStencilShadow(bool clearStencilBuffer, Color leftUpEdge, Color rightUpEdge, Color leftDownEdge, Color rightDownEdge)
{
	m_VideoDriver->drawStencilShadow(
		clearStencilBuffer,
		leftUpEdge,
		rightUpEdge,
		leftDownEdge,
		rightDownEdge);
}

void VideoDriver::DrawStencilShadow(bool clearStencilBuffer, Color allEdges)
{
	m_VideoDriver->drawStencilShadow(
		clearStencilBuffer,
		allEdges,
		allEdges,
		allEdges,
		allEdges);
}

void VideoDriver::DrawStencilShadow(bool clearStencilBuffer)
{
	m_VideoDriver->drawStencilShadow(clearStencilBuffer);
}

void VideoDriver::DrawStencilShadow()
{
	m_VideoDriver->drawStencilShadow();
}

void VideoDriver::DrawStencilShadowVolume(List<Vector3Df>^ triangles, bool zfail, Scene::DebugSceneType debugDataVisible)
{
	LIME_ASSERT(triangles != nullptr);
	LIME_ASSERT(triangles->Count > 0);
	LIME_ASSERT((triangles->Count % 3) == 0);

	core::array<core::vector3df> t;
	for (int i = 0; i < triangles->Count; i++)
	{
		t.push_back(triangles[i]);
	}

	m_VideoDriver->drawStencilShadowVolume(t, zfail, (scene::E_DEBUG_SCENE_TYPE)debugDataVisible);
}

void VideoDriver::DrawStencilShadowVolume(List<Vector3Df>^ triangles, bool zfail)
{
	LIME_ASSERT(triangles != nullptr);
	LIME_ASSERT(triangles->Count > 0);
	LIME_ASSERT((triangles->Count % 3) == 0);

	core::array<core::vector3df> t;
	for (int i = 0; i < triangles->Count; i++)
	{
		t.push_back(triangles[i]);
	}

	m_VideoDriver->drawStencilShadowVolume(t, zfail);
}

void VideoDriver::DrawStencilShadowVolume(List<Vector3Df>^ triangles)
{
	LIME_ASSERT(triangles != nullptr);
	LIME_ASSERT(triangles->Count > 0);
	LIME_ASSERT((triangles->Count % 3) == 0);

	core::array<core::vector3df> t;
	for (int i = 0; i < triangles->Count; i++)
	{
		t.push_back(triangles[i]);
	}

	m_VideoDriver->drawStencilShadowVolume(t);
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::DrawVertexPrimitiveList(array<T>^ vertices, array<unsigned short>^ indices16bit, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(vertices->Length <= 0xFFFF);
	LIME_ASSERT(indices16bit != nullptr);

	if (vertices->Length == 0 || indices16bit->Length == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(indices16bit->Length, pType);

	pin_ptr<void> vertexList = &vertices[0];
	VertexType type = vertices[0]->Type;
	/*video::S3DVertex* vertexList = new S3DVertex[vertices->Length];
	for (int i = 0; i < vertices->Length; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}*/

	pin_ptr<u16> indexList = &indices16bit[0];
	//u16* indexList = new u16[indices16bit->Length];
	//Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(indexList), indices16bit->Length);

	m_VideoDriver->drawVertexPrimitiveList(vertexList, vertices->Length, indexList, primCount,
		(E_VERTEX_TYPE)type, (scene::E_PRIMITIVE_TYPE)pType, EIT_16BIT);

	//delete[] indexList;
	//delete[] vertexList;
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::DrawVertexPrimitiveList(array<T>^ vertices, array<unsigned short>^ indices16bit)
{
	DrawVertexPrimitiveList(vertices, indices16bit, Scene::PrimitiveType::Triangles);
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::DrawVertexPrimitiveList(array<T>^ vertices, array<unsigned int>^ indices32bit, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(indices32bit != nullptr);

	if (vertices->Length == 0 || indices32bit->Length == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(indices32bit->Length, pType);

	pin_ptr<void> vertexList = &vertices[0];
	VertexType type = vertices[0]->Type;
	/*video::S3DVertex* vertexList = new S3DVertex[vertices->Length];
	for (int i = 0; i < vertices->Length; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}*/

	pin_ptr<u32> indexList = &indices32bit[0];
	//u32* indexList = new u32[indices32bit->Length];
	//Marshal::Copy((array<int>^)indices32bit, 0, IntPtr(indexList), indices32bit->Length);

	m_VideoDriver->drawVertexPrimitiveList(vertexList, vertices->Length, indexList, primCount,
		(E_VERTEX_TYPE)type, (scene::E_PRIMITIVE_TYPE)pType, EIT_32BIT);

	//delete[] indexList;
	//delete[] vertexList;
}

generic<typename T>
where T : IVertex3D, value class
void VideoDriver::DrawVertexPrimitiveList(array<T>^ vertices, array<unsigned int>^ indices32bit)
{
	DrawVertexPrimitiveList(vertices, indices32bit, Scene::PrimitiveType::Triangles);
}

void VideoDriver::DrawVertexPrimitiveList(Scene::VertexBuffer^ vertexBuffer, Scene::IndexBuffer^ indexBuffer, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertexBuffer != nullptr);
	LIME_ASSERT(indexBuffer != nullptr);

	scene::IVertexBuffer* vb = vertexBuffer->m_VertexBuffer;
	scene::IIndexBuffer* ib = indexBuffer->m_IndexBuffer;

	if (vb->size() == 0 || ib->size() == 0)
		return;

	unsigned int primCount = calculatePrimitiveCount(ib->size(), pType);

	m_VideoDriver->drawVertexPrimitiveList(
		vb->pointer(),
		vb->size(),
		ib->pointer(),
		primCount,
		vb->getType(),
		(scene::E_PRIMITIVE_TYPE)pType,
		ib->getType());
}

void VideoDriver::DrawVertexPrimitiveList(Scene::VertexBuffer^ vertexBuffer, Scene::IndexBuffer^ indexBuffer)
{
	DrawVertexPrimitiveList(vertexBuffer, indexBuffer, Scene::PrimitiveType::Triangles);
}

void VideoDriver::EnableClipPlane(int index, bool enable)
{
	LIME_ASSERT(index >= 0 && index < (int)Attributes->GetValue("MaxUserClipPlanes"));
	m_VideoDriver->enableClipPlane(index, enable);
}

void VideoDriver::EnableClipPlane(int index)
{
	LIME_ASSERT(index >= 0 && index < (int)Attributes->GetValue("MaxUserClipPlanes"));
	m_VideoDriver->enableClipPlane(index, true);
}

void VideoDriver::EnableMaterial2D(bool enable)
{
	m_VideoDriver->enableMaterial2D(enable);
}

void VideoDriver::EnableMaterial2D()
{
	m_VideoDriver->enableMaterial2D();
}

bool VideoDriver::EndScene()
{
	return m_VideoDriver->endScene();
}

Texture^ VideoDriver::FindTexture(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	video::ITexture* t = m_VideoDriver->findTexture(Lime::StringToPath(filename));
	return Texture::Wrap(t);
}

Light^ VideoDriver::GetDynamicLight(int index)
{
	LIME_ASSERT(index >= 0 && index < DynamicLightCount);
	return gcnew Light((video::SLight*)&m_VideoDriver->getDynamicLight(index)); // !!! cast to non-const
}

ImageLoader^ VideoDriver::GetImageLoader(int index)
{
	LIME_ASSERT(index >= 0 && index < ImageLoaderCount);

	video::IImageLoader* l = m_VideoDriver->getImageLoader(index);
	return ImageLoader::Wrap(l);
}

Material^ VideoDriver::GetMaterialFromAttributes(IO::Attributes^ attributes)
{
	LIME_ASSERT(attributes != nullptr);

	video::SMaterial m;
	m_VideoDriver->fillMaterialStructureFromAttributes(m, LIME_SAFEREF(attributes, m_Attributes));

	return gcnew Material(m);
}

MaterialRenderer^ VideoDriver::GetMaterialRenderer(int index)
{
	LIME_ASSERT(index >= 0 && index < MaterialRendererCount);
	
	video::IMaterialRenderer* r = m_VideoDriver->getMaterialRenderer(index);
	return MaterialRenderer::Wrap(r);
}

MaterialRenderer^ VideoDriver::GetMaterialRenderer(MaterialType material)
{
	video::IMaterialRenderer* r = m_VideoDriver->getMaterialRenderer((unsigned int)material);
	return MaterialRenderer::Wrap(r);
}

String^ VideoDriver::GetMaterialRendererName(int index)
{
	LIME_ASSERT(index >= 0 && index < MaterialRendererCount);

	const char* n = m_VideoDriver->getMaterialRendererName(index);
	return n == nullptr ? nullptr : gcnew String(n);
}

String^ VideoDriver::GetMaterialRendererName(MaterialType material)
{
	const char* n = m_VideoDriver->getMaterialRendererName((unsigned int)material);
	return n == nullptr ? nullptr : gcnew String(n);
}

int VideoDriver::GetOcclusionQueryResult(Scene::SceneNode^ node)
{
	return m_VideoDriver->getOcclusionQueryResult(LIME_SAFEREF(node, m_SceneNode));
}

Texture^ VideoDriver::GetTexture(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	video::ITexture* t = m_VideoDriver->getTexture(Lime::StringToPath(filename));
	return Texture::Wrap(t);
}

Texture^ VideoDriver::GetTexture(IO::ReadFile^ file)
{
	LIME_ASSERT(file != nullptr);

	video::ITexture* t = m_VideoDriver->getTexture(file->m_ReadFile);
	return Texture::Wrap(t);
}

Texture^ VideoDriver::GetTexture(int index)
{
	LIME_ASSERT(index >= 0 && index < TextureCount);

	video::ITexture* t = m_VideoDriver->getTextureByIndex(index);
	return Texture::Wrap(t);
}

bool VideoDriver::GetTextureCreationFlag(TextureCreationFlag flag)
{
	return m_VideoDriver->getTextureCreationFlag((video::E_TEXTURE_CREATION_FLAG)flag);
}

Matrix^ VideoDriver::GetTransform(TransformationState state)
{
	return gcnew Matrix(m_VideoDriver->getTransform((video::E_TRANSFORMATION_STATE)state));
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Color color)
{
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), color);
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Vector2Di colorKeyPixelPos)
{
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), colorKeyPixelPos);
}

void VideoDriver::MakeNormalMapTexture(Texture^ texture, float amplitude)
{
	m_VideoDriver->makeNormalMapTexture(LIME_SAFEREF(texture, m_Texture), amplitude);
}

void VideoDriver::MakeNormalMapTexture(Texture^ texture)
{
	m_VideoDriver->makeNormalMapTexture(LIME_SAFEREF(texture, m_Texture));
}

bool VideoDriver::QueryFeature(VideoDriverFeature feature)
{
	return m_VideoDriver->queryFeature((video::E_VIDEO_DRIVER_FEATURE)feature);
}

bool VideoDriver::QueryTextureFormat(Video::ColorFormat format)
{
	return m_VideoDriver->queryTextureFormat((ECOLOR_FORMAT)format);
}

void VideoDriver::RemoveAllHardwareBuffers()
{
	m_VideoDriver->removeAllHardwareBuffers();
}

void VideoDriver::RemoveAllOcclusionQueries()
{
	m_VideoDriver->removeAllOcclusionQueries();
}

void VideoDriver::RemoveAllRenderTargets()
{
	m_VideoDriver->removeAllRenderTargets();
}

void VideoDriver::RemoveAllTextures()
{
	m_VideoDriver->removeAllTextures();
}

void VideoDriver::RemoveHardwareBuffer(Scene::MeshBuffer^ mb)
{
	m_VideoDriver->removeHardwareBuffer(LIME_SAFEREF(mb, m_MeshBuffer));
}

void VideoDriver::RemoveOcclusionQuery(Scene::SceneNode^ node)
{
	m_VideoDriver->removeOcclusionQuery(LIME_SAFEREF(node, m_SceneNode));
}

void VideoDriver::RemoveRenderTarget(RenderTarget^ target)
{
	m_VideoDriver->removeRenderTarget(LIME_SAFEREF(target, m_RenderTarget));
}

void VideoDriver::RemoveTexture(Texture^ texture)
{
	m_VideoDriver->removeTexture(LIME_SAFEREF(texture, m_Texture));
}

void VideoDriver::RenameTexture(Texture^ texture, String^ newName)
{
	LIME_ASSERT(newName != nullptr);
	m_VideoDriver->renameTexture(LIME_SAFEREF(texture, m_Texture), Lime::StringToPath(newName));
}

void VideoDriver::ResizeNotify(Dimension2Di^ size)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(size->Width >= 0);
	LIME_ASSERT(size->Height >= 0);

	m_VideoDriver->OnResize((core::dimension2du&)*size->m_NativeValue);
}

void VideoDriver::RunAllOcclusionQueries(bool visible)
{
	m_VideoDriver->runAllOcclusionQueries(visible);
}

void VideoDriver::RunAllOcclusionQueries()
{
	m_VideoDriver->runAllOcclusionQueries();
}

void VideoDriver::RunOcclusionQuery(Scene::SceneNode^ node, bool visible)
{
	m_VideoDriver->runOcclusionQuery(LIME_SAFEREF(node, m_SceneNode), visible);
}

void VideoDriver::RunOcclusionQuery(Scene::SceneNode^ node)
{
	m_VideoDriver->runOcclusionQuery(LIME_SAFEREF(node, m_SceneNode));
}

bool VideoDriver::SetClipPlane(int index, Plane3Df^ plane, bool enable)
{
	LIME_ASSERT(index >= 0 && index < (int)Attributes->GetValue("MaxUserClipPlanes"));
	LIME_ASSERT(plane != nullptr);

	return m_VideoDriver->setClipPlane(
		index,
		*plane->m_NativeValue,
		enable);
}

bool VideoDriver::SetClipPlane(int index, Plane3Df^ plane)
{
	LIME_ASSERT(index >= 0 && index < (int)Attributes->GetValue("MaxUserClipPlanes"));
	LIME_ASSERT(plane != nullptr);

	return m_VideoDriver->setClipPlane(
		index,
		*plane->m_NativeValue);
}

void VideoDriver::SetMaterial(Material^ material)
{
	LIME_ASSERT(material != nullptr);
	m_VideoDriver->setMaterial(*material->m_NativeValue);
}

void VideoDriver::SetMaterialRendererName(MaterialType materialType, String^ name)
{
	m_VideoDriver->setMaterialRendererName(
		(video::E_MATERIAL_TYPE) materialType,
		LIME_SAFESTRINGTOSTRINGC_C_STR(name));
}

void VideoDriver::SetMinHardwareBufferVertexCount(int count)
{
	LIME_ASSERT(count >= 0);
	m_VideoDriver->setMinHardwareBufferVertexCount(count);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer, Color color)
{
#pragma warning (push)
#pragma warning (disable: 4996)	//marked as deprecated, we use a ObsoleteAttribute, so warning here is disabled
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture), clearBackBuffer, clearZBuffer, color);
#pragma warning (pop)
}

bool VideoDriver::SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer)
{
#pragma warning (push)
#pragma warning (disable: 4996)	//marked as deprecated, we use a ObsoleteAttribute, so warning here is disabled
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture), clearBackBuffer, clearZBuffer);
#pragma warning (pop)
}

bool VideoDriver::SetRenderTarget(Texture^ texture, ClearBufferFlag clearFlag, Color clearColor,	float clearDepth, unsigned char clearStencil)
{
	return m_VideoDriver->setRenderTarget(
		LIME_SAFEREF(texture, m_Texture),
		(u16)clearFlag,
		clearColor,
		clearDepth,
		clearStencil);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, ClearBufferFlag clearFlag, Color clearColor,	float clearDepth)
{
	return m_VideoDriver->setRenderTarget(
		LIME_SAFEREF(texture, m_Texture),
		(u16)clearFlag,
		clearColor,
		clearDepth);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, ClearBufferFlag clearFlag, Color clearColor)
{
	return m_VideoDriver->setRenderTarget(
		LIME_SAFEREF(texture, m_Texture),
		(u16)clearFlag,
		clearColor);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, ClearBufferFlag clearFlag)
{
	return m_VideoDriver->setRenderTarget(
		LIME_SAFEREF(texture, m_Texture),
		(u16)clearFlag);
}

bool VideoDriver::SetRenderTarget(Texture^ texture)
{
	return m_VideoDriver->setRenderTarget(
		LIME_SAFEREF(texture, m_Texture));
}

bool VideoDriver::SetRenderTargetEx(RenderTarget^ target, ClearBufferFlag clearFlag, Color clearColor, float clearDepth, unsigned char clearStencil)
{
	return m_VideoDriver->setRenderTargetEx(
		LIME_SAFEREF(target, m_RenderTarget),
		(u16)clearFlag,
		clearColor,
		clearDepth,
		clearStencil);
}

bool VideoDriver::SetRenderTargetEx(RenderTarget^ target, ClearBufferFlag clearFlag, Color clearColor, float clearDepth)
{
	return m_VideoDriver->setRenderTargetEx(
		LIME_SAFEREF(target, m_RenderTarget),
		(u16)clearFlag,
		clearColor,
		clearDepth);
}

bool VideoDriver::SetRenderTargetEx(RenderTarget^ target, ClearBufferFlag clearFlag, Color clearColor)
{
	return m_VideoDriver->setRenderTargetEx(
		LIME_SAFEREF(target, m_RenderTarget),
		(u16)clearFlag,
		clearColor);
}

bool VideoDriver::SetRenderTargetEx(RenderTarget^ target, ClearBufferFlag clearFlag)
{
	return m_VideoDriver->setRenderTargetEx(
		LIME_SAFEREF(target, m_RenderTarget),
		(u16)clearFlag);
}

/*
bool VideoDriver::SetRenderTarget(RenderTargetType target, bool clearTarget, bool clearZBuffer, Color color)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget, clearZBuffer, color);
}

bool VideoDriver::SetRenderTarget(RenderTargetType target, bool clearTarget, bool clearZBuffer)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget, clearZBuffer);
}

bool VideoDriver::SetRenderTarget(RenderTargetType target, bool clearTarget)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget);
}

bool VideoDriver::SetRenderTarget(RenderTargetType target)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target);
}
*/
void VideoDriver::SetTextureCreationFlag(TextureCreationFlag flag, bool enabled)
{
	m_VideoDriver->setTextureCreationFlag((video::E_TEXTURE_CREATION_FLAG)flag, enabled);
}

void VideoDriver::SetTransform(TransformationState state, Matrix^ mat)
{
	LIME_ASSERT(mat != nullptr);
	m_VideoDriver->setTransform((video::E_TRANSFORMATION_STATE)state, *mat->m_NativeValue);
}

void VideoDriver::TurnLight(int index, bool turnOn)
{
	LIME_ASSERT(index >= 0 && index < DynamicLightCount);
	m_VideoDriver->turnLightOn(index, turnOn);
}

void VideoDriver::UpdateAllOcclusionQueries(bool block)
{
	m_VideoDriver->updateAllOcclusionQueries(block);
}

void VideoDriver::UpdateAllOcclusionQueries()
{
	m_VideoDriver->updateAllOcclusionQueries();
}

void VideoDriver::UpdateOcclusionQuery(Scene::SceneNode^ node, bool block)
{
	m_VideoDriver->updateOcclusionQuery(LIME_SAFEREF(node, m_SceneNode), block);
}

void VideoDriver::UpdateOcclusionQuery(Scene::SceneNode^ node)
{
	m_VideoDriver->updateOcclusionQuery(LIME_SAFEREF(node, m_SceneNode));
}

bool VideoDriver::WriteImage(Image^ image, String^ filename, unsigned int param)
{
	LIME_ASSERT(image != nullptr);
	LIME_ASSERT(filename != nullptr);

	return m_VideoDriver->writeImageToFile(
		LIME_SAFEREF(image, m_Image),
		Lime::StringToPath(filename),
		param);
}

bool VideoDriver::WriteImage(Image^ image, String^ filename)
{
	LIME_ASSERT(image != nullptr);
	LIME_ASSERT(filename != nullptr);

	return m_VideoDriver->writeImageToFile(
		LIME_SAFEREF(image, m_Image),
		Lime::StringToPath(filename));
}

bool VideoDriver::WriteImage(Image^ image, IO::WriteFile^ file, unsigned int param)
{
	LIME_ASSERT(image != nullptr);
	LIME_ASSERT(file != nullptr);

	return m_VideoDriver->writeImageToFile(
		LIME_SAFEREF(image, m_Image),
		LIME_SAFEREF(file, m_WriteFile),
		param);
}

bool VideoDriver::WriteImage(Image^ image, IO::WriteFile^ file)
{
	LIME_ASSERT(image != nullptr);
	LIME_ASSERT(file != nullptr);

	return m_VideoDriver->writeImageToFile(
		LIME_SAFEREF(image, m_Image),
		LIME_SAFEREF(file, m_WriteFile));
}

IO::Attributes^ VideoDriver::Attributes::get()
{
	const io::IAttributes& a = m_VideoDriver->getDriverAttributes();
	return IO::Attributes::Wrap((io::IAttributes*)&a); // !!! cast to non-const pointer
}

Video::ColorFormat VideoDriver::ColorFormat::get()
{
	return (Video::ColorFormat)m_VideoDriver->getColorFormat();
}

Video::DriverType VideoDriver::DriverType::get()
{
	return (Video::DriverType)m_VideoDriver->getDriverType();
}

Recti VideoDriver::ViewPort::get()
{
	return Recti(m_VideoDriver->getViewPort());
}

void VideoDriver::ViewPort::set(Recti value)
{
	m_VideoDriver->setViewPort(value);
}

Dimension2Di^ VideoDriver::ScreenSize::get()
{
	return gcnew Dimension2Di(m_VideoDriver->getScreenSize());
}

Dimension2Di^ VideoDriver::CurrentRenderTargetSize::get()
{
	return gcnew Dimension2Di(m_VideoDriver->getCurrentRenderTargetSize());
}

Dimension2Di^ VideoDriver::MaxTextureSize::get()
{
	return gcnew Dimension2Di(m_VideoDriver->getMaxTextureSize());
}

List<VideoDriverFeature>^ VideoDriver::FeatureList::get()
{
	List<VideoDriverFeature>^ l = gcnew List<VideoDriverFeature>();

	for each(VideoDriverFeature f in Enum::GetValues(VideoDriverFeature::typeid))
		if (m_VideoDriver->queryFeature((video::E_VIDEO_DRIVER_FEATURE)f))
			l->Add(f);

	return l;
}

Video::Fog^ VideoDriver::Fog::get()
{
	video::SColor c;
	video::E_FOG_TYPE t;
	float s;
	float e;
	float d;
	bool p;
	bool r;

	m_VideoDriver->getFog(c, t, s, e, d, p, r);

	return gcnew Video::Fog(Color(c), (FogType)t, s, e, d, p, r);
}

void VideoDriver::Fog::set(Video::Fog^ value)
{
	LIME_ASSERT(value != nullptr);

	m_VideoDriver->setFog(
		value->Color,
		(video::E_FOG_TYPE)value->Type,
		value->Start,
		value->End,
		value->Density,
		value->PixelFog,
		value->RangeFog);
}

int VideoDriver::FPS::get()
{
	return m_VideoDriver->getFPS();
}

Video::GPUProgrammingServices^ VideoDriver::GPUProgrammingServices::get()
{
	video::IGPUProgrammingServices* s = m_VideoDriver->getGPUProgrammingServices();
	return Video::GPUProgrammingServices::Wrap(s);
}

int VideoDriver::ImageLoaderCount::get()
{
	return m_VideoDriver->getImageLoaderCount();
}

Material^ VideoDriver::Material2D::get()
{
	return Material::Wrap(&m_VideoDriver->getMaterial2D());
}

int VideoDriver::PrimitiveCountDrawn::get()
{
	return m_VideoDriver->getPrimitiveCountDrawn();
}

int VideoDriver::MaxDynamicLightCount::get()
{
	return m_VideoDriver->getMaximalDynamicLightAmount();
}

int VideoDriver::DynamicLightCount::get()
{
	return m_VideoDriver->getDynamicLightCount();
}

Video::ExposedVideoData^ VideoDriver::ExposedVideoData::get()
{
	return gcnew Video::ExposedVideoData(m_VideoDriver->getExposedVideoData());
}

int VideoDriver::MaxPrimitiveCount::get()
{
	return m_VideoDriver->getMaximalPrimitiveCount();
}

int VideoDriver::MaterialRendererCount::get()
{
	return m_VideoDriver->getMaterialRendererCount();
}

Scene::MeshManipulator^ VideoDriver::MeshManipulator::get()
{
	scene::IMeshManipulator* m = m_VideoDriver->getMeshManipulator();
	return Scene::MeshManipulator::Wrap(m);
}

String^ VideoDriver::Name::get()
{
	return gcnew String(m_VideoDriver->getName());
}

int VideoDriver::TextureCount::get()
{
	return m_VideoDriver->getTextureCount();
}

List<Texture^>^ VideoDriver::TextureList::get()
{
	List<Texture^>^ l = gcnew List<Texture^>();

	for (unsigned int i = 0; i < m_VideoDriver->getTextureCount(); i++)
	{
		video::ITexture* t = m_VideoDriver->getTextureByIndex(i);
		l->Add(Texture::Wrap(t));
	}

	return l;
}

String^ VideoDriver::VendorInfo::get()
{
	return gcnew String(m_VideoDriver->getVendorInfo().c_str());
}

String^ VideoDriver::ToString()
{
	return String::Format("VideoDriver: Name={0}; ScreenSize={1}", Name, ScreenSize);
}

unsigned int VideoDriver::calculatePrimitiveCount(unsigned int indexCount, Scene::PrimitiveType pType)
{
	unsigned int c = 0;

	switch (pType)
	{
	case Scene::PrimitiveType::Points:
	case Scene::PrimitiveType::PointSprites:
	case Scene::PrimitiveType::LineLoop:
	case Scene::PrimitiveType::Polygon:
		c = indexCount;
		break;

	case Scene::PrimitiveType::LineStrip:
		LIME_ASSERT(indexCount >= 2);
		c = indexCount - 1;
		break;

	case Scene::PrimitiveType::Lines:
		LIME_ASSERT(indexCount == (indexCount / 2) * 2);
		c = indexCount / 2;
		break;

	case Scene::PrimitiveType::TriangleStrip:
	case Scene::PrimitiveType::TriangleFan:
		LIME_ASSERT(indexCount >= 3);
		c = indexCount - 2;
		break;

	case Scene::PrimitiveType::Triangles:
		LIME_ASSERT(indexCount == (indexCount / 3) * 3);
		c = indexCount / 3;
		break;

	case Scene::PrimitiveType::QuadStrip:
		LIME_ASSERT(indexCount == (indexCount / 2) * 2);
		LIME_ASSERT(indexCount >= 4);
		c = (indexCount - 2) / 2;
		break;

	case Scene::PrimitiveType::Quads:
		LIME_ASSERT(indexCount == (indexCount / 4) * 4);
		c = indexCount / 4;
		break;
	}

	return c;
}

} // end namespace Video
} // end namespace IrrlichtLime