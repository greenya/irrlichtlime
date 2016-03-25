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

int MaterialRendererServices::GetPixelShaderConstantID(String^ name)
{
	LIME_ASSERT(name != nullptr);
	return m_MaterialRendererServices->getPixelShaderConstantID(LIME_SAFESTRINGTOSTRINGC_C_STR(name));
}

void MaterialRendererServices::SetPixelShaderConstantList(int startRegisterIndex, array<float>^ valueFloats, bool highLevelShader)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(valueFloats != nullptr);
	LIME_ASSERT(valueFloats->Length >= 4);
	LIME_ASSERT((valueFloats->Length % 4) == 0);

	int c = valueFloats->Length;
	pin_ptr<float> f = &valueFloats[0];

	if (!highLevelShader)
		c = (c - 1) / 4 + 1;

	m_MaterialRendererServices->setPixelShaderConstant(
		f,
		startRegisterIndex,
		c / 4);
}

bool MaterialRendererServices::SetPixelShaderConstant(int index, array<float>^ valueFloats, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(valueFloats != nullptr);

	int c = valueFloats->Length;
	pin_ptr<float> f = &valueFloats[0];

	bool b;
	if (!highLevelShader)
	{
		c = (c - 1) / 4 + 1;
		m_MaterialRendererServices->setPixelShaderConstant(f, index, c);
		b = true;
	} else
		b = m_MaterialRendererServices->setPixelShaderConstant(index, f, c);

	return b;
}

bool MaterialRendererServices::SetPixelShaderConstant(int index, array<int>^ valueInts, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(valueInts != nullptr);

	int c = valueInts->Length;
	pin_ptr<int> v = &valueInts[0];

	if (!highLevelShader)
		c = (c - 1) / 4 + 1;
	bool b = m_MaterialRendererServices->setPixelShaderConstant(index, v, c);

	return b;
}

bool MaterialRendererServices::SetPixelShaderConstant(int index, float valueFloat, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	float valueFloats = valueFloat; 
	float* f = &valueFloats;

	bool b;
	if (!highLevelShader)
	{
		m_MaterialRendererServices->setPixelShaderConstant(f, index, 1);
		b = true;
	} else
		b = m_MaterialRendererServices->setPixelShaderConstant(index, f, 1);

	return b;
}

bool MaterialRendererServices::SetPixelShaderConstant(int index, int valueInt, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	int valueInts = valueInt; 
	int* v = &valueInts;

	bool b;
	if (!highLevelShader)
	{
		m_MaterialRendererServices->setPixelShaderConstant(reinterpret_cast<float*>(v), index, 1);
		b = true;
	} else
		b = m_MaterialRendererServices->setPixelShaderConstant(index, v, 1);

	return b;
}

generic<typename T> where T : IShaderConstant
bool MaterialRendererServices::SetPixelShaderConstant(int index, T value, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	float valueFloats[16]; 
	float* f = &valueFloats[0];
	int c = value->GetData(f);

	bool b;
	if (!highLevelShader)
	{
		c = (c - 1) / 4 + 1;
		m_MaterialRendererServices->setPixelShaderConstant(f, index, c);
		b = true;
	} else
		b = m_MaterialRendererServices->setPixelShaderConstant(index, f, c);

	return b;
}

int MaterialRendererServices::GetVertexShaderConstantID(String^ name)
{
	LIME_ASSERT(name != nullptr);
	return m_MaterialRendererServices->getVertexShaderConstantID(LIME_SAFESTRINGTOSTRINGC_C_STR(name));
}

void MaterialRendererServices::SetVertexShaderConstantList(int startRegisterIndex, array<float>^ valueFloats, bool highLevelShader)
{
	LIME_ASSERT(startRegisterIndex >= 0);
	LIME_ASSERT(valueFloats != nullptr);
	LIME_ASSERT(valueFloats->Length >= 4);
	LIME_ASSERT((valueFloats->Length % 4) == 0);

	int c = valueFloats->Length;
	pin_ptr<float> f = &valueFloats[0];

	if (!highLevelShader)
		c = (c - 1) / 4 + 1;

	m_MaterialRendererServices->setVertexShaderConstant(
		f,
		startRegisterIndex,
		c / 4);
}

bool MaterialRendererServices::SetVertexShaderConstant(int index, array<float>^ valueFloats, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(valueFloats != nullptr);

	int c = valueFloats->Length;
	pin_ptr<float> f = &valueFloats[0];

	bool b;
	if (!highLevelShader)
	{
		c = (c - 1) / 4 + 1;
		m_MaterialRendererServices->setVertexShaderConstant(f, index, c);
		b = true;
	} else
		b = m_MaterialRendererServices->setVertexShaderConstant(index, f, c);

	return b;
}

bool MaterialRendererServices::SetVertexShaderConstant(int index, array<int>^ valueInts, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);
	LIME_ASSERT(valueInts != nullptr);

	int c = valueInts->Length;
	pin_ptr<int> v = &valueInts[0];

	if (!highLevelShader)
		c = (c - 1) / 4 + 1;
	bool b = m_MaterialRendererServices->setVertexShaderConstant(index,	v, c);

	return b;
}

bool MaterialRendererServices::SetVertexShaderConstant(int index, float valueFloat, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	float valueFloats = valueFloat;
	float* f = &valueFloats;

	bool b;
	if (!highLevelShader)
	{
		m_MaterialRendererServices->setVertexShaderConstant(f, index, 1);
		b = true;
	} else
		b = m_MaterialRendererServices->setVertexShaderConstant(index, f, 1);

	return b;
}

bool MaterialRendererServices::SetVertexShaderConstant(int index, int valueInt, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	int valueInts = valueInt;
	int* v = &valueInts;

	bool b;
	if (!highLevelShader)
	{
		m_MaterialRendererServices->setVertexShaderConstant(reinterpret_cast<float*>(v), index, 1);
		b = true;
	} else
		b = m_MaterialRendererServices->setVertexShaderConstant(index, v, 1);

	return b;
}

generic<typename T> where T : IShaderConstant
bool MaterialRendererServices::SetVertexShaderConstant(int index, T value, bool highLevelShader)
{
	LIME_ASSERT(index >= 0);

	float valueFloats[16]; 
	float* f = &valueFloats[0];
	int c = value->GetData(f);

	bool b;
	if (!highLevelShader)
	{
		c = (c - 1) / 4 + 1;
		m_MaterialRendererServices->setVertexShaderConstant(f, index, c);
		b = true;
	} else
		b = m_MaterialRendererServices->setVertexShaderConstant(index, f, c);

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