#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

ref class GUIFont;

public ref class GUIProfiler : GUIElement
{
public:
	
	void FirstPage(bool includeOverview);
	void FirstPage();

	void NextPage(bool includeOverview);
	void NextPage();

	void PreviousPage(bool includeOverview);
	void PreviousPage();

	property GUIFont^ ActiveFont { GUIFont^ get(); }
	property bool IgnoreUncalled { bool get(); void set(bool value); }
	property GUIFont^ OverrideFont { GUIFont^ get(); void set(GUIFont^ value); }

internal:

	static GUIProfiler^ Wrap(gui::IGUIProfiler* ref);
	GUIProfiler(gui::IGUIProfiler* ref);

	gui::IGUIProfiler* m_GUIProfiler;
};

} // end namespace GUI
} // end namespace IrrlichtLime