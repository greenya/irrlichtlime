#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Scene
{
	public ref class SceneNode
	{
	public:

	internal:

		scene::ISceneNode* m_SceneNode;

		SceneNode(scene::ISceneNode* sceneNode)
		{
			m_SceneNode = sceneNode;
		}
	};
}
}