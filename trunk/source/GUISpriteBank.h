#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class GUISpriteBank : ReferenceCounted
{
public:

	//property array<Recti^>^ Positions { array<Recti^>^ get(); }

	//no GUISprite yet
	//property array<GUISprite^>^ Sprites {array<GUISprite^>^ get(); }

internal:

	static GUISpriteBank^ Wrap(gui::IGUISpriteBank* ref);
	GUISpriteBank(gui::IGUISpriteBank* ref);

	gui::IGUISpriteBank* m_GUISpriteBank;
};

} // end namespace GUI
} // end namespace IrrlichtLime