#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

class LightManagerInheritor;
ref class SceneNode;

public ref class LightManager : ReferenceCounted
{
public:

	void NodePostRender(SceneNode^ node);
	void NodePreRender(SceneNode^ node);
	void PostRender();
	void PreRender(array<SceneNode^>^ lightList);
	void RenderPassPostRender(SceneNodeRenderPass renderPass);
	void RenderPassPreRender(SceneNodeRenderPass renderPass);

	virtual String^ ToString() override;

	delegate void NodePostRenderEventHandler(SceneNode^ node);
	delegate void NodePreRenderEventHandler(SceneNode^ node);
	delegate void PostRenderEventHandler();
	delegate void PreRenderEventHandler(array<SceneNode^>^ lightList);
	delegate void RenderPassPostRenderEventHandler(SceneNodeRenderPass renderPass);
	delegate void RenderPassPreRenderEventHandler(SceneNodeRenderPass renderPass);

protected:

	event NodePostRenderEventHandler^ OnNodePostRender;
	event NodePreRenderEventHandler^ OnNodePreRender;
	event PostRenderEventHandler^ OnPostRender;
	event PreRenderEventHandler^ OnPreRender;
	event RenderPassPostRenderEventHandler^ OnRenderPassPostRender;
	event RenderPassPreRenderEventHandler^ OnRenderPassPreRender;

	LightManager();

internal:

	static LightManager^ Wrap(scene::ILightManager* ref);
	LightManager(scene::ILightManager* ref);

	scene::ILightManager* m_LightManager;
	bool m_Inherited;

private:

	void initInheritor(LightManagerInheritor* i);
};

} // end namespace Scene
} // end namespace IrrlichtLime