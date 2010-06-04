#pragma once
#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class ExposedVideoData : Lime::NativeValue<video::SExposedVideoData>
{
public:

	// ...

internal:

	ExposedVideoData(video::SExposedVideoData* ref)
	{
		LIME_ASSERT(ref != nullptr);
		m_NativeValue = ref;
		m_DeleteOnFinalization = false;
	}
};

} // end namespace Video
} // end namespace IrrlichtLime