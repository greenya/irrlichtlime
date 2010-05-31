#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;
using namespace System::Runtime::InteropServices; // for OutAttribute
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

ref class GUIElement;
ref class GUIFont;
ref class GUISpriteBank;

public ref class GUISkin : IO::AttributeExchangingObject
{
public:

	void Draw2DRectangle(GUIElement^ element, Video::Coloru^ color, Recti^ pos, Recti^ clip);
	void Draw2DRectangle(GUIElement^ element, Video::Coloru^ color, Recti^ pos);

	void Draw3DButtonPanePressed(GUIElement^ element, Recti^ rect, Recti^ clip);
	void Draw3DButtonPanePressed(GUIElement^ element, Recti^ rect);

	void Draw3DButtonPaneStandard(GUIElement^ element, Recti^ rect, Recti^ clip);
	void Draw3DButtonPaneStandard(GUIElement^ element, Recti^ rect);

	void Draw3DMenuPane(GUIElement^ element, Recti^ rect, Recti^ clip);
	void Draw3DMenuPane(GUIElement^ element, Recti^ rect);

	void Draw3DSunkenPane(GUIElement^ element, Video::Coloru^ bgcolor, bool flat, bool fillBackGround, Recti^ rect, Recti^ clip);
	void Draw3DSunkenPane(GUIElement^ element, Video::Coloru^ bgcolor, bool flat, bool fillBackGround, Recti^ rect);

	void Draw3DTabBody(GUIElement^ element, bool border, bool background, Recti^ rect, Recti^ clip, int tabHeight, GUIAlignment alignment);
	void Draw3DTabBody(GUIElement^ element, bool border, bool background, Recti^ rect, Recti^ clip, int tabHeight);
	void Draw3DTabBody(GUIElement^ element, bool border, bool background, Recti^ rect, Recti^ clip);
	void Draw3DTabBody(GUIElement^ element, bool border, bool background, Recti^ rect);

	void Draw3DTabButton(GUIElement^ element, bool active, Recti^ rect, Recti^ clip, GUIAlignment alignment);
	void Draw3DTabButton(GUIElement^ element, bool active, Recti^ rect, Recti^ clip);
	void Draw3DTabButton(GUIElement^ element, bool active, Recti^ rect);

	void Draw3DToolBar(GUIElement^ element, Recti^ rect, Recti^ clip);
	void Draw3DToolBar(GUIElement^ element, Recti^ rect);

	Recti^ Draw3DWindowBackground(GUIElement^ element, bool drawTitleBar, Video::Coloru^ titleBarColor, Recti^ rect, Recti^ clip, [Out] Recti^ checkClientArea);
	Recti^ Draw3DWindowBackground(GUIElement^ element, bool drawTitleBar, Video::Coloru^ titleBarColor, Recti^ rect, Recti^ clip);
	Recti^ Draw3DWindowBackground(GUIElement^ element, bool drawTitleBar, Video::Coloru^ titleBarColor, Recti^ rect);

	void DrawIcon(GUIElement^ element, GUIDefaultIcon icon, Vector2Di^ position, unsigned int starttime, unsigned int currenttime, bool loop, Recti^ clip);
	void DrawIcon(GUIElement^ element, GUIDefaultIcon icon, Vector2Di^ position, unsigned int starttime, unsigned int currenttime, bool loop);
	void DrawIcon(GUIElement^ element, GUIDefaultIcon icon, Vector2Di^ position, unsigned int starttime, unsigned int currenttime);
	void DrawIcon(GUIElement^ element, GUIDefaultIcon icon, Vector2Di^ position, unsigned int starttime);
	void DrawIcon(GUIElement^ element, GUIDefaultIcon icon, Vector2Di^ position);

	Video::Coloru^ GetColor(GUIDefaultColor color);
	String^ GetText(GUIDefaultText text);
	GUIFont^ GetFont(GUIDefaultFont which);
	unsigned int GetIcon(GUIDefaultIcon icon);
	int GetSize(GUIDefaultSize size);

	void SetColor(GUIDefaultColor which, Video::Coloru^ newColor);
	void SetText(GUIDefaultText which, String^ newText);
	void SetFont(GUIDefaultFont which, GUIFont^ font);
	void SetIcon(GUIDefaultIcon which, unsigned int index);
	void SetSize(GUIDefaultSize which, int size);

	property GUISpriteBank^ SpriteBank { GUISpriteBank^ get(); void set(GUISpriteBank^ value); }
	property GUISkinType Type { GUISkinType get(); }

	virtual String^ ToString() override;

internal:

	GUISkin(gui::IGUISkin* guiSkin);

	gui::IGUISkin* m_GUISkin;
};

} // end namespace GUI
} // end namespace IrrlichtLime