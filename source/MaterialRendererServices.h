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

	int GetPixelShaderConstantID(String^ name);
	void SetPixelShaderConstantList(int startRegisterIndex, array<float>^ valueFloats, bool highLevelShader);
	bool SetPixelShaderConstant(int index, array<float>^ valueFloats, bool highLevelShader);
	bool SetPixelShaderConstant(int index, array<int>^ valueInts, bool highLevelShader);
	bool SetPixelShaderConstant(int index, float value, bool highLevelShader);
	bool SetPixelShaderConstant(int index, int value, bool highLevelShader);
	generic<typename T> where T : IShaderConstant bool SetPixelShaderConstant(int index, T value, bool highLevelShader);


	int GetVertexShaderConstantID(String^ name);
	void SetVertexShaderConstantList(int startRegisterIndex, array<float>^ valueFloats, bool highLevelShader);
	bool SetVertexShaderConstant(int index, array<float>^ valueFloats, bool highLevelShader);
	bool SetVertexShaderConstant(int index, array<int>^ valueInts, bool highLevelShader);
	bool SetVertexShaderConstant(int index, float value, bool highLevelShader);
	bool SetVertexShaderConstant(int index, int value, bool highLevelShader);
	generic<typename T> where T : IShaderConstant bool SetVertexShaderConstant(int index, T value, bool highLevelShader);

	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }

	virtual String^ ToString() override;

internal:

	static MaterialRendererServices^ Wrap(video::IMaterialRendererServices* ref);
	MaterialRendererServices(video::IMaterialRendererServices* ref);

	video::IMaterialRendererServices* m_MaterialRendererServices;
};

} // end namespace Video
} // end namespace IrrlichtLime