#include "stdafx.h"
#include "LightManager.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {


LightManager^ LightManager::Wrap(scene::ILightManager* ref)
{
	if (ref == nullptr)
		return nullptr;

	try {
		LightManagerInheritor * lightManager;
		lightManager = dynamic_cast<LightManagerInheritor*> (ref);
		if (lightManager != 0)
			return lightManager->m_userLightManager;
	} catch (...){}

	return gcnew LightManager(ref);

}

LightManager::LightManager(scene::ILightManager* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_LightManager = ref;
	m_Inherited = false;
}

LightManager::LightManager()
	: ReferenceCounted(nullptr)
{

	LightManagerInheritor* i = new LightManagerInheritor();
	initInheritor(i);
	m_LightManager = i;
	m_ReferenceCounted = i;
	m_Inherited = true;
	
}

void LightManager::NodePostRender(SceneNode^ node)
{
	if (m_Inherited)
	{
		OnNodePostRender(node);
		return;
	}
	m_LightManager->OnNodePostRender(LIME_SAFEREF(node, m_SceneNode));
}

void LightManager::NodePreRender(SceneNode^ node)
{
	if (m_Inherited)
	{
		OnNodePreRender(node);
		return;
	}
	m_LightManager->OnNodePreRender(LIME_SAFEREF(node, m_SceneNode));
}

void LightManager::PostRender()
{
	if (m_Inherited)
	{
		OnPostRender();
		return;
	}
	m_LightManager->OnPostRender();
}

void LightManager::PreRender(array<SceneNode^>^ lightList)
{
	if (m_Inherited)
	{
		OnPreRender(lightList);
		return;
	}

	int lc = lightList->Length;
	core::array<ISceneNode*> la = core::array<ISceneNode*>(lc);
	for(int i = 0; i < lc; i++)
		la[i] = LIME_SAFEREF(lightList[i], m_SceneNode);

	m_LightManager->OnPreRender(la);
	//delete[] la;
}

void LightManager::RenderPassPostRender(SceneNodeRenderPass renderPass)
{
	if (m_Inherited)
	{
		OnRenderPassPostRender(renderPass);
		return;
	}
	m_LightManager->OnRenderPassPostRender((E_SCENE_NODE_RENDER_PASS)renderPass);
}

void LightManager::RenderPassPreRender(SceneNodeRenderPass renderPass)
{
	if (m_Inherited)
	{
		OnRenderPassPreRender(renderPass);
		return;
	}
	m_LightManager->OnRenderPassPreRender((E_SCENE_NODE_RENDER_PASS)renderPass);
}

String^ LightManager::ToString()
{
	return String::Format("LightManager");
}

void LightManager::initInheritor(LightManagerInheritor* i)
{
	i->m_userLightManager = this;
}

} // end namespace Scene
} // end namespace IrrlichtLime
