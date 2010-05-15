#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace GUI
{
	public ref class GUIEnvironment
	{
	public:

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, Int32 id, bool fillBackground)
		{
			gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
				Lime::StringToStringW(text).c_str(),
				*((core::recti*)rectangle->m_NativeObject),
				border,
				wordWrap,
				parent == nullptr ? nullptr : parent->m_GUIElement,
				id,
				fillBackground);

			return gcnew GUIStaticText(t);
		}

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, Int32 id)
		{
			return AddStaticText(text, rectangle, border, wordWrap, parent, id, false);
		}

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent)
		{
			return AddStaticText(text, rectangle, border, wordWrap, parent, -1);
		}

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle, bool border, bool wordWrap)
		{
			return AddStaticText(text, rectangle, border, wordWrap, nullptr);
		}

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle, bool border)
		{
			return AddStaticText(text, rectangle, border, true);
		}

		GUIStaticText^ AddStaticText(String^ text, Core::Recti^ rectangle)
		{
			return AddStaticText(text, rectangle, false);
		}

	internal:

		gui::IGUIEnvironment* m_GUIEnvironment;

		GUIEnvironment(gui::IGUIEnvironment* guiEnvironment)
		{
			m_GUIEnvironment = guiEnvironment;
		}
	};
}
}