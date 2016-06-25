#pragma once

#include "stdafx.h"
#include "IGUISpriteBank.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class GUISpriteFrame
{
public:

	GUISpriteFrame(unsigned int TextureNumber, unsigned int RectNumber)
		: TextureNumber(TextureNumber), RectNumber(RectNumber)
	{
	}

	unsigned int TextureNumber;
	unsigned int RectNumber;

internal:

	GUISpriteFrame(const gui::SGUISpriteFrame& value)
		: TextureNumber(value.textureNumber), RectNumber(value.rectNumber)
	{
	}

	operator gui::SGUISpriteFrame()
	{
#ifdef FAST_TO_NATIVE
		return (gui::SGUISpriteFrame&)*this;
		//return *(interior_ptr<gui::SGUISpriteFrame>)this;
#else
		return gui::SGUISpriteFrame(TextureNumber, RectNumber);
#endif
	}

	gui::SGUISpriteFrame ToNative()
	{
		return (gui::SGUISpriteFrame)*this;
	}

};


} // end namespace GUI
} // end namespace IrrlichtLime