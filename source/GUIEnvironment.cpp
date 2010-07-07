#include "stdafx.h"
#include "Event.h"
#include "FileSystem.h"
#include "GUIButton.h"
#include "GUICheckBox.h"
#include "GUIColorSelectDialog.h"
#include "GUIComboBox.h"
#include "GUIContextMenu.h"
#include "GUIEditBox.h"
#include "GUIElement.h"
#include "GUIEnvironment.h"
#include "GUIFileOpenDialog.h"
#include "GUIFont.h"
#include "GUIImage.h"
#include "GUIImageList.h"
#include "GUIInOutFader.h"
#include "GUIListBox.h"
#include "GUIMeshViewer.h"
#include "GUIScrollBar.h"
#include "GUISkin.h"
#include "GUISpinBox.h"
#include "GUISpriteBank.h"
#include "GUIStaticText.h"
#include "GUITab.h"
#include "GUITabControl.h"
#include "GUITable.h"
#include "GUIToolBar.h"
#include "GUITreeView.h"
#include "GUIWindow.h"
#include "ReferenceCounted.h"
#include "Texture.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIEnvironment^ GUIEnvironment::Wrap(gui::IGUIEnvironment* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIEnvironment(ref);
}

GUIEnvironment::GUIEnvironment(gui::IGUIEnvironment* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIEnvironment = ref;
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent, int id, String^ text, String^ tooltiptext)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str(),
		Lime::StringToStringW(tooltiptext).c_str());

	return GUIButton::Wrap(b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent, int id, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return GUIButton::Wrap(b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIButton::Wrap(b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIButton::Wrap(b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue);

	return GUIButton::Wrap(b);
}

GUICheckBox^ GUIEnvironment::AddCheckBox(bool checkedState, Recti^ rectangle, String^ text, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUICheckBox* c = m_GUIEnvironment->addCheckBox(
		checkedState,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return GUICheckBox::Wrap(c);
}

GUICheckBox^ GUIEnvironment::AddCheckBox(bool checkedState, Recti^ rectangle, String^ text, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUICheckBox* c = m_GUIEnvironment->addCheckBox(
		checkedState,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		-1,
		Lime::StringToStringW(text).c_str());

	return GUICheckBox::Wrap(c);
}

GUICheckBox^ GUIEnvironment::AddCheckBox(bool checkedState, Recti^ rectangle, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUICheckBox* c = m_GUIEnvironment->addCheckBox(
		checkedState,
		*rectangle->m_NativeValue,
		nullptr,
		-1,
		Lime::StringToStringW(text).c_str());

	return GUICheckBox::Wrap(c);
}

GUICheckBox^ GUIEnvironment::AddCheckBox(bool checkedState, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUICheckBox* c = m_GUIEnvironment->addCheckBox(
		checkedState,
		*rectangle->m_NativeValue);

	return GUICheckBox::Wrap(c);
}

GUIColorSelectDialog^ GUIEnvironment::AddColorSelectDialog(String^ title, bool modal, GUIElement^ parent, int id)
{
	gui::IGUIColorSelectDialog* d = m_GUIEnvironment->addColorSelectDialog(
		Lime::StringToStringW(title).c_str(),
		modal,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIColorSelectDialog::Wrap(d);
}

GUIColorSelectDialog^ GUIEnvironment::AddColorSelectDialog(String^ title, bool modal, GUIElement^ parent)
{
	gui::IGUIColorSelectDialog* d = m_GUIEnvironment->addColorSelectDialog(
		Lime::StringToStringW(title).c_str(),
		modal,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIColorSelectDialog::Wrap(d);
}

GUIColorSelectDialog^ GUIEnvironment::AddColorSelectDialog(String^ title, bool modal)
{
	gui::IGUIColorSelectDialog* d = m_GUIEnvironment->addColorSelectDialog(
		Lime::StringToStringW(title).c_str(),
		modal);

	return GUIColorSelectDialog::Wrap(d);
}

GUIColorSelectDialog^ GUIEnvironment::AddColorSelectDialog(String^ title)
{
	gui::IGUIColorSelectDialog* d = m_GUIEnvironment->addColorSelectDialog(
		Lime::StringToStringW(title).c_str());

	return GUIColorSelectDialog::Wrap(d);
}

GUIColorSelectDialog^ GUIEnvironment::AddColorSelectDialog()
{
	gui::IGUIColorSelectDialog* d = m_GUIEnvironment->addColorSelectDialog();
	return GUIColorSelectDialog::Wrap(d);
}

GUIComboBox^ GUIEnvironment::AddComboBox(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIComboBox* c = m_GUIEnvironment->addComboBox(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIComboBox::Wrap(c);
}

GUIComboBox^ GUIEnvironment::AddComboBox(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIComboBox* c = m_GUIEnvironment->addComboBox(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIComboBox::Wrap(c);
}

GUIComboBox^ GUIEnvironment::AddComboBox(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIComboBox* c = m_GUIEnvironment->addComboBox(
		*rectangle->m_NativeValue);

	return GUIComboBox::Wrap(c);
}

GUIContextMenu^ GUIEnvironment::AddContextMenu(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIContextMenu* m = m_GUIEnvironment->addContextMenu(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIContextMenu::Wrap(m);
}

GUIContextMenu^ GUIEnvironment::AddContextMenu(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIContextMenu* m = m_GUIEnvironment->addContextMenu(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIContextMenu::Wrap(m);
}

GUIContextMenu^ GUIEnvironment::AddContextMenu(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIContextMenu* m = m_GUIEnvironment->addContextMenu(
		*rectangle->m_NativeValue);

	return GUIContextMenu::Wrap(m);
}

GUIEditBox^ GUIEnvironment::AddEditBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIEditBox* b = m_GUIEnvironment->addEditBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIEditBox::Wrap(b);
}

GUIEditBox^ GUIEnvironment::AddEditBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIEditBox* b = m_GUIEnvironment->addEditBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIEditBox::Wrap(b);
}

GUIEditBox^ GUIEnvironment::AddEditBox(String^ text, Recti^ rectangle, bool border)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIEditBox* b = m_GUIEnvironment->addEditBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border);

	return GUIEditBox::Wrap(b);
}

GUIEditBox^ GUIEnvironment::AddEditBox(String^ text, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIEditBox* b = m_GUIEnvironment->addEditBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue);

	return GUIEditBox::Wrap(b);
}

GUISpriteBank^ GUIEnvironment::AddEmptySpriteBank(String^ name)
{
	gui::IGUISpriteBank* b = m_GUIEnvironment->addEmptySpriteBank(Lime::StringToPath(name));
	return GUISpriteBank::Wrap(b);
}

GUIFileOpenDialog^ GUIEnvironment::AddFileOpenDialog(String^ title, bool modal, GUIElement^ parent, int id)
{
	gui::IGUIFileOpenDialog* f = m_GUIEnvironment->addFileOpenDialog(
		Lime::StringToStringW(title).c_str(),
		modal,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIFileOpenDialog::Wrap(f);
}

GUIFileOpenDialog^ GUIEnvironment::AddFileOpenDialog(String^ title, bool modal, GUIElement^ parent)
{
	gui::IGUIFileOpenDialog* f = m_GUIEnvironment->addFileOpenDialog(
		Lime::StringToStringW(title).c_str(),
		modal,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIFileOpenDialog::Wrap(f);
}

GUIFileOpenDialog^ GUIEnvironment::AddFileOpenDialog(String^ title, bool modal)
{
	gui::IGUIFileOpenDialog* f = m_GUIEnvironment->addFileOpenDialog(
		Lime::StringToStringW(title).c_str(),
		modal);

	return GUIFileOpenDialog::Wrap(f);
}

GUIFileOpenDialog^ GUIEnvironment::AddFileOpenDialog(String^ title)
{
	gui::IGUIFileOpenDialog* f = m_GUIEnvironment->addFileOpenDialog(
		Lime::StringToStringW(title).c_str());

	return GUIFileOpenDialog::Wrap(f);
}

GUIFileOpenDialog^ GUIEnvironment::AddFileOpenDialog()
{
	gui::IGUIFileOpenDialog* f = m_GUIEnvironment->addFileOpenDialog();
	return GUIFileOpenDialog::Wrap(f);
}

GUIFont^ GUIEnvironment::AddFont(String^ name, GUIFont^ font)
{
	LIME_ASSERT(font != nullptr);

	gui::IGUIFont* f = m_GUIEnvironment->addFont(
		Lime::StringToPath(name),
		LIME_SAFEREF(font, m_GUIFont));

	return GUIFont::Wrap(f);
}

GUIElement^ GUIEnvironment::AddGUIElement(String^ elementName, GUIElement^ parent)
{
	gui::IGUIElement* e = m_GUIEnvironment->addGUIElement(
		Lime::StringToStringC(elementName).c_str(),
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIElement::Wrap(e);
}

GUIElement^ GUIEnvironment::AddGUIElement(String^ elementName)
{
	gui::IGUIElement* e = m_GUIEnvironment->addGUIElement(
		Lime::StringToStringC(elementName).c_str());

	return GUIElement::Wrap(e);
}

GUIImage^ GUIEnvironment::AddImage(Recti^ rectangle, GUIElement^ parent, int id, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(*rectangle->m_NativeValue);
	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id, String^ text)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent, int id)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel);

	return GUIImage::Wrap(i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue);

	return GUIImage::Wrap(i);
}

GUIInOutFader^ GUIEnvironment::AddInOutFader(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIInOutFader* f = m_GUIEnvironment->addInOutFader(
		rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIInOutFader::Wrap(f);
}

GUIInOutFader^ GUIEnvironment::AddInOutFader(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIInOutFader* f = m_GUIEnvironment->addInOutFader(
		rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIInOutFader::Wrap(f);
}

GUIInOutFader^ GUIEnvironment::AddInOutFader(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIInOutFader* f = m_GUIEnvironment->addInOutFader(rectangle->m_NativeValue);
	return GUIInOutFader::Wrap(f);
}

GUIInOutFader^ GUIEnvironment::AddInOutFader()
{
	gui::IGUIInOutFader* f = m_GUIEnvironment->addInOutFader();
	return GUIInOutFader::Wrap(f);
}

GUIListBox^ GUIEnvironment::AddListBox(Recti^ rectangle, GUIElement^ parent, int id, bool drawBackground)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIListBox* b = m_GUIEnvironment->addListBox(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		drawBackground);

	return GUIListBox::Wrap(b);
}

GUIListBox^ GUIEnvironment::AddListBox(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIListBox* b = m_GUIEnvironment->addListBox(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIListBox::Wrap(b);
}

GUIListBox^ GUIEnvironment::AddListBox(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIListBox* b = m_GUIEnvironment->addListBox(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIListBox::Wrap(b);
}

GUIListBox^ GUIEnvironment::AddListBox(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIListBox* b = m_GUIEnvironment->addListBox(
		*rectangle->m_NativeValue);

	return GUIListBox::Wrap(b);
}

GUIContextMenu^ GUIEnvironment::AddMenu(GUIElement^ parent, int id)
{
	gui::IGUIContextMenu* m = m_GUIEnvironment->addMenu(
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIContextMenu::Wrap(m);
}

GUIContextMenu^ GUIEnvironment::AddMenu(GUIElement^ parent)
{
	gui::IGUIContextMenu* m = m_GUIEnvironment->addMenu(
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIContextMenu::Wrap(m);
}

GUIContextMenu^ GUIEnvironment::AddMenu()
{
	gui::IGUIContextMenu* m = m_GUIEnvironment->addMenu();
	return GUIContextMenu::Wrap(m);
}

GUIMeshViewer^ GUIEnvironment::AddMeshViewer(Recti^ rectangle, GUIElement^ parent, int id, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIMeshViewer* v = m_GUIEnvironment->addMeshViewer(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return GUIMeshViewer::Wrap(v);
}

GUIMeshViewer^ GUIEnvironment::AddMeshViewer(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIMeshViewer* v = m_GUIEnvironment->addMeshViewer(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIMeshViewer::Wrap(v);
}

GUIMeshViewer^ GUIEnvironment::AddMeshViewer(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIMeshViewer* v = m_GUIEnvironment->addMeshViewer(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIMeshViewer::Wrap(v);
}

GUIMeshViewer^ GUIEnvironment::AddMeshViewer(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIMeshViewer* v = m_GUIEnvironment->addMeshViewer(*rectangle->m_NativeValue);
	return GUIMeshViewer::Wrap(v);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent, int id, Video::Texture^ image)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str(),
		modal,
		(gui::EMESSAGE_BOX_FLAG)flags,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		LIME_SAFEREF(image, m_Texture));

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent, int id)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str(),
		modal,
		(gui::EMESSAGE_BOX_FLAG)flags,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags, GUIElement^ parent)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str(),
		modal,
		(gui::EMESSAGE_BOX_FLAG)flags,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text, bool modal, GUIMessageBoxFlag flags)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str(),
		modal,
		(gui::EMESSAGE_BOX_FLAG)flags);

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text, bool modal)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str(),
		modal);

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddMessageBox(String^ caption, String^ text)
{
	gui::IGUIWindow* w = m_GUIEnvironment->addMessageBox(
		Lime::StringToStringW(caption).c_str(),
		Lime::StringToStringW(text).c_str());

	return GUIWindow::Wrap(w);
}

GUIElement^ GUIEnvironment::AddModalScreen(GUIElement^ parent)
{
	gui::IGUIElement* e = m_GUIEnvironment->addModalScreen(LIME_SAFEREF(parent, m_GUIElement));
	return GUIElement::Wrap(e);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIScrollBar::Wrap(s);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIScrollBar::Wrap(s);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue);

	return GUIScrollBar::Wrap(s);
}

GUISpinBox^ GUIEnvironment::AddSpinBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUISpinBox* b = m_GUIEnvironment->addSpinBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUISpinBox::Wrap(b);
}

GUISpinBox^ GUIEnvironment::AddSpinBox(String^ text, Recti^ rectangle, bool border, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUISpinBox* b = m_GUIEnvironment->addSpinBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUISpinBox::Wrap(b);
}

GUISpinBox^ GUIEnvironment::AddSpinBox(String^ text, Recti^ rectangle, bool border)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUISpinBox* b = m_GUIEnvironment->addSpinBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border);

	return GUISpinBox::Wrap(b);
}

GUISpinBox^ GUIEnvironment::AddSpinBox(String^ text, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUISpinBox* b = m_GUIEnvironment->addSpinBox(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue);

	return GUISpinBox::Wrap(b);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent,
	int id, bool fillBackground)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		wordWrap,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		fillBackground);

	return GUIStaticText::Wrap(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent,
	int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		wordWrap,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIStaticText::Wrap(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		wordWrap,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIStaticText::Wrap(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		wordWrap);

	return GUIStaticText::Wrap(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border);

	return GUIStaticText::Wrap(t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue);

	return GUIStaticText::Wrap(t);
}

GUITab^ GUIEnvironment::AddTab(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITab* t = m_GUIEnvironment->addTab(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUITab::Wrap(t);
}

GUITab^ GUIEnvironment::AddTab(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITab* t = m_GUIEnvironment->addTab(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUITab::Wrap(t);
}

GUITab^ GUIEnvironment::AddTab(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITab* t = m_GUIEnvironment->addTab(*rectangle->m_NativeValue);
	return GUITab::Wrap(t);
}

GUITabControl^ GUIEnvironment::AddTabControl(Recti^ rectangle, GUIElement^ parent, bool fillBackground, bool border, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITabControl* t = m_GUIEnvironment->addTabControl(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		fillBackground,
		border,
		id);

	return GUITabControl::Wrap(t);
}

GUITabControl^ GUIEnvironment::AddTabControl(Recti^ rectangle, GUIElement^ parent, bool fillBackground, bool border)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITabControl* t = m_GUIEnvironment->addTabControl(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		fillBackground,
		border);

	return GUITabControl::Wrap(t);
}

GUITabControl^ GUIEnvironment::AddTabControl(Recti^ rectangle, GUIElement^ parent, bool fillBackground)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITabControl* t = m_GUIEnvironment->addTabControl(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		fillBackground);

	return GUITabControl::Wrap(t);
}

GUITabControl^ GUIEnvironment::AddTabControl(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITabControl* t = m_GUIEnvironment->addTabControl(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUITabControl::Wrap(t);
}

GUITabControl^ GUIEnvironment::AddTabControl(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITabControl* t = m_GUIEnvironment->addTabControl(*rectangle->m_NativeValue);
	return GUITabControl::Wrap(t);
}

GUITable^ GUIEnvironment::AddTable(Recti^ rectangle, GUIElement^ parent, int id, bool drawBackground)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITable* t = m_GUIEnvironment->addTable(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		drawBackground);

	return GUITable::Wrap(t);
}

GUITable^ GUIEnvironment::AddTable(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITable* t = m_GUIEnvironment->addTable(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUITable::Wrap(t);
}

GUITable^ GUIEnvironment::AddTable(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITable* t = m_GUIEnvironment->addTable(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUITable::Wrap(t);
}

GUITable^ GUIEnvironment::AddTable(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITable* t = m_GUIEnvironment->addTable(*rectangle->m_NativeValue);
	return GUITable::Wrap(t);
}

GUIToolBar^ GUIEnvironment::AddToolBar(GUIElement^ parent, int id)
{
	gui::IGUIToolBar* b = m_GUIEnvironment->addToolBar(
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIToolBar::Wrap(b);
}

GUIToolBar^ GUIEnvironment::AddToolBar(GUIElement^ parent)
{
	gui::IGUIToolBar* b = m_GUIEnvironment->addToolBar(
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIToolBar::Wrap(b);
}

GUIToolBar^ GUIEnvironment::AddToolBar()
{
	gui::IGUIToolBar* b = m_GUIEnvironment->addToolBar();
	return GUIToolBar::Wrap(b);
}

GUITreeView^ GUIEnvironment::AddTreeView(Recti^ rectangle, GUIElement^ parent, int id, bool drawBackground, bool scrollBarVertical, bool scrollBarHorizontal)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITreeView* v = m_GUIEnvironment->addTreeView(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		drawBackground,
		scrollBarVertical,
		scrollBarHorizontal);

	return GUITreeView::Wrap(v);
}

GUITreeView^ GUIEnvironment::AddTreeView(Recti^ rectangle, GUIElement^ parent, int id, bool drawBackground)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITreeView* v = m_GUIEnvironment->addTreeView(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		drawBackground);

	return GUITreeView::Wrap(v);
}

GUITreeView^ GUIEnvironment::AddTreeView(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITreeView* v = m_GUIEnvironment->addTreeView(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUITreeView::Wrap(v);
}

GUITreeView^ GUIEnvironment::AddTreeView(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITreeView* v = m_GUIEnvironment->addTreeView(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return GUITreeView::Wrap(v);
}

GUITreeView^ GUIEnvironment::AddTreeView(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUITreeView* v = m_GUIEnvironment->addTreeView(*rectangle->m_NativeValue);
	return GUITreeView::Wrap(v);
}

GUIWindow^ GUIEnvironment::AddWindow(Recti^ rectangle, bool modal, String^ text, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIWindow* w = m_GUIEnvironment->addWindow(
		*rectangle->m_NativeValue,
		modal,
		Lime::StringToStringW(text).c_str(),
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddWindow(Recti^ rectangle, bool modal, String^ text, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIWindow* w = m_GUIEnvironment->addWindow(
		*rectangle->m_NativeValue,
		modal,
		Lime::StringToStringW(text).c_str(),
		LIME_SAFEREF(parent, m_GUIElement));

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddWindow(Recti^ rectangle, bool modal, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIWindow* w = m_GUIEnvironment->addWindow(
		*rectangle->m_NativeValue,
		modal,
		Lime::StringToStringW(text).c_str());

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddWindow(Recti^ rectangle, bool modal)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIWindow* w = m_GUIEnvironment->addWindow(
		*rectangle->m_NativeValue,
		modal);

	return GUIWindow::Wrap(w);
}

GUIWindow^ GUIEnvironment::AddWindow(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIWindow* w = m_GUIEnvironment->addWindow(
		*rectangle->m_NativeValue);

	return GUIWindow::Wrap(w);
}

void GUIEnvironment::Clear()
{
	m_GUIEnvironment->clear();
}

bool GUIEnvironment::ClearFocus(GUIElement^ element)
{
	return m_GUIEnvironment->removeFocus(LIME_SAFEREF(element, m_GUIElement));
}

GUIImageList^ GUIEnvironment::CreateImageList(Video::Texture^ texture, Dimension2Di^ imageSize, bool useAlphaChannel)
{
	LIME_ASSERT(imageSize != nullptr);

	gui::IGUIImageList* l = m_GUIEnvironment->createImageList(
		LIME_SAFEREF(texture, m_Texture),
		*imageSize->m_NativeValue,
		useAlphaChannel);

	return GUIImageList::Wrap(l);
}

GUISkin^ GUIEnvironment::CreateSkin(GUISkinType type)
{
	gui::IGUISkin* s = m_GUIEnvironment->createSkin((gui::EGUI_SKIN_TYPE)type);
	return GUISkin::Wrap(s);
}

void GUIEnvironment::DrawAll()
{
	m_GUIEnvironment->drawAll();
}

bool GUIEnvironment::Focused(GUIElement^ element)
{
	return m_GUIEnvironment->hasFocus(LIME_SAFEREF(element, m_GUIElement));
}

GUIFont^ GUIEnvironment::GetFont(String^ filename)
{
	gui::IGUIFont* f = m_GUIEnvironment->getFont(Lime::StringToPath(filename));
	return GUIFont::Wrap(f);
}

GUISpriteBank^ GUIEnvironment::GetSpriteBank(String^ filename)
{
	gui::IGUISpriteBank* b = m_GUIEnvironment->getSpriteBank(Lime::StringToPath(filename));
	return GUISpriteBank::Wrap(b);
}

bool GUIEnvironment::PostEvent(Event^ e)
{
	LIME_ASSERT(e != nullptr);
	return m_GUIEnvironment->postEventFromUser(*e->m_NativeValue);
}

GUIFont^ GUIEnvironment::BuiltInFont::get()
{
	return GUIFont::Wrap(m_GUIEnvironment->getBuiltInFont());
}

IrrlichtLime::IO::FileSystem^ GUIEnvironment::FileSystem::get()
{
	io::IFileSystem* f = m_GUIEnvironment->getFileSystem();
	return IrrlichtLime::IO::FileSystem::Wrap(f);
}

GUIElement^ GUIEnvironment::Focus::get()
{
	gui::IGUIElement* e = m_GUIEnvironment->getFocus();
	return GUIElement::Wrap(e);
}

void GUIEnvironment::Focus::set(GUIElement^ value)
{
	m_GUIEnvironment->setFocus(LIME_SAFEREF(value, m_GUIElement));
}

GUIElement^ GUIEnvironment::RootElement::get()
{
	gui::IGUIElement* e = m_GUIEnvironment->getRootGUIElement();
	return GUIElement::Wrap(e);
}

GUISkin^ GUIEnvironment::Skin::get()
{
	gui::IGUISkin* s = m_GUIEnvironment->getSkin();
	return GUISkin::Wrap(s);
}

void GUIEnvironment::Skin::set(GUISkin^ value)
{
	m_GUIEnvironment->setSkin(LIME_SAFEREF(value, m_GUISkin));
}

Video::VideoDriver^ GUIEnvironment::VideoDriver::get()
{
	video::IVideoDriver* v = m_GUIEnvironment->getVideoDriver();
	return Video::VideoDriver::Wrap(v);
}

} // end namespace GUI
} // end namespace IrrlichtLime