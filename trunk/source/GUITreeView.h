#pragma once

#include "stdafx.h"
#include "GUIElement.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

ref class GUIFont;
ref class GUIImageList;
ref class GUITreeViewNode;
ref class GUIScrollBar;

public ref class GUITreeView : GUIElement
{
public:

	void SetIconFont(GUIFont^ font);

	property GUIFont^ ActiveFont { GUIFont^ get(); }
	property GUIScrollBar^ HorizontalScrollBar { GUIScrollBar^ get(); }
	property bool ImageLeftOfIcon { bool get(); void set(bool value); }
	property GUIImageList^ ImageList { GUIImageList^ get(); void set(GUIImageList^ value); }
	property GUITreeViewNode^ LastEventNode { GUITreeViewNode^ get(); }
	property bool LinesVisible { bool get(); void set(bool value); }
	property GUIFont^ OverrideFont { GUIFont^ get(); void set(GUIFont^ value); }
	property GUITreeViewNode^ RootNode { GUITreeViewNode^ get(); }
	property GUITreeViewNode^ SelectedNode { GUITreeViewNode^ get(); }
	property GUIScrollBar^ VerticalScrollBar { GUIScrollBar^ get(); }

internal:

	static GUITreeView^ Wrap(gui::IGUITreeView* ref);
	GUITreeView(gui::IGUITreeView* ref);

	gui::IGUITreeView* m_GUITreeView;
};

} // end namespace GUI
} // end namespace IrrlichtLime