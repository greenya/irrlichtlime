#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"
#include "GUISpriteBank.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class CursorSprite : Lime::NativeValue<gui::SCursorSprite>
{
public:
	
	CursorSprite()
		: Lime::NativeValue<gui::SCursorSprite>(true)
	{
		m_NativeValue = new gui::SCursorSprite();
	}

	CursorSprite(GUISpriteBank^ spriteBank, int spriteID, Vector2Di hotspot)
		: Lime::NativeValue<gui::SCursorSprite>(true)
	{
		//LIME_ASSERT(spriteBank != nullptr); can actually be null

		m_NativeValue = new gui::SCursorSprite(spriteBank->m_GUISpriteBank, spriteID, hotspot);
	}

	CursorSprite(GUISpriteBank^ spriteBank, int spriteID)
		: Lime::NativeValue<gui::SCursorSprite>(true)
	{
		//LIME_ASSERT(spriteBank != nullptr); can actually be null

		m_NativeValue = new gui::SCursorSprite(spriteBank->m_GUISpriteBank, spriteID);
	}

	property GUISpriteBank^ SpriteBank
	{
		GUISpriteBank^ get()
		{
			return GUISpriteBank::Wrap(m_NativeValue->SpriteBank);
		}

		void set(GUISpriteBank^ value)
		{
			m_NativeValue->SpriteBank = LIME_SAFEREF(value, m_GUISpriteBank);
		}
	}

	property int SpriteID
	{
		int get()
		{
			return m_NativeValue->SpriteId;
		}

		void set(int value)
		{
			m_NativeValue->SpriteId = value;
		}
	}

	property Vector2Di HotSpot
	{
		Vector2Di get()
		{
			return Vector2Di(m_NativeValue->HotSpot);
		}

		void set(Vector2Di value)
		{
			m_NativeValue->HotSpot = value;
		}
	}

internal:

	CursorSprite(const gui::SCursorSprite& other)
		: Lime::NativeValue<gui::SCursorSprite>(true)
	{
		m_NativeValue = new gui::SCursorSprite(other);
	}
};

} // end namespace GUI
} // end namespace IrrlichtLime