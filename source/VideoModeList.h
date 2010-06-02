#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class VideoModeList : ReferenceCounted
{
public:

	Dimension2Du^ GetResolution(Dimension2Du^ minSize, Dimension2Du^ maxSize);

	property VideoMode Desktop { VideoMode get(); }
	property List<VideoMode>^ ModeList { List<VideoMode>^ get(); }

	virtual String^ ToString() override;

internal:

	static VideoModeList^ Wrap(video::IVideoModeList* ref);
	VideoModeList(video::IVideoModeList* ref);

	video::IVideoModeList* m_VideoModeList;
};

} // end namespace Video
} // end namespace IrrlichtLime