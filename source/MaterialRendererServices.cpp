#include "stdafx.h"
#include "Material.h"
#include "MaterialRendererServices.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

MaterialRendererServices^ MaterialRendererServices::Wrap(video::IMaterialRendererServices* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew MaterialRendererServices(ref);
}

MaterialRendererServices::MaterialRendererServices(video::IMaterialRendererServices* ref)
{
	LIME_ASSERT(ref != nullptr);
	m_MaterialRendererServices = ref;
}

void MaterialRendererServices::SetBasicRenderStates(Material^ newMaterial, Material^ lastMaterial, bool resetAllRenderStates)
{
	LIME_ASSERT(newMaterial != nullptr);
	LIME_ASSERT(lastMaterial != nullptr);

	m_MaterialRendererServices->setBasicRenderStates(
		*newMaterial->m_NativeValue,
		*lastMaterial->m_NativeValue,
		resetAllRenderStates);
}

void MaterialRendererServices::SetPixelShaderRegister(int registerIndex, array<float>^ value)
{
	LIME_ASSERT(registerIndex >= 0);
	LIME_ASSERT(value != nullptr);
	LIME_ASSERT(value->Length == 4);

	float f[4] = { value[0], value[1], value[2], value[3] };

	m_MaterialRendererServices->setPixelShaderConstant(
		f,
		registerIndex);
}

void MaterialRendererServices::SetPixelShaderRegisters(int startRegisterIndex, array<float>^ values)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(values != nullptr);
	LIME_ASSERT(values->Length >= 4);
	LIME_ASSERT((values->Length % 4) == 0);

	int c = values->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = values[i];

	m_MaterialRendererServices->setPixelShaderConstant(
		f,
		startRegisterIndex,
		c / 4);

	delete f;
}

bool MaterialRendererServices::SetPixelShaderVariable(String^ name, array<float>^ values)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(values != nullptr);

	int c = values->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = values[i];

	bool b = m_MaterialRendererServices->setPixelShaderConstant(
		Lime::StringToStringC(name).c_str(),
		f, c);

	delete f;
	return b;
}

void MaterialRendererServices::SetVertexShaderRegister(int registerIndex, array<float>^ value)
{
	LIME_ASSERT(registerIndex >= 0);
	LIME_ASSERT(value != nullptr);
	LIME_ASSERT(value->Length == 4);

	float f[4] = { value[0], value[1], value[2], value[3] };

	m_MaterialRendererServices->setVertexShaderConstant(
		f,
		registerIndex);
}

void MaterialRendererServices::SetVertexShaderRegisters(int startRegisterIndex, array<float>^ values)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(values != nullptr);
	LIME_ASSERT(values->Length >= 4);
	LIME_ASSERT((values->Length % 4) == 0);

	int c = values->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = values[i];

	m_MaterialRendererServices->setVertexShaderConstant(
		f,
		startRegisterIndex,
		c / 4);

	delete f;
}

bool MaterialRendererServices::SetVertexShaderVariable(String^ name, array<float>^ values)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(values != nullptr);

	int c = values->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = values[i];

	bool b = m_MaterialRendererServices->setVertexShaderConstant(
		Lime::StringToStringC(name).c_str(),
		f, c);

	delete f;
	return b;
}

Video::VideoDriver^ MaterialRendererServices::VideoDriver::get()
{
	video::IVideoDriver* d = m_MaterialRendererServices->getVideoDriver();
	return Video::VideoDriver::Wrap(d);
}

String^ MaterialRendererServices::ToString()
{
	return String::Format("MaterialRendererServices: VideoDriver={0}", VideoDriver);
}

} // end namespace Video
} // end namespace IrrlichtLime