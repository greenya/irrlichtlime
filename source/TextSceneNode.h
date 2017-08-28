#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {

namespace GUI { ref class GUIFont; }

namespace Scene {

public ref class TextSceneNode : SceneNode
{
public:

	String^ GetText();
	void SetText(String^ text);

	Video::Color GetTextColor();
	void SetTextColor(Video::Color color);

	property GUI::GUIFont^ Font { GUI::GUIFont^ get(); void set(GUI::GUIFont^ value); }

internal:

	static TextSceneNode^ Wrap(scene::ITextSceneNode* ref);
	TextSceneNode(scene::ITextSceneNode* ref);

	scene::ITextSceneNode* m_TextSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime