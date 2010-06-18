#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class VolumeLightSceneNode : SceneNode
{
public:

	property Video::Coloru^ FootColor { Video::Coloru^ get(); void set(Video::Coloru^ value);  }
	property unsigned int SubDivideU { unsigned int get(); void set(unsigned int value); }
	property unsigned int SubDivideV { unsigned int get(); void set(unsigned int value); }
	property Video::Coloru^ TailColor { Video::Coloru^ get(); void set(Video::Coloru^ value);  }

internal:

	static VolumeLightSceneNode^ Wrap(scene::IVolumeLightSceneNode* ref);
	VolumeLightSceneNode(scene::IVolumeLightSceneNode* ref);

	scene::IVolumeLightSceneNode* m_VolumeLightSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime