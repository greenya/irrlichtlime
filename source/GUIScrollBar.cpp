#include "stdafx.h"
#include "GUIElement.h"
#include "GUIScrollBar.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIScrollBar::GUIScrollBar(gui::IGUIScrollBar* guiScrollBar)
	: GUIElement(guiScrollBar)
{
	LIME_ASSERT(guiScrollBar != nullptr);
	m_GUIScrollBar = guiScrollBar;
}

int GUIScrollBar::LargeStep::get()
{
	return m_GUIScrollBar->getLargeStep();
}

void GUIScrollBar::LargeStep::set(int value)
{
	m_GUIScrollBar->setLargeStep(value);
}

int GUIScrollBar::MaxValue::get()
{
	return m_GUIScrollBar->getMax();
}

void GUIScrollBar::MaxValue::set(int value)
{
	m_GUIScrollBar->setMax(value);
}

int GUIScrollBar::MinValue::get()
{
	return m_GUIScrollBar->getMin();
}

void GUIScrollBar::MinValue::set(int value)
{
	m_GUIScrollBar->setMin(value);
}

int GUIScrollBar::Position::get()
{
	return m_GUIScrollBar->getPos();
}

void GUIScrollBar::Position::set(int value)
{
	m_GUIScrollBar->setPos(value);
}

int GUIScrollBar::SmallStep::get()
{
	return m_GUIScrollBar->getSmallStep();
}

void GUIScrollBar::SmallStep::set(int value)
{
	m_GUIScrollBar->setSmallStep(value);
}

} // end namespace GUI
} // end namespace IrrlichtLime