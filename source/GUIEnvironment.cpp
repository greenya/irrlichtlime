#include "stdafx.h"
#include "GUIButton.h"
#include "GUIEditBox.h"
#include "GUIElement.h"
#include "GUIEnvironment.h"
#include "GUIFileOpenDialog.h"
#include "GUIFont.h"
#include "GUIImage.h"
#include "GUIScrollBar.h"
#include "GUISkin.h"
#include "GUIStaticText.h"
#include "GUIWindow.h"
#include "ReferenceCounted.h"
#include "Texture.h"

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

void GUIEnvironment::DrawAll()
{
	m_GUIEnvironment->drawAll();
}

GUIFont^ GUIEnvironment::GetFont(String^ filename)
{
	gui::IGUIFont* f = m_GUIEnvironment->getFont(Lime::StringToPath(filename));
	return GUIFont::Wrap(f);
}

GUIFont^ GUIEnvironment::BuiltInFont::get()
{
	return GUIFont::Wrap(m_GUIEnvironment->getBuiltInFont());
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

} // end namespace GUI
} // end namespace IrrlichtLime