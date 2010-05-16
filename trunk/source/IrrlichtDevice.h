#pragma once

#include "stdafx.h"
#include "GUIEnvironment.h"
#include "SceneManager.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

public ref class IrrlichtDevice
{
public:

	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen, bool stencilbuffer, bool vsync);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen, bool stencilbuffer);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits, bool fullscreen);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, UInt32 bits);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType);
	static IrrlichtDevice^ CreateDevice();

	void Drop();

	property GUI::GUIEnvironment^ GUIEnvironment { GUI::GUIEnvironment^ get(); }
	property Scene::SceneManager^ SceneManager { Scene::SceneManager^ get(); }
	property String^ Version { String^ get(); }
	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }
	property String^ WindowCaption { void set(String^ value); }

	virtual String^ ToString() override;

internal:

	IrrlichtDevice(irr::IrrlichtDevice* irrlichtDevice);

	irr::IrrlichtDevice* m_IrrlichtDevice;
};

} // end namespace IrrlichtLime