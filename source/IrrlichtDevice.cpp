#include "stdafx.h"
#include "CursorControl.h"
#include "EventReceiverInheritor.h"
#include "FileSystem.h"
#include "GUIEnvironment.h"
#include "IrrlichtDevice.h"
#include "ReferenceCounted.h"
#include "SceneManager.h"
#include "Timer.h"
#include "VideoDriver.h"
#include "VideoModeList.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

IrrlichtDevice::IrrlichtDevice(irr::IrrlichtDevice* irrlichtDevice)
	: ReferenceCounted(irrlichtDevice)
{
	LIME_ASSERT(irrlichtDevice != nullptr);
	m_IrrlichtDevice = irrlichtDevice;
}

IrrlichtDevice::~IrrlichtDevice()
{
	this->!IrrlichtDevice();
}

IrrlichtDevice::!IrrlichtDevice()
{
	if (m_EventReceiverInheritor != nullptr)
	{
		delete m_EventReceiverInheritor;
		m_EventReceiverInheritor = nullptr;
	}
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen,
	bool stencilbuffer, bool vsync)
{
	LIME_ASSERT(windowSize != nullptr);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer, vsync);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen,
	bool stencilbuffer)
{
	LIME_ASSERT(windowSize != nullptr);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen, stencilbuffer);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen)
{
	LIME_ASSERT(windowSize != nullptr);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits, fullscreen);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits)
{
	LIME_ASSERT(windowSize != nullptr);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue,
		bits);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize)
{
	LIME_ASSERT(windowSize != nullptr);

	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType,
		*windowSize->m_NativeValue);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice(Video::DriverType driverType)
{
	irr::IrrlichtDevice* d = createDevice(
		(video::E_DRIVER_TYPE)driverType);

	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

IrrlichtDevice^ IrrlichtDevice::CreateDevice()
{
	irr::IrrlichtDevice* d = createDevice();
	IrrlichtDevice^ w = LIME_SAFEWRAP(IrrlichtDevice, d);
	deviceHasBeenCreated(w);
	return w;
}

bool IrrlichtDevice::IsDriverSupported(Video::DriverType driver)
{
	return irr::IrrlichtDevice::isDriverSupported((video::E_DRIVER_TYPE)driver);
}

void IrrlichtDevice::ClearSystemMessages()
{
	m_IrrlichtDevice->clearSystemMessages();
}

void IrrlichtDevice::Close()
{
	m_IrrlichtDevice->closeDevice();
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

void IrrlichtDevice::MaximizeWindow()
{
	m_IrrlichtDevice->maximizeWindow();
}

void IrrlichtDevice::MinimizeWindow()
{
	m_IrrlichtDevice->minimizeWindow();
}

void IrrlichtDevice::RestoreWindow()
{
	m_IrrlichtDevice->restoreWindow();
}

bool IrrlichtDevice::Run()
{
	return m_IrrlichtDevice->run();
}

bool IrrlichtDevice::SetGammaRamp(float red, float green, float blue, float relativebrightness, float relativecontrast)
{
	return m_IrrlichtDevice->setGammaRamp(red, green, blue, relativebrightness, relativecontrast);
}

void IrrlichtDevice::SetInputReceivingSceneManager(Scene::SceneManager^ sceneManager)
{
	m_IrrlichtDevice->setInputReceivingSceneManager(LIME_SAFEREF(sceneManager, m_SceneManager));
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

Video::ColorFormat IrrlichtDevice::ColorFormat::get()
{
	return (Video::ColorFormat)m_IrrlichtDevice->getColorFormat();
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

Scene::SceneManager^ IrrlichtDevice::SceneManager::get()
{
	return LIME_SAFEWRAP(Scene::SceneManager, m_IrrlichtDevice->getSceneManager());
}

IrrlichtLime::Timer^ IrrlichtDevice::Timer::get()
{
	return LIME_SAFEWRAP(IrrlichtLime::Timer, m_IrrlichtDevice->getTimer());
}

DeviceType IrrlichtDevice::Type::get()
{
	return (DeviceType)m_IrrlichtDevice->getType();
}

String^ IrrlichtDevice::Version::get()
{
	return gcnew String(m_IrrlichtDevice->getVersion());
}

Video::VideoDriver^ IrrlichtDevice::VideoDriver::get()
{
	return LIME_SAFEWRAP(Video::VideoDriver, m_IrrlichtDevice->getVideoDriver());
}

Video::VideoModeList^ IrrlichtDevice::VideoModeList::get()
{
	return LIME_SAFEWRAP(Video::VideoModeList, m_IrrlichtDevice->getVideoModeList());
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

void IrrlichtDevice::deviceHasBeenCreated(IrrlichtDevice^ device)
{
	if (device == nullptr)
	{
		Console::WriteLine("Device creation failed.");
		return;
	}

	core::stringw s = "Irrlicht Lime version ";
	s += Lime::StringToStringW(Lime::Version);
	device->m_IrrlichtDevice->getLogger()->log(s.c_str());

	device->m_EventReceiverInheritor = new EventReceiverInheritor();
	device->m_EventReceiverInheritor->m_EventHandler = gcnew EventHandler(device, &IrrlichtDevice::Event);
	device->m_IrrlichtDevice->setEventReceiver(device->m_EventReceiverInheritor);
}

bool IrrlichtDevice::Event(IrrlichtLime::Event^ e)
{
	return OnEvent(e);
}

} // end namespace IrrlichtLime