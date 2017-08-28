#pragma once

#include "stdafx.h"
#include "BillboardSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

namespace GUI { ref class GUIFont; }

namespace Scene {

public ref class BillboardTextSceneNode : BillboardSceneNode
{
public:

	String^ GetText();
	void SetText(String^ text);
	void SetTextColor(Video::Color color);

	property GUI::GUIFont^ Font { GUI::GUIFont^ get(); }

internal:

	static BillboardTextSceneNode^ Wrap(scene::IBillboardTextSceneNode* ref);
	BillboardTextSceneNode(scene::IBillboardTextSceneNode* ref);

	scene::IBillboardTextSceneNode* m_BillboardTextSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime