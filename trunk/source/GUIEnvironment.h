#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace GUI {

ref class GUIElement;
ref class GUIFont;
ref class GUIImage;
ref class GUISkin;
ref class GUIStaticText;

public ref class GUIEnvironment : ReferenceCounted
{
public:

	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id, String^ text);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos);

	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id, bool fillBackground);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle);

	void DrawAll();

	GUIFont^ GetFont(String^ filename);

	property GUIFont^ BuiltInFont { GUIFont^ get(); }
	property GUISkin^ Skin { GUISkin^ get(); void set(GUISkin^ value); }

	virtual String^ ToString() override;

internal:

	GUIEnvironment(gui::IGUIEnvironment* guiEnvironment);

	gui::IGUIEnvironment* m_GUIEnvironment;
};

} // end namespace GUI
} // end namespace IrrlichtLime