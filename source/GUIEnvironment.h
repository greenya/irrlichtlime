#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace GUI {

ref class GUIButton;
ref class GUIComboBox;
ref class GUIContextMenu;
ref class GUIEditBox;
ref class GUIElement;
ref class GUIFileOpenDialog;
ref class GUIFont;
ref class GUIImage;
ref class GUIListBox;
ref class GUIScrollBar;
ref class GUISkin;
ref class GUIStaticText;
ref class GUIToolBar;
ref class GUIWindow;

public ref class GUIEnvironment : ReferenceCounted
{
public:

	GUIButton^ AddButton(Recti^ rectangle, GUIElement^ parent, int id, String^ text, String^ tooltiptext);
	GUIButton^ AddButton(Recti^ rectangle, GUIElement^ parent, int id, String^ text);
	GUIButton^ AddButton(Recti^ rectangle, GUIElement^ parent, int id);
	GUIButton^ AddButton(Recti^ rectangle, GUIElement^ parent);
	GUIButton^ AddButton(Recti^ rectangle);

	GUIComboBox^ AddComboBox(Recti^ rectangle, GUIElement^ parent, int id);
	GUIComboBox^ AddComboBox(Recti^ rectangle, GUIElement^ parent);
	GUIComboBox^ AddComboBox(Recti^ rectangle);

	GUIContextMenu^ AddContextMenu(Recti^ rectangle, GUIElement^ parent, int id);
	GUIContextMenu^ AddContextMenu(Recti^ rectangle, GUIElement^ parent);
	GUIContextMenu^ AddContextMenu(Recti^ rectangle);

	GUIEditBox^ AddEditBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent, int id);
	GUIEditBox^ AddEditBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent);
	GUIEditBox^ AddEditBox(String^ text, Recti^ rectangle, bool border);
	GUIEditBox^ AddEditBox(String^ text, Recti^ rectangle);

	GUIFileOpenDialog^ AddFileOpenDialog(String^ title, bool modal, GUIElement^ parent, int id);
	GUIFileOpenDialog^ AddFileOpenDialog(String^ title, bool modal, GUIElement^ parent);
	GUIFileOpenDialog^ AddFileOpenDialog(String^ title, bool modal);
	GUIFileOpenDialog^ AddFileOpenDialog(String^ title);
	GUIFileOpenDialog^ AddFileOpenDialog();

	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id, String^ text);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel);
	GUIImage^ AddImage(Video::Texture^ image, Vector2Di^ pos);

	GUIListBox^ AddListBox(Recti^ rectangle, GUIElement^ parent, int id, bool drawBackground);
	GUIListBox^ AddListBox(Recti^ rectangle, GUIElement^ parent, int id);
	GUIListBox^ AddListBox(Recti^ rectangle, GUIElement^ parent);
	GUIListBox^ AddListBox(Recti^ rectangle);

	GUIContextMenu^ AddMenu(GUIElement^ parent, int id);
	GUIContextMenu^ AddMenu(GUIElement^ parent);
	GUIContextMenu^ AddMenu();

	GUIWindow^ AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent, int id, Video::Texture^ image);
	GUIWindow^ AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent, int id);
	GUIWindow^ AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent);
	GUIWindow^ AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags);
	GUIWindow^ AddMessageBox(String^ caption, String^ text, bool modal);
	GUIWindow^ AddMessageBox(String^ caption, String^ text);

	GUIScrollBar^ AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent, int id);
	GUIScrollBar^ AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent);
	GUIScrollBar^ AddScrollBar(bool horizontal, Recti^ rectangle);

	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id, bool fillBackground);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent, int id);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle, bool border);
	GUIStaticText^ AddStaticText(String^ text, Recti^ rectangle);

	GUIToolBar^ AddToolBar(GUIElement^ parent, int id);
	GUIToolBar^ AddToolBar(GUIElement^ parent);
	GUIToolBar^ AddToolBar();

	GUIWindow^ AddWindow(Recti^ rectangle, bool modal, String^ text, GUIElement^ parent, int id);
	GUIWindow^ AddWindow(Recti^ rectangle, bool modal, String^ text, GUIElement^ parent);
	GUIWindow^ AddWindow(Recti^ rectangle, bool modal, String^ text);
	GUIWindow^ AddWindow(Recti^ rectangle, bool modal);
	GUIWindow^ AddWindow(Recti^ rectangle);

	void DrawAll();

	GUIFont^ GetFont(String^ filename);

	property GUIFont^ BuiltInFont { GUIFont^ get(); }
	property GUIElement^ RootElement { GUIElement^ get(); }
	property GUISkin^ Skin { GUISkin^ get(); void set(GUISkin^ value); }

internal:

	static GUIEnvironment^ Wrap(gui::IGUIEnvironment* ref);
	GUIEnvironment(gui::IGUIEnvironment* ref);

	gui::IGUIEnvironment* m_GUIEnvironment;
};

} // end namespace GUI
} // end namespace IrrlichtLime