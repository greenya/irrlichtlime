#include "stdafx.h"
#include "GUIFont.h"
#include "BillboardSceneNode.h"
#include "BillboardTextSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

BillboardTextSceneNode^ BillboardTextSceneNode::Wrap(scene::IBillboardTextSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew BillboardTextSceneNode(ref);
}

BillboardTextSceneNode::BillboardTextSceneNode(scene::IBillboardTextSceneNode* ref)
	: BillboardSceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_BillboardTextSceneNode = ref;
}

String^ BillboardTextSceneNode::GetText()
{
	const wchar_t* text = m_BillboardTextSceneNode->getText();
	if (text == nullptr)
		return nullptr;
	else
		return gcnew String(text);
}

void BillboardTextSceneNode::SetText(String^ text)
{
	m_BillboardTextSceneNode->setText(LIME_SAFESTRINGTOSTRINGW_C_STR(text));
}

void BillboardTextSceneNode::SetTextColor(Video::Color color)
{
	m_BillboardTextSceneNode->setTextColor(color);
}

GUI::GUIFont^ BillboardTextSceneNode::Font::get()
{
	return GUI::GUIFont::Wrap(m_BillboardTextSceneNode->getFont());
}

} // end namespace Scene
} // end namespace IrrlichtLime