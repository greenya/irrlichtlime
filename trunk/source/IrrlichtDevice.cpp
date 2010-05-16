#pragma once

#include "stdafx.h"
#include "GUIEnvironment.h"
#include "IrrlichtDevice.h"
#include "SceneManager.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

IrrlichtDevice::IrrlichtDevice(irr::IrrlichtDevice* irrlichtDevice)
{
	LIME_ASSERT(irrlichtDevice != nullptr);
	m_IrrlichtDevice = irrlichtDevice;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen,
	bool stencilbuffer, bool vsync)
{
	Console::WriteLine("Irrlicht Lime version " + Lime::Version);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject,
		bits, fullscreen, stencilbuffer, vsync);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen,
	bool stencilbuffer)
{
	return IrrlichtDevice::CreateDevice(driverType, windowSize, bits, fullscreen, stencilbuffer, false);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen)
{
	return IrrlichtDevice::CreateDevice(driverType, windowSize, bits, fullscreen, false);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits)
{
	return IrrlichtDevice::CreateDevice(driverType, windowSize, bits, false);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize)
{
	return IrrlichtDevice::CreateDevice(driverType, windowSize, 16);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType)
{
	return IrrlichtDevice::CreateDevice(driverType, gcnew Dimension2Du(640, 480));
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice()
{
	return IrrlichtDevice::CreateDevice(Video::DriverType::Software);
}

void IrrlichtDevice::Drop()
{
	m_IrrlichtDevice->drop();
}

Video::VideoDriver^ IrrlichtDevice::VideoDriver::get()
{
	return gcnew Video::VideoDriver(m_IrrlichtDevice->getVideoDriver());
}

Scene::SceneManager^ IrrlichtDevice::SceneManager::get()
{
	return gcnew Scene::SceneManager(m_IrrlichtDevice->getSceneManager());
}

GUI::GUIEnvironment^ IrrlichtDevice::GUIEnvironment::get()
{
	return gcnew GUI::GUIEnvironment(m_IrrlichtDevice->getGUIEnvironment());
}

String^ IrrlichtDevice::Version::get()
{
	return gcnew String(m_IrrlichtDevice->getVersion());
}

void IrrlichtDevice::WindowCaption::set(String^ value)
{
	m_IrrlichtDevice->setWindowCaption(Lime::StringToStringW(value).c_str());
}

String^ IrrlichtDevice::ToString()
{
	return String::Format("Irrlicht {0}{1}", Version,
		m_IrrlichtDevice->getDebugName() == nullptr ? "" : " DEBUG");
}

} // end namespace IrrlichtLime