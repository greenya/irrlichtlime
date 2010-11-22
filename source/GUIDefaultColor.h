#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIDefaultColor
{
	_3dDarkShadow = EGDC_3D_DARK_SHADOW,
	_3dShadow = EGDC_3D_SHADOW,
	_3dFace = EGDC_3D_FACE,
	_3dHighLight = EGDC_3D_HIGH_LIGHT,
	_3dLight = EGDC_3D_LIGHT,
	ActiveBorder = EGDC_ACTIVE_BORDER,
	ActiveCaption = EGDC_ACTIVE_CAPTION,
	AppWorkspace = EGDC_APP_WORKSPACE,
	ButtonText = EGDC_BUTTON_TEXT,
	GrayText = EGDC_GRAY_TEXT,
	HighLight = EGDC_HIGH_LIGHT,
	HighLightText = EGDC_HIGH_LIGHT_TEXT,
	InactiveBorder = EGDC_INACTIVE_BORDER,
	InactiveCaption = EGDC_INACTIVE_CAPTION,
	TooltipText = EGDC_TOOLTIP,
	TooltipBackground = EGDC_TOOLTIP_BACKGROUND,
	ScrollBar = EGDC_SCROLLBAR,
	WindowBackground = EGDC_WINDOW,
	WindowSymbol = EGDC_WINDOW_SYMBOL,
	Icon = EGDC_ICON,
	IconHighLight = EGDC_ICON_HIGH_LIGHT,
	GrayWindowSymbol = EGDC_GRAY_WINDOW_SYMBOL,
	Editable = EGDC_EDITABLE,
	GrayEditable = EGDC_GRAY_EDITABLE,
	FocusedEditable = EGDC_FOCUSED_EDITABLE
};

} // end namespace GUI
} // end namespace IrrlichtLime