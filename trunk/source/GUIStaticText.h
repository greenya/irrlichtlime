#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace GUI
{
	public ref class GUIStaticText : GUIElement
	{
	public:

	internal:

		gui::IGUIStaticText* m_GUIStaticText;

		GUIStaticText(gui::IGUIStaticText* guiStaticText)
			: GUIElement(guiStaticText)
		{
			m_GUIStaticText = guiStaticText;
		}
	};
}
}