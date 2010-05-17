#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

namespace GUI { ref class GUIEnvironment; }
namespace Scene { ref class SceneManager; }
namespace Video { ref class VideoDriver; }

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
	bool Run();
	void Yield();

	property GUI::GUIEnvironment^ GUIEnvironment { GUI::GUIEnvironment^ get(); }
	property Scene::SceneManager^ SceneManager { Scene::SceneManager^ get(); }
	property String^ Version { String^ get(); }
	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }
	property String^ WindowCaption { void set(String^ value); }

	virtual String^ ToString() override;

internal:

	IrrlichtDevice(irr::IrrlichtDevice* irrlichtDevice);

	irr::IrrlichtDevice* m_IrrlichtDevice;

private:

	static void CreateDevice_start();
};

} // end namespace IrrlichtLime