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

	//...

	virtual String^ ToString() override;

internal:

	GUISpriteBank(gui::IGUISpriteBank* guiSpriteBank);

	gui::IGUISpriteBank* m_GUISpriteBank;
};

} // end namespace GUI
} // end namespace IrrlichtLime