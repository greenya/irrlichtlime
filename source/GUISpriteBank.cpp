#include "stdafx.h"
#include "GUISpriteBank.h"
#include "ReferenceCounted.h"
#include "Rect.h"
#include "Texture.h"
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

void GUISpriteBank::AddTexture(Video::Texture^ texture)
{
	LIME_ASSERT(texture != nullptr);
	m_GUISpriteBank->addTexture(texture->m_Texture);
}

int GUISpriteBank::AddTextureAsSprite(Video::Texture^ texture)
{
	LIME_ASSERT(texture != nullptr);
	return m_GUISpriteBank->addTextureAsSprite(texture->m_Texture);
}

void GUISpriteBank::Clear()
{
	m_GUISpriteBank->clear();
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop, bool center)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime,
		loop,
		center);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime,
		loop);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip),
		color,
		starttime);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip),
		color);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos,
		LIME_NULLABLE(clip));
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Vector2Di pos)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	m_GUISpriteBank->draw2DSprite(
		index,
		pos);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors, unsigned int timeTicks, bool loop)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	video::SColor colors_native[4];
	if (colors != nullptr)
	{
		LIME_ASSERT(colors->Count == 4);
		colors_native[0] = colors[0];
		colors_native[1] = colors[1];
		colors_native[2] = colors[2];
		colors_native[3] = colors[3];
	}

	m_GUISpriteBank->draw2DSprite(
		index,
		destRect,
		LIME_NULLABLE(clip),
		colors == nullptr ? nullptr : colors_native,
		timeTicks,
		loop);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors, unsigned int timeTicks)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)
	
	video::SColor colors_native[4];
	if (colors != nullptr)
	{
		LIME_ASSERT(colors->Count == 4);
		colors_native[0] = colors[0];
		colors_native[1] = colors[1];
		colors_native[2] = colors[2];
		colors_native[3] = colors[3];
	}

	m_GUISpriteBank->draw2DSprite(
		index,
		destRect,
		LIME_NULLABLE(clip),
		colors == nullptr ? nullptr : colors_native,
		timeTicks);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)

	video::SColor colors_native[4];
	if (colors != nullptr)
	{
		LIME_ASSERT(colors->Count == 4);
		colors_native[0] = colors[0];
		colors_native[1] = colors[1];
		colors_native[2] = colors[2];
		colors_native[3] = colors[3];
	}

	m_GUISpriteBank->draw2DSprite(
		index,
		destRect,
		LIME_NULLABLE(clip),
		colors == nullptr ? nullptr : colors_native);
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count)

	m_GUISpriteBank->draw2DSprite(
		index,
		destRect,
		LIME_NULLABLE(clip));
}

void GUISpriteBank::Draw2DSprite(unsigned int index, Recti destRect)
{
	LIME_ASSERT(index >= 0 && index < (unsigned int)Sprites->Count);

	m_GUISpriteBank->draw2DSprite(
		index,
		destRect);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop, bool center)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime,
		loop,
		center);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime,
		loop);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip),
		color,
		starttime,
		currenttime);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip),
		color,
		starttime);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip),
		color);
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native,
		LIME_NULLABLE(clip));
}

void GUISpriteBank::Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos)
{
	LIME_ASSERT(indices != nullptr);
	LIME_ASSERT(pos != nullptr);
	//LIME_ASSERT(indices.Count == pos.Count);	//not needed, checked by Irrlicht itself

	core::array<u32> indices_native(indices->Count);
	core::array<core::vector2di> pos_native(pos->Count);
	for (int i = 0; i < indices->Count; i++)
		indices_native.push_back(indices[i]);
	for (int i = 0; i < pos->Count; i++)
		pos_native.push_back(pos[i]);

	m_GUISpriteBank->draw2DSpriteBatch(
		indices_native,
		pos_native);
}

Video::Texture^ GUISpriteBank::GetTexture(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < TextureCount);

	return Video::Texture::Wrap(m_GUISpriteBank->getTexture(index));
}

void GUISpriteBank::SetTexture(unsigned int index, Video::Texture^ texture)
{
	LIME_ASSERT(index >= 0 && index < TextureCount);
	LIME_ASSERT(texture != nullptr);

	m_GUISpriteBank->setTexture(index, texture->m_Texture);
}

NativeList<Recti>^ GUISpriteBank::Positions::get()
{
	core::array<core::rect<s32>>& positions = m_GUISpriteBank->getPositions();
	return gcnew NativeListIrrArrayTemplate<Recti, Recti, core::rect<s32>>(positions);
}

NativeList<GUISprite>^ GUISpriteBank::Sprites::get()
{
	core::array<gui::SGUISprite>& sprites = m_GUISpriteBank->getSprites();
	return gcnew NativeListIrrArrayTemplate<GUISprite, GUISprite, gui::SGUISprite>(sprites);
}

unsigned int GUISpriteBank::TextureCount::get()
{
	return m_GUISpriteBank->getTextureCount();
}

} // end namespace GUI
} // end namespace IrrlichtLime