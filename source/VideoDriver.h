#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Video
{
	public ref class VideoDriver
	{
	public:

		property Video::DriverType DriverType
		{
			Video::DriverType get()
			{
				return (Video::DriverType)m_VideoDriver->getDriverType();
			}
		}

		property Core::Recti^ ViewPort
		{
			Core::Recti^ get()
			{
				return gcnew Core::Recti(m_VideoDriver->getViewPort());
			}

			void set(Core::Recti^ value)
			{
				m_VideoDriver->setViewPort(*((core::recti*)value->m_NativeObject));
			}
		}

		property Core::Dimension2Du^ ScreenSize
		{
			Core::Dimension2Du^ get()
			{
				return gcnew Core::Dimension2Du(m_VideoDriver->getScreenSize());
			}
		}

		property Core::Dimension2Du^ CurrentRenderTargetSize
		{
			Core::Dimension2Du^ get()
			{
				return gcnew Core::Dimension2Du(m_VideoDriver->getCurrentRenderTargetSize());
			}
		}

		property Core::Dimension2Du^ MaxTextureSize
		{
			Core::Dimension2Du^ get()
			{
				return gcnew Core::Dimension2Du(m_VideoDriver->getMaxTextureSize());
			}
		}

		property Int32 FPS
		{
			Int32 get()
			{
				return m_VideoDriver->getFPS();
			}
		}

		property UInt32 PrimitiveCountDrawn
		{
			UInt32 get()
			{
				return m_VideoDriver->getPrimitiveCountDrawn();
			}
		}

		property UInt32 MaximalDynamicLightAmount
		{
			UInt32 get()
			{
				return m_VideoDriver->getMaximalDynamicLightAmount();
			}
		}

		property UInt32 DynamicLightCount
		{
			UInt32 get()
			{
				return m_VideoDriver->getDynamicLightCount();
			}
		}

		property UInt32 MaximalPrimitiveCount
		{
			UInt32 get()
			{
				return m_VideoDriver->getMaximalPrimitiveCount();
			}
		}

		property UInt32 MaterialRendererCount
		{
			UInt32 get()
			{
				return m_VideoDriver->getMaterialRendererCount();
			}
		}

		property String^ Name
		{
			String^ get()
			{
				return gcnew String(m_VideoDriver->getName());
			}
		}

		property String^ VendorInfo
		{
			String^ get()
			{
				return gcnew String(m_VideoDriver->getVendorInfo().c_str());
			}
		}

		virtual String^ ToString() override
		{
			return Name;
		}

	internal:

		video::IVideoDriver* m_VideoDriver;

		VideoDriver(video::IVideoDriver* videoDriver)
		{
			m_VideoDriver = videoDriver;
		}
	};
}
}