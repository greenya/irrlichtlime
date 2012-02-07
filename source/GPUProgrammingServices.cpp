#include "stdafx.h"
#include "GPUProgrammingServices.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

GPUProgrammingServices^ GPUProgrammingServices::Wrap(video::IGPUProgrammingServices* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GPUProgrammingServices(ref);
}

GPUProgrammingServices::GPUProgrammingServices(video::IGPUProgrammingServices* ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GPUProgrammingServices = ref;
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	MaterialType baseMaterial, int userData)
{
	LIME_ASSERT(vertexShaderEntryPoint != nullptr);
	LIME_ASSERT(pixelShaderEntryPoint != nullptr);

	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addHighLevelShaderMaterial(
		Lime::StringToStringC(vertexShaderProgram).c_str(),
		Lime::StringToStringC(vertexShaderEntryPoint).c_str(),
		(video::E_VERTEX_SHADER_TYPE)vsCompileTarget,
		Lime::StringToStringC(pixelShaderProgram).c_str(),
		Lime::StringToStringC(pixelShaderEntryPoint).c_str(),
		(video::E_PIXEL_SHADER_TYPE)psCompileTarget,
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	MaterialType baseMaterial)
{
	return AddHighLevelShaderMaterial(vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram,
		pixelShaderEntryPoint, psCompileTarget, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget)
{
	return AddHighLevelShaderMaterial(vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram,
		pixelShaderEntryPoint, psCompileTarget, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget)
{
	return AddHighLevelShaderMaterial(vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget,
		"", "main", PixelShaderType::PS_1_1, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram)
{
	return AddHighLevelShaderMaterial(vertexShaderProgram, "main", VertexShaderType::VS_1_1,
		"", "main", PixelShaderType::PS_1_1, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData)
{
	LIME_ASSERT(vertexShaderEntryPoint != nullptr);
	LIME_ASSERT(pixelShaderEntryPoint != nullptr);
	LIME_ASSERT(geometryShaderEntryPoint != nullptr);

	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addHighLevelShaderMaterial(
		Lime::StringToStringC(vertexShaderProgram).c_str(),
		Lime::StringToStringC(vertexShaderEntryPoint).c_str(),
		(video::E_VERTEX_SHADER_TYPE)vsCompileTarget,
		Lime::StringToStringC(pixelShaderProgram).c_str(),
		Lime::StringToStringC(pixelShaderEntryPoint).c_str(),
		(video::E_PIXEL_SHADER_TYPE)psCompileTarget,
		Lime::StringToStringC(geometryShaderProgram).c_str(),
		Lime::StringToStringC(geometryShaderEntryPoint).c_str(),
		(video::E_GEOMETRY_SHADER_TYPE)gsCompileTarget,
		(scene::E_PRIMITIVE_TYPE)inType,
		(scene::E_PRIMITIVE_TYPE)outType,
		verticesOut,
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial)
{
	return AddHighLevelShaderMaterial(
		vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderProgram, geometryShaderEntryPoint, gsCompileTarget, inType, outType, verticesOut, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut)
{
	return AddHighLevelShaderMaterial(
		vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderProgram, geometryShaderEntryPoint, gsCompileTarget, inType, outType, verticesOut, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType)
{
	return AddHighLevelShaderMaterial(
		vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderProgram, geometryShaderEntryPoint, gsCompileTarget, inType, outType, 0, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterial(String^ vertexShaderProgram, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderProgram, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderProgram, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget)
{
	return AddHighLevelShaderMaterial(
		vertexShaderProgram, vertexShaderEntryPoint, vsCompileTarget, pixelShaderProgram, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderProgram, geometryShaderEntryPoint, gsCompileTarget, Scene::PrimitiveType::Triangles,
		Scene::PrimitiveType::TriangleStrip, 0, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	MaterialType baseMaterial, int userData)
{
	LIME_ASSERT(vertexShaderEntryPoint != nullptr);
	LIME_ASSERT(pixelShaderEntryPoint != nullptr);

	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addHighLevelShaderMaterialFromFiles(
		Lime::StringToPath(vertexShaderFileName),
		Lime::StringToStringC(vertexShaderEntryPoint).c_str(),
		(video::E_VERTEX_SHADER_TYPE)vsCompileTarget,
		Lime::StringToPath(pixelShaderFileName),
		Lime::StringToStringC(pixelShaderEntryPoint).c_str(),
		(video::E_PIXEL_SHADER_TYPE)psCompileTarget,
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	MaterialType baseMaterial)
{
	return AddHighLevelShaderMaterialFromFiles(vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName,
		pixelShaderEntryPoint, psCompileTarget, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget)
{
	return AddHighLevelShaderMaterialFromFiles(vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName,
		pixelShaderEntryPoint, psCompileTarget, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget)
{
	return AddHighLevelShaderMaterialFromFiles(vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget,
		"", "main", PixelShaderType::PS_1_1, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName)
{
	return AddHighLevelShaderMaterialFromFiles(vertexShaderFileName, "main", VertexShaderType::VS_1_1,
		"", "main", PixelShaderType::PS_1_1, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial, int userData)
{
	LIME_ASSERT(vertexShaderEntryPoint != nullptr);
	LIME_ASSERT(pixelShaderEntryPoint != nullptr);
	LIME_ASSERT(geometryShaderEntryPoint != nullptr);

	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addHighLevelShaderMaterialFromFiles(
		Lime::StringToPath(vertexShaderFileName),
		Lime::StringToStringC(vertexShaderEntryPoint).c_str(),
		(video::E_VERTEX_SHADER_TYPE)vsCompileTarget,
		Lime::StringToPath(pixelShaderFileName),
		Lime::StringToStringC(pixelShaderEntryPoint).c_str(),
		(video::E_PIXEL_SHADER_TYPE)psCompileTarget,
		Lime::StringToPath(geometryShaderFileName),
		Lime::StringToStringC(geometryShaderEntryPoint).c_str(),
		(video::E_GEOMETRY_SHADER_TYPE)gsCompileTarget,
		(scene::E_PRIMITIVE_TYPE)inType,
		(scene::E_PRIMITIVE_TYPE)outType,
		verticesOut,
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut, MaterialType baseMaterial)
{
	return AddHighLevelShaderMaterialFromFiles(
		vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderFileName, geometryShaderEntryPoint, gsCompileTarget, inType, outType, verticesOut, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType, unsigned int verticesOut)
{
	return AddHighLevelShaderMaterialFromFiles(
		vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderFileName, geometryShaderEntryPoint, gsCompileTarget, inType, outType, verticesOut, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget, Scene::PrimitiveType inType,
	Scene::PrimitiveType outType)
{
	return AddHighLevelShaderMaterialFromFiles(
		vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderFileName, geometryShaderEntryPoint, gsCompileTarget, inType, outType, 0, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddHighLevelShaderMaterialFromFiles(String^ vertexShaderFileName, String^ vertexShaderEntryPoint,
	VertexShaderType vsCompileTarget, String^ pixelShaderFileName, String^ pixelShaderEntryPoint, PixelShaderType psCompileTarget,
	String^ geometryShaderFileName, String^ geometryShaderEntryPoint, GeometryShaderType gsCompileTarget)
{
	return AddHighLevelShaderMaterialFromFiles(
		vertexShaderFileName, vertexShaderEntryPoint, vsCompileTarget, pixelShaderFileName, pixelShaderEntryPoint, psCompileTarget,
		geometryShaderFileName, geometryShaderEntryPoint, gsCompileTarget, Scene::PrimitiveType::Triangles,
		Scene::PrimitiveType::TriangleStrip, 0, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial, int userData)
{
	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addShaderMaterial(
		Lime::StringToStringC(vertexShaderProgram).c_str(),
		Lime::StringToStringC(pixelShaderProgram).c_str(),
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram, MaterialType baseMaterial)
{
	return AddShaderMaterial(vertexShaderProgram, pixelShaderProgram, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterial(String^ vertexShaderProgram, String^ pixelShaderProgram)
{
	return AddShaderMaterial(vertexShaderProgram, pixelShaderProgram, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterial(String^ vertexShaderProgram)
{
	return AddShaderMaterial(vertexShaderProgram, "", MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial, int userData)
{
	ShaderCallBackInheritor* c = new ShaderCallBackInheritor();
	c->m_SetConstantsHandler = gcnew SetConstantsHandler(this, &GPUProgrammingServices::SetConstants);
	c->m_SetMaterialHandler = gcnew SetMaterialHandler(this, &GPUProgrammingServices::SetMaterial);

	int o = m_GPUProgrammingServices->addShaderMaterialFromFiles(
		Lime::StringToPath(vertexShaderFileName),
		Lime::StringToPath(pixelShaderFileName),
		c,
		(video::E_MATERIAL_TYPE)baseMaterial,
		userData);

	c->drop();

	return (MaterialType)o;
}

MaterialType GPUProgrammingServices::AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName, MaterialType baseMaterial)
{
	return AddShaderMaterialFromFiles(vertexShaderFileName, pixelShaderFileName, baseMaterial, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterialFromFiles(String^ vertexShaderFileName, String^ pixelShaderFileName)
{
	return AddShaderMaterialFromFiles(vertexShaderFileName, pixelShaderFileName, MaterialType::Solid, 0);
}

MaterialType GPUProgrammingServices::AddShaderMaterialFromFiles(String^ vertexShaderFileName)
{
	return AddShaderMaterialFromFiles(vertexShaderFileName, "", MaterialType::Solid, 0);
}

void GPUProgrammingServices::SetConstants(MaterialRendererServices^ services, int userData)
{
	OnSetConstants(services, userData);
}

void GPUProgrammingServices::SetMaterial(Material^ material)
{
	OnSetMaterial(material);
}

} // end namespace Video
} // end namespace IrrlichtLime