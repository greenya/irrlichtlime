#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace System::Runtime::InteropServices; // for OutAttribute
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

namespace GUI { ref class CursorControl; ref class GUIEnvironment; }
namespace IO { ref class FileSystem; }
namespace Scene { ref class SceneManager; }
namespace Video { ref class VideoDriver; ref class VideoModeList; }

ref class Event;
ref class Timer;
class EventReceiverInheritor;

public ref class IrrlichtDevice : ReferenceCounted
{
public:

	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen, bool stencilbuffer, bool vsync);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen, bool stencilbuffer);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits, bool fullscreen);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize, unsigned int bits);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Dimension2Du^ windowSize);
	static IrrlichtDevice^ CreateDevice(Video::DriverType driverType);
	static IrrlichtDevice^ CreateDevice();

	static bool IsDriverSupported(Video::DriverType driver);

	~IrrlichtDevice();
	!IrrlichtDevice();

	void ClearSystemMessages();
	void Close();
	bool GetGammaRamp([Out] float% red, [Out] float% green, [Out] float% blue, [Out] float% relativebrightness, [Out] float% relativecontrast);
	void MaximizeWindow();
	void MinimizeWindow();
	void RestoreWindow();
	bool Run();
	bool SetGammaRamp(float red, float green, float blue, float relativebrightness, float relativecontrast);
	void SetInputReceivingSceneManager(Scene::SceneManager^ sceneManager);
	void SetWindowCaption(String^ text);
	void SetWindowResizable(bool resize);
	void Sleep(unsigned int timeMs, bool pauseTimer);
	void Sleep(unsigned int timeMs);
	void Yield();

	property Video::ColorFormat ColorFormat { Video::ColorFormat get(); }
	property GUI::CursorControl^ CursorControl { GUI::CursorControl^ get(); }
	property IO::FileSystem^ FileSystem { IO::FileSystem^ get(); }
	property bool Fullscreen { bool get(); }
	property GUI::GUIEnvironment^ GUIEnvironment { GUI::GUIEnvironment^ get(); }
	property Scene::SceneManager^ SceneManager { Scene::SceneManager^ get(); }
	property IrrlichtLime::Timer^ Timer { IrrlichtLime::Timer^ get(); }
	property DeviceType Type { DeviceType get(); }
	property String^ Version { String^ get(); }
	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }
	property Video::VideoModeList^ VideoModeList { Video::VideoModeList^ get(); }
	property bool WindowActive { bool get(); }
	property bool WindowFocused { bool get(); }
	property bool WindowMinimized { bool get(); }

	virtual String^ ToString() override;

	delegate bool EventHandler(IrrlichtLime::Event^ e);
	event EventHandler^ OnEvent;

internal:

	static IrrlichtDevice^ Wrap(irr::IrrlichtDevice* ref);
	IrrlichtDevice(irr::IrrlichtDevice* ref);
	bool Event(IrrlichtLime::Event^ e);

	irr::IrrlichtDevice* m_IrrlichtDevice;
	EventReceiverInheritor* m_EventReceiverInheritor;
};

} // end namespace IrrlichtLime