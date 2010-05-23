#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class CursorControl : ReferenceCounted
{
public:

	property Vector2Di^ Position { Vector2Di^ get(); void set(Vector2Di^ value); }
	property Recti^ ReferenceRect { void set(Recti^ value); }
	property Vector2Df^ RelativePosition { Vector2Df^ get(); }
	property bool Visible { bool get(); void set(bool value); }

	virtual String^ ToString() override;

internal:

	CursorControl(gui::ICursorControl* cursorControl);

	gui::ICursorControl* m_CursorControl;
};

} // end namespace GUI
} // end namespace IrrlichtLime