#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

ref class GUIElement;
ref class GUIStaticText;

public ref class GUIEnvironment
{
public:

	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, Int32 id, bool fillBackground);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, Int32 id);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle);

	void DrawAll();

internal:

	GUIEnvironment(gui::IGUIEnvironment* guiEnvironment);

	gui::IGUIEnvironment* m_GUIEnvironment;
};

} // end namespace GUI
} // end namespace IrrlichtLime