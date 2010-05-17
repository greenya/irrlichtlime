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
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer, vsync);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen,
	bool stencilbuffer)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits);

	return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue);

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

bool IrrlichtDevice::GetGammaRamp([Out] float% red, [Out] float% green, [Out] float% blue, [Out] float% relativebrightness, [Out] float% relativecontrast)
{
	float r, g, b, rb, rv;
	bool o = m_IrrlichtDevice->getGammaRamp(r, g, b, rb, rv);

	red = r;
	green = g;
	blue = b;
	relativebrightness = rb;
	relativecontrast = rv;

	return o;
}

bool IrrlichtDevice::Run()
{
	return m_IrrlichtDevice->run();
}

bool IrrlichtDevice::SetGammaRamp(float red, float green, float blue, float relativebrightness, float relativecontrast)
{
	return m_IrrlichtDevice->setGammaRamp(red, green, blue, relativebrightness, relativecontrast);
}

void IrrlichtDevice::Sleep(UInt32 timeMs, bool pauseTimer)
{
	m_IrrlichtDevice->sleep(timeMs, pauseTimer);
}

void IrrlichtDevice::Sleep(UInt32 timeMs)
{
	m_IrrlichtDevice->sleep(timeMs);
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

bool IrrlichtDevice::Fullscreen::get()
{
	return m_IrrlichtDevice->isFullscreen();
}

GUI::GUIEnvironment^ IrrlichtDevice::GUIEnvironment::get()
{
	return gcnew GUI::GUIEnvironment(m_IrrlichtDevice->getGUIEnvironment());
}

String^ IrrlichtDevice::Version::get()
{
	return gcnew String(m_IrrlichtDevice->getVersion());
}

bool IrrlichtDevice::WindowActive::get()
{
	return m_IrrlichtDevice->isWindowActive();
}

void IrrlichtDevice::WindowCaption::set(String^ value)
{
	m_IrrlichtDevice->setWindowCaption(Lime::StringToStringW(value).c_str());
}

bool IrrlichtDevice::WindowFocused::get()
{
	return m_IrrlichtDevice->isWindowFocused();
}

bool IrrlichtDevice::WindowMinimized::get()
{
	return m_IrrlichtDevice->isWindowMinimized();
}

void IrrlichtDevice::WindowResizable::set(bool value)
{
	m_IrrlichtDevice->setResizable(value);
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