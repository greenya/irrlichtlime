#include "stdafx.h"
#include "GUIFontBitmap.h"
#include "GUISpriteBank.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

GUIFontBitmap^ GUIFontBitmap::Wrap(gui::IGUIFontBitmap* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIFontBitmap(ref);
}

GUIFontBitmap::GUIFontBitmap(gui::IGUIFontBitmap* ref)
	: GUIFont(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIFontBitmap = ref;
}

int GUIFontBitmap::GetKerningWidth(Nullable<Char> thisLetter, Nullable<Char> previousLetter)
{
	wchar_t c_thisLetter;
	wchar_t c_previousLetter;
	if (thisLetter.HasValue)
		c_thisLetter = thisLetter.Value;
	if (previousLetter.HasValue)
		c_previousLetter = previousLetter.Value;

	return m_GUIFontBitmap->getKerningWidth(
		thisLetter.HasValue ? &c_thisLetter : 0,
		previousLetter.HasValue ? &c_previousLetter : 0);
}

int GUIFontBitmap::GetKerningWidth(Nullable<Char> thisLetter)
{
	wchar_t c_thisLetter;
	if (thisLetter.HasValue)
		c_thisLetter = thisLetter.Value;

	return m_GUIFontBitmap->getKerningWidth(
		thisLetter.HasValue ? &c_thisLetter : 0);
}

int GUIFontBitmap::GetKerningWidth()
{
	return m_GUIFontBitmap->getKerningWidth();
}

unsigned int GUIFontBitmap::GetSpriteNoFromChar(Char c)
{
	return m_GUIFontBitmap->getSpriteNoFromChar(&c);
}

GUISpriteBank^ GUIFontBitmap::SpriteBank::get()
{
	return GUISpriteBank::Wrap(m_GUIFontBitmap->getSpriteBank());
}

} // end namespace GUI
} // end namespace IrrlichtLime