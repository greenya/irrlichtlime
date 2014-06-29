#include "stdafx.h"
#include "Light.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

Light::Light(video::SLight* ref)
	: Lime::NativeValue<video::SLight>(false)
{
	LIME_ASSERT(ref != nullptr);
	m_NativeValue = ref;
}

Light::Light()
	: Lime::NativeValue<video::SLight>(true)
{
	m_NativeValue = new video::SLight();
}

Colorf Light::AmbientColor::get()
{
	return Colorf(m_NativeValue->AmbientColor);
}

void Light::AmbientColor::set(Colorf value)
{
	m_NativeValue->AmbientColor = value;
}

Vector3Df Light::Attenuation::get()
{
	return Vector3Df(m_NativeValue->Attenuation);
}

void Light::Attenuation::set(Vector3Df value)
{
	m_NativeValue->Attenuation = value;
}

bool Light::CastShadows::get()
{
	return m_NativeValue->CastShadows;
}

void Light::CastShadows::set(bool value)
{
	m_NativeValue->CastShadows = value;
}

Colorf Light::DiffuseColor::get()
{
	return Colorf(m_NativeValue->DiffuseColor);
}

void Light::DiffuseColor::set(Colorf value)
{
	m_NativeValue->DiffuseColor = value;
}

Vector3Df Light::Direction::get()
{
	return Vector3Df(m_NativeValue->Direction);
}

void Light::Direction::set(Vector3Df value)
{
	m_NativeValue->Direction = value;
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

Vector3Df Light::Position::get()
{
	return Vector3Df(m_NativeValue->Position);
}

void Light::Position::set(Vector3Df value)
{
	m_NativeValue->Position = value;
}

float Light::Radius::get()
{
	return m_NativeValue->Radius;
}

void Light::Radius::set(float value)
{
	m_NativeValue->Radius = value;
}

Colorf Light::SpecularColor::get()
{
	return Colorf(m_NativeValue->SpecularColor);
}

void Light::SpecularColor::set(Colorf value)
{
	m_NativeValue->SpecularColor = value;
}

LightType Light::Type::get()
{
	return (LightType)m_NativeValue->Type;
}

void Light::Type::set(LightType value)
{
	m_NativeValue->Type = (video::E_LIGHT_TYPE)value;
}

String^ Light::ToString()
{
	return String::Format("Light: Type={0}", Type);
}

} // end namespace Video
} // end namespace IrrlichtLime