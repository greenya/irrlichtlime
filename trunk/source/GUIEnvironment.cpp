#include "stdafx.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIEnvironment.h"
#include "GUIFont.h"
#include "GUIImage.h"
#include "GUIScrollBar.h"
#include "GUISkin.h"
#include "GUIStaticText.h"
#include "ReferenceCounted.h"
#include "Texture.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIEnvironment::GUIEnvironment(gui::IGUIEnvironment* guiEnvironment)
	: ReferenceCounted(guiEnvironment)
{
	LIME_ASSERT(guiEnvironment != nullptr);
	m_GUIEnvironment = guiEnvironment;
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

	return LIME_SAFEWRAP(GUIButton, b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent, int id, String^ text)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id,
		Lime::StringToStringW(text).c_str());

	return LIME_SAFEWRAP(GUIButton, b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return LIME_SAFEWRAP(GUIButton, b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIButton* b = m_GUIEnvironment->addButton(
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return LIME_SAFEWRAP(GUIButton, b);
}

GUIButton^ GUIEnvironment::AddButton(Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);
	gui::IGUIButton* b = m_GUIEnvironment->addButton(*rectangle->m_NativeValue);
	return LIME_SAFEWRAP(GUIButton, b);
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

	return LIME_SAFEWRAP(GUIImage, i);
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

	return LIME_SAFEWRAP(GUIImage, i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel, GUIElement^ parent)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel,
		LIME_SAFEREF(parent, m_GUIElement));

	return LIME_SAFEWRAP(GUIImage, i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos, bool useAlphaChannel)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue,
		useAlphaChannel);

	return LIME_SAFEWRAP(GUIImage, i);
}

GUIImage^ GUIEnvironment::AddImage(Video::Texture^ image, Vector2Di^ pos)
{
	LIME_ASSERT(pos != nullptr);

	gui::IGUIImage* i = m_GUIEnvironment->addImage(
		LIME_SAFEREF(image, m_Texture),
		*pos->m_NativeValue);

	return LIME_SAFEWRAP(GUIImage, i);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent, int id)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement),
		id);

	return LIME_SAFEWRAP(GUIScrollBar, s);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle, GUIElement^ parent)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue,
		LIME_SAFEREF(parent, m_GUIElement));

	return LIME_SAFEWRAP(GUIScrollBar, s);
}

GUIScrollBar^ GUIEnvironment::AddScrollBar(bool horizontal, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIScrollBar* s = m_GUIEnvironment->addScrollBar(
		horizontal,
		*rectangle->m_NativeValue);

	return LIME_SAFEWRAP(GUIScrollBar, s);
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

	return LIME_SAFEWRAP(GUIStaticText, t);
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

	return LIME_SAFEWRAP(GUIStaticText, t);
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

	return LIME_SAFEWRAP(GUIStaticText, t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border, bool wordWrap)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border,
		wordWrap);

	return LIME_SAFEWRAP(GUIStaticText, t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle, bool border)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue,
		border);

	return LIME_SAFEWRAP(GUIStaticText, t);
}

GUIStaticText^ GUIEnvironment::AddStaticText(String^ text, Recti^ rectangle)
{
	LIME_ASSERT(rectangle != nullptr);

	gui::IGUIStaticText* t = m_GUIEnvironment->addStaticText(
		Lime::StringToStringW(text).c_str(),
		*rectangle->m_NativeValue);

	return LIME_SAFEWRAP(GUIStaticText, t);
}

void GUIEnvironment::DrawAll()
{
	m_GUIEnvironment->drawAll();
}

GUIFont^ GUIEnvironment::GetFont(String^ filename)
{
	gui::IGUIFont* f = m_GUIEnvironment->getFont(Lime::StringToPath(filename));
	return LIME_SAFEWRAP(GUIFont, f);
}

GUIFont^ GUIEnvironment::BuiltInFont::get()
{
	return LIME_SAFEWRAP(GUIFont, m_GUIEnvironment->getBuiltInFont());
}

GUISkin^ GUIEnvironment::Skin::get()
{
	gui::IGUISkin* s = m_GUIEnvironment->getSkin();
	return LIME_SAFEWRAP(GUISkin, s);
}

void GUIEnvironment::Skin::set(GUISkin^ value)
{
	m_GUIEnvironment->setSkin(LIME_SAFEREF(value, m_GUISkin));
}

String^ GUIEnvironment::ToString()
{
	return String::Format("gui environment...");
}

} // end namespace GUI
} // end namespace IrrlichtLime