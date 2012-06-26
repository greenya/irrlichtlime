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

void MaterialRendererServices::SetPixelShaderConstant(int startRegisterIndex, array<float>^ valueFloats)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(valueFloats != nullptr);
	LIME_ASSERT(valueFloats->Length >= 4);
	LIME_ASSERT((valueFloats->Length % 4) == 0);

	int c = valueFloats->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = valueFloats[i];

	m_MaterialRendererServices->setPixelShaderConstant(
		f,
		startRegisterIndex,
		c / 4);

	delete f;
}

bool MaterialRendererServices::SetPixelShaderConstant(String^ name, array<float>^ valueFloats)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(valueFloats != nullptr);

	int c = valueFloats->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = valueFloats[i];

	bool b = m_MaterialRendererServices->setPixelShaderConstant(
		Lime::StringToStringC(name).c_str(),
		f, c);

	delete f;
	return b;
}

bool MaterialRendererServices::SetPixelShaderConstant(String^ name, array<int>^ valueInts)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(valueInts != nullptr);

	int c = valueInts->Length;
	int* v = new int[c];

	for (int i = 0; i < c; i++)
		v[i] = valueInts[i];

	bool b = m_MaterialRendererServices->setPixelShaderConstant(
		Lime::StringToStringC(name).c_str(),
		v, c);

	delete v;
	return b;
}

void MaterialRendererServices::SetVertexShaderConstant(int startRegisterIndex, array<float>^ valueFloats)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(valueFloats != nullptr);
	LIME_ASSERT(valueFloats->Length >= 4);
	LIME_ASSERT((valueFloats->Length % 4) == 0);

	int c = valueFloats->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = valueFloats[i];

	m_MaterialRendererServices->setVertexShaderConstant(
		f,
		startRegisterIndex,
		c / 4);

	delete f;
}

bool MaterialRendererServices::SetVertexShaderConstant(String^ name, array<float>^ valueFloats)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(valueFloats != nullptr);

	int c = valueFloats->Length;
	float* f = new float[c];

	for (int i = 0; i < c; i++)
		f[i] = valueFloats[i];

	bool b = m_MaterialRendererServices->setVertexShaderConstant(
		Lime::StringToStringC(name).c_str(),
		f, c);

	delete f;
	return b;
}

bool MaterialRendererServices::SetVertexShaderConstant(String^ name, array<int>^ valueInts)
{
	LIME_ASSERT(name != nullptr);
	LIME_ASSERT(valueInts != nullptr);

	int c = valueInts->Length;
	int* v = new int[c];

	for (int i = 0; i < c; i++)
		v[i] = valueInts[i];

	bool b = m_MaterialRendererServices->setVertexShaderConstant(
		Lime::StringToStringC(name).c_str(),
		v, c);

	delete v;
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