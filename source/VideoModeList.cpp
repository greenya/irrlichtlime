#include "stdafx.h"
#include "ReferenceCounted.h"
#include "VideoModeList.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

VideoModeList^ VideoModeList::Wrap(video::IVideoModeList* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew VideoModeList(ref);
}

VideoModeList::VideoModeList(video::IVideoModeList* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_VideoModeList = ref;
}

Dimension2Du^ VideoModeList::GetResolution(Dimension2Du^ minSize, Dimension2Du^ maxSize)
{
	LIME_ASSERT(minSize != nullptr);
	LIME_ASSERT(maxSize != nullptr);
	return gcnew Dimension2Du(m_VideoModeList->getVideoModeResolution(*minSize->m_NativeValue, *maxSize->m_NativeValue));
}

VideoMode VideoModeList::Desktop::get()
{
	return VideoMode(m_VideoModeList->getDesktopResolution(), m_VideoModeList->getDesktopDepth());
}

List<VideoMode>^ VideoModeList::ModeList::get()
{
	List<VideoMode>^ l = gcnew List<VideoMode>();

	for (int i = 0; i < m_VideoModeList->getVideoModeCount(); i++)
		l->Add(VideoMode(m_VideoModeList->getVideoModeResolution(i), m_VideoModeList->getVideoModeDepth(i)));

	return l;
}

String^ VideoModeList::ToString()
{
	return String::Format("VideoModeList: Desktop={0}", Desktop);
}

} // end namespace Video
} // end namespace IrrlichtLime