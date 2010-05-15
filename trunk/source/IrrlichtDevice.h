#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
	public ref class IrrlichtDevice
	{
	public:

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Core::Dimension2Du^ windowSize, UInt32 bits,
			bool fullscreen, bool stencilbuffer, bool vsync)
		{
			Console::WriteLine("Irrlicht Lime version " + Lime::Version);

			irr::IrrlichtDevice* d = createDevice(
				(video::E_DRIVER_TYPE)driverType,
				*(core::dimension2du*)windowSize->m_NativeObject,
				bits, fullscreen, stencilbuffer, vsync);

			return d == nullptr ? nullptr : gcnew IrrlichtDevice(d);
		}

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Core::Dimension2Du^ windowSize, UInt32 bits,
			bool fullscreen, bool stencilbuffer)
		{
			return CreateDevice(driverType, windowSize, bits, fullscreen, stencilbuffer, false);
		}

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Core::Dimension2Du^ windowSize, UInt32 bits,
			bool fullscreen)
		{
			return CreateDevice(driverType, windowSize, bits, fullscreen, false);
		}

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Core::Dimension2Du^ windowSize, UInt32 bits)
		{
			return CreateDevice(driverType, windowSize, bits, false);
		}

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType, Core::Dimension2Du^ windowSize)
		{
			return CreateDevice(driverType, windowSize, 16);
		}

		static IrrlichtDevice^ CreateDevice(Video::DriverType driverType)
		{
			return CreateDevice(driverType, gcnew Core::Dimension2Du(640, 480));
		}

		static IrrlichtDevice^ CreateDevice()
		{
			return CreateDevice(Video::DriverType::Software);
		}

		void Drop()
		{
			m_IrrlichtDevice->drop();
		}

		property Video::VideoDriver^ VideoDriver
		{
			Video::VideoDriver^ get()
			{
				return gcnew Video::VideoDriver(m_IrrlichtDevice->getVideoDriver());
			}
		}

		property Scene::SceneManager^ SceneManager
		{
			Scene::SceneManager^ get()
			{
				return gcnew Scene::SceneManager(m_IrrlichtDevice->getSceneManager());
			}
		}

		property GUI::GUIEnvironment^ GUIEnvironment
		{
			GUI::GUIEnvironment^ get()
			{
				return gcnew GUI::GUIEnvironment(m_IrrlichtDevice->getGUIEnvironment());
			}
		}

		property String^ Version
		{
			String^ get()
			{
				return gcnew String(m_IrrlichtDevice->getVersion());
			}
		}

		property String^ WindowCaption
		{
			void set(String^ value)
			{
				m_IrrlichtDevice->setWindowCaption(Lime::StringToStringW(value).c_str());
			}
		}

		virtual String^ ToString() override
		{
			return String::Format("Irrlicht {0}{1}", Version,
				m_IrrlichtDevice->getDebugName() == nullptr ? "" : " DEBUG");
		}

	internal:

		irr::IrrlichtDevice* m_IrrlichtDevice;

		IrrlichtDevice(irr::IrrlichtDevice* irrlichtDevice)
		{
			m_IrrlichtDevice = irrlichtDevice;
		}
	};
}