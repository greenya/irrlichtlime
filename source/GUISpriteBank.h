#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace GUI {

public ref class GUISpriteBank : ReferenceCounted
{
public:

	void AddTexture(Video::Texture^ texure);
	int AddTextureAsSprite(Video::Texture^ texture);
	void Clear();

	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop, bool center);
	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop);
	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime);
	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime);
	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip, Video::Color color);
	void Draw2DSprite(unsigned int index, Vector2Di pos, Nullable<Recti> clip);
	void Draw2DSprite(unsigned int index, Vector2Di pos);

	void Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors, unsigned int timeTicks, bool loop);
	void Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors, unsigned int timeTicks);
	void Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip, IList<Video::Color>^ colors);
	void Draw2DSprite(unsigned int index, Recti destRect, Nullable<Recti> clip);
	void Draw2DSprite(unsigned int index, Recti destRect);

	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop, bool center);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime, bool loop);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime, unsigned int currenttime);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color, unsigned int starttime);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip, Video::Color color);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos, Nullable<Recti> clip);
	void Draw2DSpriteBatch(IList<unsigned int>^ indices, IList<Vector2Di>^ pos);

	Video::Texture^ GetTexture(unsigned int index);
	void SetTexture(unsigned int index, Video::Texture^ texture);

	property NativeList<Recti>^ Positions { NativeList<Recti>^ get(); }
	property NativeList<GUISprite>^ Sprites { NativeList<GUISprite>^ get(); }
	property unsigned int TextureCount { unsigned int get(); }

internal:

	static GUISpriteBank^ Wrap(gui::IGUISpriteBank* ref);
	GUISpriteBank(gui::IGUISpriteBank* ref);

	gui::IGUISpriteBank* m_GUISpriteBank;
};

} // end namespace GUI
} // end namespace IrrlichtLime