#pragma once

#include <vcclr.h> // for gcroot
#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace Scene {

class SceneNodeInheritor : public scene::ISceneNode
{
public:

	SceneNodeInheritor(scene::ISceneNode* parent, scene::ISceneManager* manager, int id=-1,
		const core::vector3df& position = core::vector3df(0),
		const core::vector3df& rotation = core::vector3df(0),
		const core::vector3df& scale = core::vector3df(1))
		: ISceneNode(parent, manager, id, position, rotation, scale)
	{
		m_boundingBox = core::aabbox3df();
	}

	gcroot<SceneNode::RenderEventHandler^> m_renderHandler;
	virtual void render()
	{
		m_renderHandler->Invoke();
	}

	virtual const core::aabbox3df& getBoundingBox() const
	{// temp code
		return m_boundingBox;
	}

	virtual void OnRegisterSceneNode()
	{// temp code
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	virtual u32 getMaterialCount() const
	{// temp code
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{// temp code
		SMaterial m;
		return m;
	} 

private:

	core::aabbox3df m_boundingBox;
};

} // end namespace Scene
} // end namespace IrrlichtLime