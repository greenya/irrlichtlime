#include "stdafx.h"
#include "TextSceneNode.h"
#include "GUIFont.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

TextSceneNode^ TextSceneNode::Wrap(scene::ITextSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew TextSceneNode(ref);
}

TextSceneNode::TextSceneNode(scene::ITextSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_TextSceneNode = ref;
}

String^ TextSceneNode::GetText()
{
	return gcnew String(m_TextSceneNode->getText());
}

void TextSceneNode::SetText(String^ text)
{
	m_TextSceneNode->setText(LIME_SAFESTRINGTOSTRINGW_C_STR(text));
}

Video::Color TextSceneNode::GetTextColor()
{
	return Video::Color(m_TextSceneNode->getTextColor());
}

void TextSceneNode::SetTextColor(Video::Color color)
{
	m_TextSceneNode->setTextColor(color);
}

GUI::GUIFont^ TextSceneNode::Font::get()
{
	return GUI::GUIFont::Wrap(m_TextSceneNode->getFont());
}

void TextSceneNode::Font::set(GUI::GUIFont^ value)
{
	m_TextSceneNode->setFont(value->m_GUIFont);
}

} // end namespace Scene
} // end namespace IrrlichtLime