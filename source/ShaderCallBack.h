#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class ShaderCallBack
{
public:

	delegate void SetConstantsHandler(MaterialRendererServices^ services, int userData);
	event SetConstantsHandler^ OnSetConstants;

	delegate void SetMaterialHandler(Material^ material);
	event SetMaterialHandler^ OnSetMaterial;

	property Video::MaterialType MaterialType { Video::MaterialType get() { return m_MaterialType; } }

	static operator Video::MaterialType(ShaderCallBack^ callback)
	{
		if (callback == nullptr)
			return (Video::MaterialType)-1;

		return callback->m_MaterialType;
	}

internal:

	static ShaderCallBack^ Wrap(Video::MaterialType materialType)
	{
		if ((int)materialType == -1)
			return nullptr;

		return gcnew ShaderCallBack(materialType);
	}

	void SetConstants(MaterialRendererServices^ services, int userData)
	{
		OnSetConstants(services, userData);
	}

	void SetMaterial(Material^ material)
	{
		OnSetMaterial(material);
	}

private:

	ShaderCallBack(Video::MaterialType materialType)
		: m_MaterialType(materialType) { }

	Video::MaterialType m_MaterialType;
};

} // end namespace Video
} // end namespace IrrlichtLime