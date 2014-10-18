#include "stdafx.h"
#include "GUIProfiler.h"
#include "GUIElement.h"
#include "GUIFont.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIProfiler^ GUIProfiler::Wrap(gui::IGUIProfiler* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIProfiler(ref);
}

GUIProfiler::GUIProfiler(gui::IGUIProfiler* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIProfiler = ref;
}

void GUIProfiler::FirstPage(bool includeOverview)
{
	m_GUIProfiler->firstPage(includeOverview);
}

void GUIProfiler::FirstPage()
{
	m_GUIProfiler->firstPage();
}

void GUIProfiler::NextPage(bool includeOverview)
{
	m_GUIProfiler->nextPage(includeOverview);
}

void GUIProfiler::NextPage()
{
	m_GUIProfiler->nextPage();
}

void GUIProfiler::PreviousPage(bool includeOverview)
{
	m_GUIProfiler->previousPage(includeOverview);
}

void GUIProfiler::PreviousPage()
{
	m_GUIProfiler->previousPage();
}

void GUIProfiler::SetFilters(unsigned int minCalls, unsigned int minTimeSum, float minTimeAverage, unsigned int minTimeMax)
{
	m_GUIProfiler->setFilters(minCalls, minTimeSum, minTimeAverage, minTimeMax);
}

GUIFont^ GUIProfiler::ActiveFont::get()
{
	return GUIFont::Wrap(m_GUIProfiler->getActiveFont());
}

bool GUIProfiler::DrawBackground::get()
{
	return m_GUIProfiler->isDrawBackgroundEnabled();
}

void GUIProfiler::DrawBackground::set(bool value)
{
	m_GUIProfiler->setDrawBackground(value);
}

bool GUIProfiler::Frozen::get()
{
	return m_GUIProfiler->getFrozen();
}

void GUIProfiler::Frozen::set(bool value)
{
	m_GUIProfiler->setFrozen(value);
}

GUIFont^ GUIProfiler::OverrideFont::get()
{
	return GUIFont::Wrap(m_GUIProfiler->getOverrideFont());
}

void GUIProfiler::OverrideFont::set(GUIFont^ value)
{
	m_GUIProfiler->setOverrideFont(LIME_SAFEREF(value, m_GUIFont));
}

bool GUIProfiler::ShowGroupsTogether::get()
{
	return m_GUIProfiler->getShowGroupsTogether();
}

void GUIProfiler::ShowGroupsTogether::set(bool value)
{
	m_GUIProfiler->setShowGroupsTogether(value);
}

}
}
