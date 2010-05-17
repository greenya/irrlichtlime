#pragma once

#include "stdafx.h"
#include "FileSystem.h"
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
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject,
		bits, fullscreen, stencilbuffer, vsync);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen,
	bool stencilbuffer)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject,
		bits, fullscreen, stencilbuffer);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject,
		bits, fullscreen);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject,
		bits);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*(core::dimension2du*)windowSize->m_NativeObject);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice()
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice();

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

void IrrlichtDevice::Drop()
{
	m_IrrlichtDevice->drop();
}

bool IrrlichtDevice::Run()
{
	return m_IrrlichtDevice->run();
}

void IrrlichtDevice::Yield()
{
	m_IrrlichtDevice->yield();
}

Video::VideoDriver^ IrrlichtDevice::VideoDriver::get()
{
	return gcnew Video::VideoDriver(m_IrrlichtDevice->getVideoDriver());
}

Scene::SceneManager^ IrrlichtDevice::SceneManager::get()
{
	return gcnew Scene::SceneManager(m_IrrlichtDevice->getSceneManager());
}

IO::FileSystem^ IrrlichtDevice::FileSystem::get()
{
	return gcnew IO::FileSystem(m_IrrlichtDevice->getFileSystem());
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

void IrrlichtDevice::CreateDevice_start()
{
	Console::WriteLine("Irrlicht Lime version " + Lime::Version);
}

} // end namespace IrrlichtLime