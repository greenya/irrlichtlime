#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace GUI
{
	public ref class GUIElement
	{
	public:

		GUIElement^ GetElementFromID(Int32 id, bool searchchildren)
		{
			gui::IGUIElement *e = m_GUIElement->getElementFromId(id, searchchildren);
			return e == nullptr ? nullptr : gcnew GUIElement(e);
		}

		GUIElement^ GetElementFromID(Int32 id)
		{
			return GetElementFromID(id, false);
		}

		GUIElement^ GetElementFromPoint(Core::Vector2Di^ point)
		{
			gui::IGUIElement *e = m_GUIElement->getElementFromPoint(*((core::vector2di*)point->m_NativeObject));
			return e == nullptr ? nullptr : gcnew GUIElement(e);
		}

		bool IsMyChild(GUIElement^ child)
		{
			return m_GUIElement->isMyChild(child->m_GUIElement);
		}

		bool IsPointInside(Core::Vector2Di^ point)
		{
			return m_GUIElement->isPointInside(*((core::vector2di*)point->m_NativeObject));
		}

		property GUIElementType Type
		{
			GUIElementType get()
			{
				return (GUIElementType)m_GUIElement->getType();
			}
		}

		property Int32 ID
		{
			Int32 get()
			{
				return m_GUIElement->getID();
			}

			void set(Int32 value)
			{
				m_GUIElement->setID(value);
			}
		}

		property bool Visible
		{
			bool get()
			{
				return m_GUIElement->isVisible();
			}

			void set(bool value)
			{
				m_GUIElement->setVisible(value);
			}
		}

		property bool Enabled
		{
			bool get()
			{
				return m_GUIElement->isEnabled();
			}

			void set(bool value)
			{
				m_GUIElement->setEnabled(value);
			}
		}

		property bool TabStop
		{
			bool get()
			{
				return m_GUIElement->isTabStop();
			}

			void set(bool value)
			{
				m_GUIElement->setTabStop(value);
			}
		}

		property Int32 TabOrder
		{
			Int32 get()
			{
				return m_GUIElement->getTabOrder();
			}

			void set(Int32 value)
			{
				m_GUIElement->setTabOrder(value);
			}
		}

		property Core::Recti^ RelativePosition
		{
			Core::Recti^ get()
			{
				return gcnew Core::Recti(m_GUIElement->getRelativePosition());
			}

			void set(Core::Recti^ value)
			{
				m_GUIElement->setRelativePosition(*((core::recti*)value->m_NativeObject));
			}
		}

		property Core::Recti^ AbsolutePosition
		{
			Core::Recti^ get()
			{
				return gcnew Core::Recti(m_GUIElement->getAbsolutePosition());
			}
		}

		property bool NotClipped
		{
			bool get()
			{
				return m_GUIElement->isNotClipped();
			}

			void set(bool value)
			{
				m_GUIElement->setNotClipped(value);
			}
		}

		property Core::Recti^ AbsoluteClippingRect
		{
			Core::Recti^ get()
			{
				return gcnew Core::Recti(m_GUIElement->getAbsoluteClippingRect());
			}
		}

		property String^ Text
		{
			String^ get()
			{
				return gcnew String(m_GUIElement->getText());
			}

			void set(String^ value)
			{
				m_GUIElement->setText(Lime::StringToStringW(value).c_str());
			}
		}

		property String^ ToolTipText
		{
			String^ get()
			{
				return gcnew String(m_GUIElement->getToolTipText().c_str());
			}

			void set(String^ value)
			{
				m_GUIElement->setToolTipText(Lime::StringToStringW(value).c_str());
			}
		}

		virtual String^ ToString() override
		{
			return String::Format("Type={0}; Text={1}", Type, Text);
		}

	internal:

		gui::IGUIElement* m_GUIElement;

		GUIElement(gui::IGUIElement* guiElement)
		{
			m_GUIElement = guiElement;
		}
	};
}
}