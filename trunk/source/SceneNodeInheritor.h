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
		m_BoundingBox = core::aabbox3df();
	}

	gcroot<SceneNode::RenderEventHandler^> m_RenderHandler;
	virtual void render()
	{
		m_RenderHandler->Invoke();
	}

	virtual const core::aabbox3df& getBoundingBox() const
	{// temp code
		return m_BoundingBox;
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
		return m_Material;
	}

// "internal" section (C++ does not support this modificator)

	void AbsoluteTransformation_set(const core::matrix4& value)
	{
		AbsoluteTransformation = value;
	}

	void SceneManager_set(scene::ISceneManager* newManager)
	{
		setSceneManager(newManager);
	}

private:

	core::aabbox3df m_BoundingBox;
	video::SMaterial m_Material;
};

} // end namespace Scene
} // end namespace IrrlichtLime