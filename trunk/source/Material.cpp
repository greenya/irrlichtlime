#include "stdafx.h"
#include "Material.h"
#include "MaterialLayer.h"
#include "Texture.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

Material^ Material::Wrap(video::SMaterial* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew Material(ref);
}

Material::Material(video::SMaterial* ref)
	: Lime::NativeValue<video::SMaterial>(false)
{
	LIME_ASSERT(ref != nullptr);
	m_NativeValue = ref;
}

Material::Material()
	: Lime::NativeValue<video::SMaterial>(true)
{
	m_NativeValue = new video::SMaterial();
}

bool Material::GetFlag(MaterialFlag flag)
{
	return m_NativeValue->getFlag((E_MATERIAL_FLAG)flag);
}

void Material::SetFlag(MaterialFlag flag, bool value)
{
	m_NativeValue->setFlag((E_MATERIAL_FLAG)flag, value);
}

Matrix4f^ Material::GetTextureMatrix(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < Material::TextureCount);
	return gcnew Matrix4f(m_NativeValue->getTextureMatrix(index));
}

void Material::SetTexture(unsigned int index, Texture^ tex)
{
	LIME_ASSERT(index >= 0 && index < Material::TextureCount);
	m_NativeValue->setTexture(index, LIME_SAFEREF(tex, m_Texture));
}

void Material::SetTextureMatrix(unsigned int index, Matrix4f^ mat)
{
	LIME_ASSERT(mat != nullptr);
	LIME_ASSERT(index >= 0 && index < Material::TextureCount);
	m_NativeValue->setTextureMatrix(index, *mat->m_NativeValue);
}

List<MaterialLayer^>^ Material::Layer::get()
{
	List<MaterialLayer^>^ l = gcnew List<MaterialLayer^>();

	for (unsigned int i = 0; i < Material::TextureCount; i++)
		l->Add(gcnew MaterialLayer(&m_NativeValue->TextureLayer[i]));

	return l;
}

Texture^ Material::GetTexture(unsigned int index)
{
	LIME_ASSERT(index >= 0 && index < Material::TextureCount);
	video::ITexture* t = m_NativeValue->getTexture(index);
	return Texture::Wrap(t);
}

Video::MaterialType Material::Type::get()
{
	return (Video::MaterialType)m_NativeValue->MaterialType;
}

void Material::Type::set(Video::MaterialType value)
{
	m_NativeValue->MaterialType = (video::E_MATERIAL_TYPE)value;
}

Coloru^ Material::AmbientColor::get()
{
	return gcnew Coloru(m_NativeValue->AmbientColor);
}

void Material::AmbientColor::set(Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->AmbientColor = *value->m_NativeValue;
}

Coloru^ Material::DiffuseColor::get()
{
	return gcnew Coloru(m_NativeValue->DiffuseColor);
}
void Material::DiffuseColor::set(Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->DiffuseColor = *value->m_NativeValue;
}

Coloru^ Material::EmissiveColor::get()
{
	return gcnew Coloru(m_NativeValue->EmissiveColor);
}
void Material::EmissiveColor::set(Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->EmissiveColor = *value->m_NativeValue;
}

Coloru^ Material::SpecularColor::get()
{
	return gcnew Coloru(m_NativeValue->SpecularColor);
}

void Material::SpecularColor::set(Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_NativeValue->SpecularColor = *value->m_NativeValue;
}

float Material::Shininess::get()
{
	return m_NativeValue->Shininess;
}

void Material::Shininess::set(float value)
{
	m_NativeValue->Shininess = value;
}

float Material::MaterialTypeParam::get()
{
	return m_NativeValue->MaterialTypeParam;
}

void Material::MaterialTypeParam::set(float value)
{
	m_NativeValue->MaterialTypeParam = value;
}

float Material::MaterialTypeParam2::get()
{
	return m_NativeValue->MaterialTypeParam2;
}

void Material::MaterialTypeParam2::set(float value)
{
	m_NativeValue->MaterialTypeParam2 = value;
}

float Material::Thickness::get()
{
	return m_NativeValue->Thickness;
}

void Material::Thickness::set(float value)
{
	m_NativeValue->Thickness = value;
}

ZBufferCompFunc Material::ZBuffer::get()
{
	return (ZBufferCompFunc)m_NativeValue->ZBuffer;
}

void Material::ZBuffer::set(ZBufferCompFunc value)
{
	m_NativeValue->ZBuffer = (E_COMPARISON_FUNC)value;
}

AntiAliasingMode Material::AntiAliasing::get()
{
	return (AntiAliasingMode)m_NativeValue->AntiAliasing;
}

void Material::AntiAliasing::set(AntiAliasingMode value)
{
	m_NativeValue->AntiAliasing = (E_ANTI_ALIASING_MODE)value;
}

ColorPlane Material::ColorMask::get()
{
	return (ColorPlane)m_NativeValue->ColorMask;
}

void Material::ColorMask::set(ColorPlane value)
{
	m_NativeValue->ColorMask = (E_COLOR_PLANE)value;
}

Video::ColorMaterial Material::ColorMaterial::get()
{
	return (Video::ColorMaterial)m_NativeValue->ColorMaterial;
}

void Material::ColorMaterial::set(Video::ColorMaterial value)
{
	m_NativeValue->ColorMaterial = (E_COLOR_PLANE)value;
}

bool Material::Wireframe::get()
{
	return m_NativeValue->Wireframe;
}

void Material::Wireframe::set(bool value)
{
	m_NativeValue->Wireframe = value;
}

bool Material::PointCloud::get()
{
	return m_NativeValue->PointCloud;
}

void Material::PointCloud::set(bool value)
{
	m_NativeValue->PointCloud = value;
}

bool Material::GouraudShading::get()
{
	return m_NativeValue->GouraudShading;
}

void Material::GouraudShading::set(bool value)
{
	m_NativeValue->GouraudShading = value;
}

bool Material::Lighting::get()
{
	return m_NativeValue->Lighting;
}

void Material::Lighting::set(bool value)
{
	m_NativeValue->Lighting = value;
}

bool Material::ZWrite::get()
{
	return m_NativeValue->ZWriteEnable;
}

void Material::ZWrite::set(bool value)
{
	m_NativeValue->ZWriteEnable = value;
}

bool Material::BackfaceCulling::get()
{
	return m_NativeValue->BackfaceCulling;
}

void Material::BackfaceCulling::set(bool value)
{
	m_NativeValue->BackfaceCulling = value;
}

bool Material::FrontfaceCulling::get()
{
	return m_NativeValue->FrontfaceCulling;
}

void Material::FrontfaceCulling::set(bool value)
{
	m_NativeValue->FrontfaceCulling = value;
}

bool Material::Fog::get()
{
	return m_NativeValue->FogEnable;
}

void Material::Fog::set(bool value)
{
	m_NativeValue->FogEnable = value;
}

bool Material::NormalizeNormals::get()
{
	return m_NativeValue->NormalizeNormals;
}

void Material::NormalizeNormals::set(bool value)
{
	m_NativeValue->NormalizeNormals = value;
}

bool Material::Mipmaps::get()
{
	return m_NativeValue->UseMipMaps;
}

void Material::Mipmaps::set(bool value)
{
	m_NativeValue->UseMipMaps = value;
}

bool Material::Transparent::get()
{
	return m_NativeValue->isTransparent();
}

String^ Material::ToString()
{
	return String::Format("Material: Type={0}", Type);
}

} // end namespace Video
} // end namespace IrrlichtLime