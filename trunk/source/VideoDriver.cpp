#pragma once

#include "stdafx.h"
#include "Texture.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

Texture^ VideoDriver::GetTexture(String^ filename)
{
	video::ITexture* t = m_VideoDriver->getTexture(Lime::StringToStringC(filename).c_str());
	return t == nullptr ? nullptr : gcnew Texture(t);
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
	m_VideoDriver->setViewPort(*((core::recti*)value->m_NativeObject));
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

Int32 VideoDriver::FPS::get()
{
	return m_VideoDriver->getFPS();
}

UInt32 VideoDriver::PrimitiveCountDrawn::get()
{
	return m_VideoDriver->getPrimitiveCountDrawn();
}

UInt32 VideoDriver::MaximalDynamicLightAmount::get()
{
	return m_VideoDriver->getMaximalDynamicLightAmount();
}

UInt32 VideoDriver::DynamicLightCount::get()
{
	return m_VideoDriver->getDynamicLightCount();
}

UInt32 VideoDriver::MaximalPrimitiveCount::get()
{
	return m_VideoDriver->getMaximalPrimitiveCount();
}

UInt32 VideoDriver::MaterialRendererCount::get()
{
	return m_VideoDriver->getMaterialRendererCount();
}

String^ VideoDriver::Name::get()
{
	return gcnew String(m_VideoDriver->getName());
}

String^ VideoDriver::VendorInfo::get()
{
	return gcnew String(m_VideoDriver->getVendorInfo().c_str());
}

String^ VideoDriver::ToString()
{
	return Name;
}

VideoDriver::VideoDriver(video::IVideoDriver* videoDriver)
{
	LIME_ASSERT(videoDriver != nullptr);
	m_VideoDriver = videoDriver;
}

} // end namespace Video
} // end namespace IrrlichtLime