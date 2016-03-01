#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class ContextManager : ReferenceCounted
{
public:
	
	bool ActivateContext(ExposedVideoData^ videoData);
	void DestroyContext();
	void DestroySurface();
	bool GenerateContext();
	bool GenerateSurface();
	bool Initialize(IrrlichtCreationParameters^ params, ExposedVideoData^ data);
	void Terminate();
	bool SwapBuffers();

	property ExposedVideoData^ Context { ExposedVideoData^ get(); }

internal:

	static ContextManager^ Wrap(video::IContextManager* ref);
	ContextManager(video::IContextManager* ref);

	video::IContextManager* m_ContextManager;
};

} // end namespace Video
} // end namespace IrrlichtLime