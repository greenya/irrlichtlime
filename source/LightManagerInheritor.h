#pragma once

#include <vcclr.h> // for gcroot
#include "LightManager.h"
#include "SceneNode.h"
#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

class LightManagerInheritor : public scene::ILightManager
{
public:

	LightManagerInheritor()
		: ILightManager()
	{
	}

	gcroot<LightManager^> m_userLightManager;

	virtual void OnPreRender(core::array<ISceneNode*> & lightList)
	{
		int lc = lightList.size();
		array<SceneNode^>^ la = gcnew array<SceneNode^>(lc);
		for (int i = 0; i < lc; i++)
		{
			la[i] = SceneNode::Wrap(lightList[i]);
		}
		m_userLightManager->PreRender(la);
	}

	virtual void OnPostRender(void)
	{
		m_userLightManager->PostRender();
	}

	virtual void OnRenderPassPreRender(E_SCENE_NODE_RENDER_PASS renderPass)
	{
		m_userLightManager->RenderPassPreRender((SceneNodeRenderPass)renderPass);
	}

	virtual void OnRenderPassPostRender(E_SCENE_NODE_RENDER_PASS renderPass)
	{
		m_userLightManager->RenderPassPostRender((SceneNodeRenderPass)renderPass);
	}

	virtual void OnNodePreRender(ISceneNode* node)
	{
		m_userLightManager->NodePreRender(SceneNode::Wrap(node));
	}

	virtual void OnNodePostRender(ISceneNode* node)
	{
		m_userLightManager->NodePostRender(SceneNode::Wrap(node));
	}

};

} // end namespace Scene
} // end namespace IrrlichtLime