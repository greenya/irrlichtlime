#include "stdafx.h"
#include "Light.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

Light::Light(video::SLight* ref)
{
	LIME_ASSERT(ref != nullptr);
	m_NativeValue = ref;
}

Light::Light()
{
	m_NativeValue = new video::SLight();
}

Colorf^ Light::AmbientColor::get()
{
	return gcnew Colorf(m_NativeValue->AmbientColor);
}

void Light::AmbientColor::set(Colorf^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->AmbientColor = *value->m_NativeValue;
}

Vector3Df^ Light::Attenuation::get()
{
	return gcnew Vector3Df(m_NativeValue->Attenuation);
}

void Light::Attenuation::set(Vector3Df^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->Attenuation = *value->m_NativeValue;
}

bool Light::CastShadows::get()
{
	return m_NativeValue->CastShadows;
}

Colorf^ Light::DiffuseColor::get()
{
	return gcnew Colorf(m_NativeValue->DiffuseColor);
}

void Light::DiffuseColor::set(Colorf^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->DiffuseColor = *value->m_NativeValue;
}

Vector3Df^ Light::Direction::get()
{
	return gcnew Vector3Df(m_NativeValue->Direction);
}

float Light::Falloff::get()
{
	return m_NativeValue->Falloff;
}

void Light::Falloff::set(float value)
{
	m_NativeValue->Falloff = value;
}

float Light::InnerCone::get()
{
	return m_NativeValue->InnerCone;
}

void Light::InnerCone::set(float value)
{
	m_NativeValue->InnerCone = value;
}

float Light::OuterCone::get()
{
	return m_NativeValue->OuterCone;
}

void Light::OuterCone::set(float value)
{
	m_NativeValue->OuterCone = value;
}

Vector3Df^ Light::Position::get()
{
	return gcnew Vector3Df(m_NativeValue->Position);
}

float Light::Radius::get()
{
	return m_NativeValue->Radius;
}

Colorf^ Light::SpecularColor::get()
{
	return gcnew Colorf(m_NativeValue->SpecularColor);
}

void Light::SpecularColor::set(Colorf^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->SpecularColor = *value->m_NativeValue;
}

LightType Light::Type::get()
{
	return (LightType)m_NativeValue->Type;
}

String^ Light::ToString()
{
	return String::Format("Light: Type={0}", Type);
}

} // end namespace Video
} // end namespace IrrlichtLime