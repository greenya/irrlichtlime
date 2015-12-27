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

	//TODO
	// *** CursorSprite is not implemented yet ***
	//CursorIcon AddIcon(CursorSprite icon);
	//void ChangeIcon(CursorIcon iconId, CursorSprite sprite);
	void SetReferenceRect(Nullable<Recti> rect_or_null);

	property CursorIcon ActiveIcon { CursorIcon get(); void set(CursorIcon value); }
	property CursorPlatformBehavior PlatformBehavior { CursorPlatformBehavior get(); void set(CursorPlatformBehavior value); }
	property Vector2Di Position { Vector2Di get(); void set(Vector2Di value); }
	property Vector2Df RelativePosition { Vector2Df get(); }
	property Dimension2Di^ SupportedIconSize { Dimension2Di^ get(); }
	property bool Visible { bool get(); void set(bool value); }

	virtual String^ ToString() override;

internal:

	static CursorControl^ Wrap(gui::ICursorControl* ref);
	CursorControl(gui::ICursorControl* ref);

	gui::ICursorControl* m_CursorControl;
};

} // end namespace GUI
} // end namespace IrrlichtLime