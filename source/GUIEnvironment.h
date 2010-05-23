#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

ref class GUIElement;
ref class GUIStaticText;

public ref class GUIEnvironment : ReferenceCounted
{
public:

	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id, bool fillBackground);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id);
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