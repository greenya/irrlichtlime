#include "stdafx.h"
#include "GUIElement.h"
#include "GUIInOutFader.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIInOutFader^ GUIInOutFader::Wrap(gui::IGUIInOutFader* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIInOutFader(ref);
}

GUIInOutFader::GUIInOutFader(gui::IGUIInOutFader* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIInOutFader = ref;
}

void GUIInOutFader::FadeIn(unsigned int time)
{
	m_GUIInOutFader->fadeIn(time);
}

void GUIInOutFader::FadeOut(unsigned int time)
{
	m_GUIInOutFader->fadeOut(time);
}

void GUIInOutFader::SetColor(Video::Color source, Video::Color dest)
{
	m_GUIInOutFader->setColor(
		source,
		dest);
}

void GUIInOutFader::SetColor(Video::Color bothAplhaIgnored)
{
	m_GUIInOutFader->setColor(bothAplhaIgnored);
}

bool GUIInOutFader::Ready::get()
{
	return m_GUIInOutFader->isReady();
}

} // end namespace GUI
} // end namespace IrrlichtLime