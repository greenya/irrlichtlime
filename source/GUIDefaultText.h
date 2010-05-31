#pragma once

#include "stdafx.h"

using namespace irr;
using namespace gui;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

public enum class GUIDefaultText
{
	MsgBoxOK = EGDT_MSG_BOX_OK,
	MsgBoxCancel = EGDT_MSG_BOX_CANCEL,
	MsgBoxYes = EGDT_MSG_BOX_YES,
	MsgBoxNo = EGDT_MSG_BOX_NO,
	WindowClose = EGDT_WINDOW_CLOSE,
	WindowMaximize = EGDT_WINDOW_MAXIMIZE,
	WindowMinimize = EGDT_WINDOW_MINIMIZE,
	WindowRestore = EGDT_WINDOW_RESTORE
};

} // end namespace GUI
} // end namespace IrrlichtLime