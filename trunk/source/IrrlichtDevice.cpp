#pragma once

#include "stdafx.h"
#include "CursorControl.h"
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

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen,
	bool stencilbuffer, bool vsync)
{
	LIME_ASSERT(windowSize != nullptr);

	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer, vsync);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen,
	bool stencilbuffer)
{
	LIME_ASSERT(windowSize != nullptr);

	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen)
{
	LIME_ASSERT(windowSize != nullptr);

	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits)
{
	LIME_ASSERT(windowSize != nullptr);

	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize)
{
	LIME_ASSERT(windowSize != nullptr);

	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType)
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType);

	return LIME_SAFEWRAP(IrrlichtDevice, d);
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice()
{
	CreateDevice_start();

	irr::IrrlichtDevice* d = createDevice();

	return LIME_SAFEWRAP(IrrlichtDevice, d);
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

void IrrlichtDevice::Sleep(unsigned int timeMs, bool pauseTimer)
{
	m_IrrlichtDevice->sleep(timeMs, pauseTimer);
}

void IrrlichtDevice::Sleep(unsigned int timeMs)
{
	m_IrrlichtDevice->sleep(timeMs);
}

void IrrlichtDevice::Yield()
{
	m_IrrlichtDevice->yield();
}

Video::VideoDriver^ IrrlichtDevice::VideoDriver::get()
{
	return LIME_SAFEWRAP(Video::VideoDriver, m_IrrlichtDevice->getVideoDriver());
}

Scene::SceneManager^ IrrlichtDevice::SceneManager::get()
{
	return LIME_SAFEWRAP(Scene::SceneManager, m_IrrlichtDevice->getSceneManager());
}

GUI::CursorControl^ IrrlichtDevice::CursorControl::get()
{
	return LIME_SAFEWRAP(GUI::CursorControl, m_IrrlichtDevice->getCursorControl());
}

IO::FileSystem^ IrrlichtDevice::FileSystem::get()
{
	return LIME_SAFEWRAP(IO::FileSystem, m_IrrlichtDevice->getFileSystem());
}

bool IrrlichtDevice::Fullscreen::get()
{
	return m_IrrlichtDevice->isFullscreen();
}

GUI::GUIEnvironment^ IrrlichtDevice::GUIEnvironment::get()
{
	return LIME_SAFEWRAP(GUI::GUIEnvironment, m_IrrlichtDevice->getGUIEnvironment());
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