#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ref class MaterialRendererServices;
ref class ShaderCallBack;
class ShaderCallBackInheritor;

public ref class GPUProgrammingServices
{
public:

	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram);

	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial, int userData, GPUShadingLanguage shadingLang);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram);

	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram, Scene::PrimitiveType inType, Scene::PrimitiveType outType);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram, Scene::PrimitiveType inType);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, String^ geometryShaderProgram);

	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData, GPUShadingLanguage shadingLang);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType);
	ShaderCallBack^ AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget);

	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName);

	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial, int userData, GPUShadingLanguage shadingLang);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName);

	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName, Scene::PrimitiveType inType, Scene::PrimitiveType outType);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName, Scene::PrimitiveType inType);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, String^ geometryShaderFileName);

	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData, GPUShadingLanguage shadingLang);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType, unsigned int verticesOut);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType, Scene::PrimitiveType outType);
	ShaderCallBack^ AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint, VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget, String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget);

	ShaderCallBack^ AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial);
	ShaderCallBack^ AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram);
	ShaderCallBack^ AddShaderMaterial(String^ vertexShaderProgram);

	ShaderCallBack^ AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial, int userData);
	ShaderCallBack^ AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial);
	ShaderCallBack^ AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName);
	ShaderCallBack^ AddShaderMaterialFromFiles(String^ vertexShaderFileName);

internal:

	static GPUProgrammingServices^ Wrap(video::IGPUProgrammingServices* ref);
	GPUProgrammingServices(video::IGPUProgrammingServices* ref);

	video::IGPUProgrammingServices* m_GPUProgrammingServices;
};

} // end namespace Video
} // end namespace IrrlichtLime