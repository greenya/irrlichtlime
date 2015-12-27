#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::Collections::Generic;

namespace IrrlichtLime {
namespace GUI {

public value class GUISprite	//not inheriting NativeValue, because I didn't want to deal with that template for this most simple class
{
public:

    unsigned int FrameTime;

	GUISprite(GUISpriteFrame firstFrame)
	{
		FrameTime = 0;
		Frames->Add(firstFrame);
	}

	property List<GUISpriteFrame>^ Frames
	{
		List<GUISpriteFrame>^ get()
		{
			if (frames == nullptr)
				frames = gcnew List<GUISpriteFrame>();
			return frames;
		}
	}

internal:
	
	GUISprite(const gui::SGUISprite& value)
	{
		FrameTime = value.frameTime;
		frames = gcnew List<GUISpriteFrame>();
		unsigned int frameCount = value.Frames.size();

		for (unsigned int i=0; i < frameCount; i++)
			frames->Add(GUISpriteFrame(value.Frames[i]));
	}

	operator gui::SGUISprite()
	{
		gui::SGUISprite value;

		value.frameTime = FrameTime;
		for each (GUISpriteFrame frame in Frames)
			value.Frames.push_back(frame);

		return value;
	}

	gui::SGUISprite ToNative()
	{
		return (gui::SGUISprite)*this;
	}

	static GUISprite Wrap(const gui::SGUISprite& value)
	{
		return GUISprite(value);
	}

private:

	List<GUISpriteFrame>^ frames;

};

} // end namespace GUI
} // end namespace IrrlichtLime