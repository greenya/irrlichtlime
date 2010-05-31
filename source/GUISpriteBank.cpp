#include "stdafx.h"
#include "GUISpriteBank.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUISpriteBank::GUISpriteBank(gui::IGUISpriteBank* guiSpriteBank)
	: ReferenceCounted(guiSpriteBank)
{
	LIME_ASSERT(guiSpriteBank != nullptr);
	m_GUISpriteBank = guiSpriteBank;
}

String^ GUISpriteBank::ToString()
{
	return String::Format("gui sprite bank...");
}

} // end namespace GUI
} // end namespace IrrlichtLime