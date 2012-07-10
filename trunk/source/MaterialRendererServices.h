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

	void SetPixelShaderConstant(int startRegisterIndex, array<float>^ valueFloats);
	bool SetPixelShaderConstant(String^ name, array<float>^ valueFloats);
	bool SetPixelShaderConstant(String^ name, array<int>^ valueInts);
	bool SetPixelShaderConstant(String^ name, array<bool>^ valueBools);

	void SetVertexShaderConstant(int startRegisterIndex, array<float>^ valueFloats);
	bool SetVertexShaderConstant(String^ name, array<float>^ valueFloats);
	bool SetVertexShaderConstant(String^ name, array<int>^ valueInts);
	bool SetVertexShaderConstant(String^ name, array<bool>^ valueBools);

	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }

	virtual String^ ToString() override;

internal:

	static MaterialRendererServices^ Wrap(video::IMaterialRendererServices* ref);
	MaterialRendererServices(video::IMaterialRendererServices* ref);

	video::IMaterialRendererServices* m_MaterialRendererServices;
};

} // end namespace Video
} // end namespace IrrlichtLime