#include "stdafx.h"
#include "Image.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "ReferenceCounted.h"
#include "SceneNode.h"
#include "Texture.h"
#include "VideoDriver.h"

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

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Du^ size, String^ name, ColorFormat format)
{
	LIME_ASSERT(size != nullptr);
	video::ITexture* t = m_VideoDriver->addRenderTargetTexture(*size->m_NativeValue, Lime::StringToPath(name), (video::ECOLOR_FORMAT)format);
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Du^ size, String^ name)
{
	LIME_ASSERT(size != nullptr);
	video::ITexture* t = m_VideoDriver->addRenderTargetTexture(*size->m_NativeValue, Lime::StringToPath(name));
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddRenderTargetTexture(Dimension2Du^ size)
{
	LIME_ASSERT(size != nullptr);
	video::ITexture* t = m_VideoDriver->addRenderTargetTexture(*size->m_NativeValue);
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(Dimension2Du^ size, String^ name, ColorFormat format)
{
	LIME_ASSERT(size != nullptr);
	video::ITexture* t = m_VideoDriver->addTexture(*size->m_NativeValue, Lime::StringToPath(name), (video::ECOLOR_FORMAT)format);
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(Dimension2Du^ size, String^ name)
{
	LIME_ASSERT(size != nullptr);
	video::ITexture* t = m_VideoDriver->addTexture(*size->m_NativeValue, Lime::StringToPath(name));
	return Texture::Wrap(t);
}

Texture^ VideoDriver::AddTexture(String^ name, Image^ image)
{
	video::ITexture* t = m_VideoDriver->addTexture(Lime::StringToPath(name), LIME_SAFEREF(image, m_Image));
	return Texture::Wrap(t);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, Video::ExposedVideoData^ videoData, Recti^ sourceRect)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(videoData != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	return m_VideoDriver->beginScene(backBuffer, zBuffer, *color->m_NativeValue, *videoData->m_NativeValue, sourceRect->m_NativeValue);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, Video::ExposedVideoData^ videoData)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(videoData != nullptr);

	return m_VideoDriver->beginScene(backBuffer, zBuffer, *color->m_NativeValue, *videoData->m_NativeValue);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Coloru ^color)
{
	LIME_ASSERT(color != nullptr);
	return m_VideoDriver->beginScene(backBuffer, zBuffer, *color->m_NativeValue);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer)
{
	return m_VideoDriver->beginScene(backBuffer, zBuffer);
}

bool VideoDriver::BeginScene(bool backBuffer)
{
	return m_VideoDriver->beginScene(backBuffer);
}

bool VideoDriver::BeginScene()
{
	return m_VideoDriver->beginScene();
}

bool VideoDriver::CheckDriverReset()
{
	return m_VideoDriver->checkDriverReset();
}

void VideoDriver::CreateOcclusionQuery(Scene::SceneNode^ node, Scene::Mesh^ mesh)
{
	m_VideoDriver->createOcclusionQuery(LIME_SAFEREF(node, m_SceneNode), LIME_SAFEREF(mesh, m_Mesh));
}

void VideoDriver::CreateOcclusionQuery(Scene::SceneNode^ node)
{
	m_VideoDriver->createOcclusionQuery(LIME_SAFEREF(node, m_SceneNode));
}

void VideoDriver::DisableFeature(VideoDriverFeature feature, bool flag)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature, flag);
}

void VideoDriver::DisableFeature(VideoDriverFeature feature)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature);
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null, List<Coloru^>^ colors_or_null, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(destRect != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	video::SColor* colorList = nullptr;
	if (colors_or_null != nullptr)
	{
		LIME_ASSERT(colors_or_null->Count == 4);
		colorList = new video::SColor[4];
		for (int i = 0; i < 4; i++)
			colorList[i] = *colors_or_null[i]->m_NativeValue;
	}

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destRect->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue),
		colorList,
		useAlphaChannelOfTexture);

	if (colorList != nullptr)
		delete colorList;
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null, List<Coloru^>^ colors_or_null)
{
	LIME_ASSERT(destRect != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	video::SColor* colorList = nullptr;
	if (colors_or_null != nullptr)
	{
		LIME_ASSERT(colors_or_null->Count == 4);
		colorList = new video::SColor[4];
		for (int i = 0; i < 4; i++)
			colorList[i] = *colors_or_null[i]->m_NativeValue;
	}

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destRect->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue),
		colorList);

	if (colorList != nullptr)
		delete colorList;
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect, Recti^ clipRect_or_null)
{
	LIME_ASSERT(destRect != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destRect->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue));
}

void VideoDriver::Draw2DImage(Texture^ texture, Recti^ destRect, Recti^ sourceRect)
{
	LIME_ASSERT(destRect != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destRect->m_NativeValue,
		*sourceRect->m_NativeValue);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null, Coloru^ color, bool useAlphaChannelOfTexture)
{
	LIME_ASSERT(destPos != nullptr);
	LIME_ASSERT(sourceRect != nullptr);
	LIME_ASSERT(color != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destPos->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue),
		*color->m_NativeValue,
		useAlphaChannelOfTexture);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null, Coloru^ color)
{
	LIME_ASSERT(destPos != nullptr);
	LIME_ASSERT(sourceRect != nullptr);
	LIME_ASSERT(color != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destPos->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue),
		*color->m_NativeValue);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect, Recti^ clipRect_or_null)
{
	LIME_ASSERT(destPos != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destPos->m_NativeValue,
		*sourceRect->m_NativeValue,
		LIME_SAFEREF(clipRect_or_null, m_NativeValue));
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di^ destPos, Recti^ sourceRect)
{
	LIME_ASSERT(destPos != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destPos->m_NativeValue,
		*sourceRect->m_NativeValue);
}

void VideoDriver::Draw2DImage(Texture^ texture, Vector2Di^ destPos)
{
	LIME_ASSERT(destPos != nullptr);

	m_VideoDriver->draw2DImage(
		LIME_SAFEREF(texture, m_Texture),
		*destPos->m_NativeValue);
}

void VideoDriver::Draw2DRectangle(Recti^ pos, Coloru^ colorLeftUp, Coloru^ colorRightUp, Coloru^ colorLeftDown, Coloru^ colorRightDown, Recti^ clip)
{
	LIME_ASSERT(pos != nullptr);
	LIME_ASSERT(colorLeftUp != nullptr);
	LIME_ASSERT(colorRightUp != nullptr);
	LIME_ASSERT(colorLeftDown != nullptr);
	LIME_ASSERT(colorRightDown != nullptr);
	LIME_ASSERT(clip != nullptr);

	m_VideoDriver->draw2DRectangle(
		*pos->m_NativeValue,
		*colorLeftUp->m_NativeValue,
		*colorRightUp->m_NativeValue,
		*colorLeftDown->m_NativeValue,
		*colorRightDown->m_NativeValue,
		clip->m_NativeValue);
}

void VideoDriver::Draw2DRectangle(Recti^ pos, Coloru^ colorLeftUp, Coloru^ colorRightUp, Coloru^ colorLeftDown, Coloru^ colorRightDown)
{
	LIME_ASSERT(pos != nullptr);
	LIME_ASSERT(colorLeftUp != nullptr);
	LIME_ASSERT(colorRightUp != nullptr);
	LIME_ASSERT(colorLeftDown != nullptr);
	LIME_ASSERT(colorRightDown != nullptr);

	m_VideoDriver->draw2DRectangle(
		*pos->m_NativeValue,
		*colorLeftUp->m_NativeValue,
		*colorRightUp->m_NativeValue,
		*colorLeftDown->m_NativeValue,
		*colorRightDown->m_NativeValue);
}

void VideoDriver::Draw2DRectangle(Coloru^ color, Recti^ pos, Recti^ clip)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(pos != nullptr);
	LIME_ASSERT(clip != nullptr);
	
	m_VideoDriver->draw2DRectangle(
		*color->m_NativeValue,
		*pos->m_NativeValue,
		clip->m_NativeValue);
}

void VideoDriver::Draw2DRectangle(Coloru^ color, Recti^ pos)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(pos != nullptr);
	
	m_VideoDriver->draw2DRectangle(
		*color->m_NativeValue,
		*pos->m_NativeValue);
}

void VideoDriver::DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(vertices->Count > 0);
	LIME_ASSERT(vertices->Count <= 0xFFFF);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	unsigned int primCount = calculatePrimitiveCount(indices->Count, pType);

	S3DVertex* vertexList = new S3DVertex[vertices->Count];
	for (int i = 0; i < vertices->Count; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}

	u16* indexList = new u16[indices->Count];
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] >= 0);
		indexList[i] = indices[i];
	}

	m_VideoDriver->drawVertexPrimitiveList(vertexList, vertices->Count, indexList, primCount,
		EVT_STANDARD, (scene::E_PRIMITIVE_TYPE)pType, EIT_16BIT);

	delete indexList;
	delete vertexList;
}

void VideoDriver::DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned short>^ indices)
{
	DrawVertexPrimitiveList(vertices, indices, Scene::PrimitiveType::Triangles);
}

void VideoDriver::DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices, Scene::PrimitiveType pType)
{
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(vertices->Count > 0);
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(indices->Count > 0);

	unsigned int primCount = calculatePrimitiveCount(indices->Count, pType);

	S3DVertex* vertexList = new S3DVertex[vertices->Count];
	for (int i = 0; i < vertices->Count; i++)
	{
		LIME_ASSERT(vertices[i] != nullptr);
		vertexList[i] = *vertices[i]->m_NativeValue;
	}

	u32* indexList = new u32[indices->Count];
	for (int i = 0; i < indices->Count; i++)
	{
		LIME_ASSERT(indices[i] >= 0);
		indexList[i] = indices[i];
	}

	m_VideoDriver->drawVertexPrimitiveList(vertexList, vertices->Count, indexList, primCount,
		EVT_STANDARD, (scene::E_PRIMITIVE_TYPE)pType, EIT_32BIT);

	delete indexList;
	delete vertexList;
}

void VideoDriver::DrawVertexPrimitiveList(List<Vertex3D^>^ vertices, List<unsigned int>^ indices)
{
	DrawVertexPrimitiveList(vertices, indices, Scene::PrimitiveType::Triangles);
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

unsigned int VideoDriver::GetOcclusionQueryResult(Scene::SceneNode^ node)
{
	return m_VideoDriver->getOcclusionQueryResult(LIME_SAFEREF(node, m_SceneNode));
}

Texture^ VideoDriver::GetTexture(String^ filename)
{
	video::ITexture* t = m_VideoDriver->getTexture(Lime::StringToPath(filename));
	return Texture::Wrap(t);
}

Texture^ VideoDriver::GetTextureByIndex(unsigned int index)
{
	video::ITexture* t = m_VideoDriver->getTextureByIndex(index);
	return Texture::Wrap(t);
}

Matrix4f^ VideoDriver::GetTransform(TransformationState state)
{
	return gcnew Matrix4f(m_VideoDriver->getTransform((video::E_TRANSFORMATION_STATE)state));
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Coloru^ color, bool zeroTexels)
{
	LIME_ASSERT(color != nullptr);
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), *color->m_NativeValue, zeroTexels);
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), *color->m_NativeValue);
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Vector2Di^ colorKeyPixelPos, bool zeroTexels)
{
	LIME_ASSERT(colorKeyPixelPos != nullptr);
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), *colorKeyPixelPos->m_NativeValue, zeroTexels);
}

void VideoDriver::MakeColorKeyTexture(Texture^ texture, Vector2Di^ colorKeyPixelPos)
{
	LIME_ASSERT(colorKeyPixelPos != nullptr);
	m_VideoDriver->makeColorKeyTexture(LIME_SAFEREF(texture, m_Texture), *colorKeyPixelPos->m_NativeValue);
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

void VideoDriver::RemoveAllHardwareBuffers()
{
	m_VideoDriver->removeAllHardwareBuffers();
}

void VideoDriver::RemoveAllOcclusionQueries()
{
	m_VideoDriver->removeAllOcclusionQueries();
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

void VideoDriver::RemoveTexture(Texture^ texture)
{
	m_VideoDriver->removeTexture(LIME_SAFEREF(texture, m_Texture));
}

void VideoDriver::RenameTexture(Texture^ texture, String^ newName)
{
	m_VideoDriver->renameTexture(LIME_SAFEREF(texture, m_Texture), Lime::StringToPath(newName));
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

void VideoDriver::SetMaterial(Material^ material)
{
	LIME_ASSERT(material != nullptr);
	m_VideoDriver->setMaterial(*material->m_NativeValue);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer, Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture), clearBackBuffer, clearZBuffer, *color->m_NativeValue);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, bool clearBackBuffer, bool clearZBuffer)
{
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture), clearBackBuffer, clearZBuffer);
}

bool VideoDriver::SetRenderTarget(Texture^ texture, bool clearBackBuffer)
{
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture), clearBackBuffer);
}

bool VideoDriver::SetRenderTarget(Texture^ texture)
{
	return m_VideoDriver->setRenderTarget(LIME_SAFEREF(texture, m_Texture));
}

bool VideoDriver::SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer, Coloru^ color)
{
	LIME_ASSERT(color != nullptr);
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget, clearZBuffer, *color->m_NativeValue);
}

bool VideoDriver::SetRenderTarget(RenderTarget target, bool clearTarget, bool clearZBuffer)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget, clearZBuffer);
}

bool VideoDriver::SetRenderTarget(RenderTarget target, bool clearTarget)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target, clearTarget);
}

bool VideoDriver::SetRenderTarget(RenderTarget target)
{
	return m_VideoDriver->setRenderTarget((E_RENDER_TARGET)target);
}

void VideoDriver::SetTransform(TransformationState state, Matrix4f^ mat)
{
	LIME_ASSERT(mat != nullptr);
	m_VideoDriver->setTransform((video::E_TRANSFORMATION_STATE)state, *mat->m_NativeValue);
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

Video::DriverType VideoDriver::DriverType::get()
{
	return (Video::DriverType)m_VideoDriver->getDriverType();
}

Recti^ VideoDriver::ViewPort::get()
{
	return gcnew Recti(m_VideoDriver->getViewPort());
}

void VideoDriver::ViewPort::set(Recti^ value)
{
	m_VideoDriver->setViewPort(*value->m_NativeValue);
}

Dimension2Du^ VideoDriver::ScreenSize::get()
{
	return gcnew Dimension2Du(m_VideoDriver->getScreenSize());
}

Dimension2Du^ VideoDriver::CurrentRenderTargetSize::get()
{
	return gcnew Dimension2Du(m_VideoDriver->getCurrentRenderTargetSize());
}

Dimension2Du^ VideoDriver::MaxTextureSize::get()
{
	return gcnew Dimension2Du(m_VideoDriver->getMaxTextureSize());
}

int VideoDriver::FPS::get()
{
	return m_VideoDriver->getFPS();
}

Material^ VideoDriver::Material2D::get()
{
	return gcnew Material(&m_VideoDriver->getMaterial2D());
}

unsigned int VideoDriver::PrimitiveCountDrawn::get()
{
	return m_VideoDriver->getPrimitiveCountDrawn();
}

unsigned int VideoDriver::MaximalDynamicLightAmount::get()
{
	return m_VideoDriver->getMaximalDynamicLightAmount();
}

unsigned int VideoDriver::DynamicLightCount::get()
{
	return m_VideoDriver->getDynamicLightCount();
}

Video::ExposedVideoData^ VideoDriver::ExposedVideoData::get()
{
	return gcnew Video::ExposedVideoData(m_VideoDriver->getExposedVideoData());
}

unsigned int VideoDriver::MaximalPrimitiveCount::get()
{
	return m_VideoDriver->getMaximalPrimitiveCount();
}

unsigned int VideoDriver::MaterialRendererCount::get()
{
	return m_VideoDriver->getMaterialRendererCount();
}

String^ VideoDriver::Name::get()
{
	return gcnew String(m_VideoDriver->getName());
}

unsigned int VideoDriver::TextureCount::get()
{
	return m_VideoDriver->getTextureCount();
}

String^ VideoDriver::VendorInfo::get()
{
	return gcnew String(m_VideoDriver->getVendorInfo().c_str());
}

String^ VideoDriver::ToString()
{
	return String::Format("VideoDriver: {0}; ScreenSize={1}", Name, ScreenSize);
}

unsigned int VideoDriver::calculatePrimitiveCount(unsigned int indexCount, Scene::PrimitiveType pType)
{
	unsigned int c;

	LIME_ASSERT(indexCount > 0);

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

	default:
		c = 0;
	}

	LIME_ASSERT2(c > 0, "Failed to calculate count of primitives: unexpected value of PrimitiveType or number of indices invalid.");

	return c;
}

} // end namespace Video
} // end namespace IrrlichtLime