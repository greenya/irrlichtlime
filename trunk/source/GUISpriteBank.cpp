#include "stdafx.h"
#include "GUISpriteBank.h"
#include "ReferenceCounted.h"
#include "Rect.h"
#include "irrArray.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace GUI {

GUISpriteBank^ GUISpriteBank::Wrap(gui::IGUISpriteBank* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUISpriteBank(ref);
}

GUISpriteBank::GUISpriteBank(gui::IGUISpriteBank* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUISpriteBank = ref;
}

/*array<Recti^>^ GUISpriteBank::Positions::get()
{
	core::array< core::rect<s32> > pos = m_GUISpriteBank->getPositions();
	array<Recti^>^ ret = gcnew array<Recti^>(m_GUISpriteBank->getTextureCount());

	for (int i = 0; i < ret->Length; i++)
	{
		core::rect<s32> b = pos[i];
		Recti^ rect = gcnew Recti(b);
		ret[i] = rect;
	}

	return ret;
}*/

} // end namespace GUI
} // end namespace IrrlichtLime