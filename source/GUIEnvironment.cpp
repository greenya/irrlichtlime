#include "stdafx.h"
#include "GUIElement.h"
#include "GUIEnvironment.h"
#include "GUIImage.h"
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

} // end namespace GUI
} // end namespace IrrlichtLime