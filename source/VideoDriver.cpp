#pragma once

#include "stdafx.h"
#include "Material.h"
#include "Texture.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

VideoDriver::VideoDriver(video::IVideoDriver* videoDriver)
{
	LIME_ASSERT(videoDriver != nullptr);
	m_VideoDriver = videoDriver;
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData, Recti^ sourceRect)
{
	LIME_ASSERT(color != nullptr);
	LIME_ASSERT(videoData != nullptr);
	LIME_ASSERT(sourceRect != nullptr);

	return m_VideoDriver->beginScene(backBuffer, zBuffer, *color->m_NativeValue, *videoData->m_NativeValue, sourceRect->m_NativeValue);
}

bool VideoDriver::BeginScene(bool backBuffer, bool zBuffer, Coloru^ color, ExposedVideoData^ videoData)
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

void VideoDriver::DisableFeature(VideoDriverFeature feature, bool flag)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature, flag);
}

void VideoDriver::DisableFeature(VideoDriverFeature feature)
{
	m_VideoDriver->disableFeature((video::E_VIDEO_DRIVER_FEATURE)feature);
}

bool VideoDriver::EndScene()
{
	return m_VideoDriver->endScene();
}

ExposedVideoData^ VideoDriver::GetExposedVideoData()
{
	return gcnew ExposedVideoData(m_VideoDriver->getExposedVideoData());
}

Texture^ VideoDriver::GetTexture(String^ filename)
{
	return LIME_SAFEWRAP(Texture, m_VideoDriver->getTexture(Lime::StringToPath(filename)));
}

Texture^ VideoDriver::GetTextureByIndex(unsigned int index)
{
	return LIME_SAFEWRAP(Texture, m_VideoDriver->getTextureByIndex(index));
}

Matrix4f^ VideoDriver::GetTransform(TransformationState state)
{
	return gcnew Matrix4f(m_VideoDriver->getTransform((video::E_TRANSFORMATION_STATE)state));
}

bool VideoDriver::QueryFeature(VideoDriverFeature feature)
{
	return m_VideoDriver->queryFeature((video::E_VIDEO_DRIVER_FEATURE)feature);
}

void VideoDriver::RenameTexture(Texture^ texture, String^ newName)
{
	m_VideoDriver->renameTexture(LIME_SAFEREF(texture, m_Texture), Lime::StringToPath(newName));
}

void VideoDriver::SetMaterial(Material^ material)
{
	LIME_ASSERT(material != nullptr);
	m_VideoDriver->setMaterial(*material->m_NativeValue);
}

void VideoDriver::SetTransform(TransformationState state, Matrix4f^ mat)
{
	LIME_ASSERT(mat != nullptr);
	m_VideoDriver->setTransform((video::E_TRANSFORMATION_STATE)state, *mat->m_NativeValue);
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
	return Name;
}

} // end namespace Video
} // end namespace IrrlichtLime