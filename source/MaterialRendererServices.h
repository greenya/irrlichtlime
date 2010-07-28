#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class Material;
ref class VideoDriver;

public ref class MaterialRendererServices
{
public:

	void SetBasicRenderStates(Material^ newMaterial, Material^ lastMaterial, bool resetAllRenderStates);

	void SetPixelShaderRegisters(int startRegisterIndex, array<float>^ values);
	bool SetPixelShaderVariable(String^ name, array<float>^ values);

	void SetVertexShaderRegisters(int startRegisterIndex, array<float>^ values);
	bool SetVertexShaderVariable(String^ name, array<float>^ values);

	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }

	virtual String^ ToString() override;

internal:

	static MaterialRendererServices^ Wrap(video::IMaterialRendererServices* ref);
	MaterialRendererServices(video::IMaterialRendererServices* ref);

	video::IMaterialRendererServices* m_MaterialRendererServices;
};

} // end namespace Video
} // end namespace IrrlichtLime