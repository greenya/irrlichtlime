#pragma once

#include <vcclr.h> // for gcroot
#include "stdafx.h"
#include "GPUProgrammingServices.h"
#include "MaterialRendererServices.h"
#include "ShaderCallBack.h"

namespace IrrlichtLime {
namespace Video {

class ShaderCallBackInheritor : public video::IShaderConstantSetCallBack
{
public:

	gcroot<ShaderCallBack^> m_ShaderCallBack;

	virtual void OnSetConstants(video::IMaterialRendererServices* services, int userData)
	{
		LIME_ASSERT((ShaderCallBack^)m_ShaderCallBack != nullptr)	//If it is null, creating the material failed. Irrlicht should not call this at all.

		m_ShaderCallBack->SetConstants(
			MaterialRendererServices::Wrap(services),
			userData);
	}

	virtual void OnSetMaterial(const SMaterial& material)
	{
		LIME_ASSERT((ShaderCallBack^)m_ShaderCallBack != nullptr)	//If it is null, creating the material failed. Irrlicht should not call this at all.

		m_ShaderCallBack->SetMaterial(
			Material::Wrap((SMaterial*)&material)); // !!! cast to non-const
	}
};

} // end namespace Video
} // end namespace IrrlichtLime