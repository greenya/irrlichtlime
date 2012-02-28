#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

ref class MaterialLayer;
ref class Texture;

public ref class Material : Lime::NativeValue<video::SMaterial>
{
public:

	static property Material^ Identity { Material^ get() { return gcnew Material(); } }
	static property Material^ IdentityNoLighting { Material^ get() { Material^ m = gcnew Material(); m->Lighting = false; return m; } }
	static property Material^ IdentityRedWireframe { Material^ get() { Material^ m = gcnew Material(); m->EmissiveColor = gcnew Color(255, 0, 0); m->ZBuffer = ComparisonFunc::Always; m->Wireframe = true; return m; } }

	static property int MaxTextures { int get() { return video::MATERIAL_MAX_TEXTURES; } }

	Material();
	Material(Material^ other);

	bool GetFlag(MaterialFlag flag);
	Texture^ GetTexture(int index);
	Matrix^ GetTextureMatrix(int index);
	void SetFlag(MaterialFlag flag, bool value);
	void SetTexture(int index, Texture^ tex);
	void SetTextureMatrix(int index, Matrix^ mat);

	property Video::MaterialType Type { Video::MaterialType get(); void set(Video::MaterialType value); }
	property Color^ AmbientColor { Color^ get(); void set(Color^ value); }
	property Video::BlendOperation BlendOperation { Video::BlendOperation get(); void set(Video::BlendOperation value); }
	property Video::PolygonOffset PolygonOffsetDirection { Video::PolygonOffset get(); void set(Video::PolygonOffset value); }
	property unsigned char PolygonOffsetFactor { unsigned char get(); void set(unsigned char value); }
	property Color^ DiffuseColor { Color^ get(); void set(Color^ value); }
	property Color^ EmissiveColor { Color^ get(); void set(Color^ value); }
	property Color^ SpecularColor { Color^ get(); void set(Color^ value); }
	property float Shininess { float get(); void set(float value); }
	property float MaterialTypeParam { float get(); void set(float value); }
	property float MaterialTypeParam2 { float get(); void set(float value); }
	property float Thickness { float get(); void set(float value); }
	property ComparisonFunc ZBuffer { ComparisonFunc get(); void set(ComparisonFunc value); }
	property AntiAliasingMode AntiAliasing { AntiAliasingMode get(); void set(AntiAliasingMode value); }
	property ColorPlane ColorMask { ColorPlane get(); void set(ColorPlane value); }
	property Video::ColorMaterial ColorMaterial { Video::ColorMaterial get(); void set(Video::ColorMaterial value); }
	property bool Wireframe { bool get(); void set(bool value); }
	property bool PointCloud { bool get(); void set(bool value); }
	property bool GouraudShading { bool get(); void set(bool value); }
	property bool Lighting { bool get(); void set(bool value); }
	property bool ZWrite { bool get(); void set(bool value); }
	property bool BackfaceCulling { bool get(); void set(bool value); }
	property bool FrontfaceCulling { bool get(); void set(bool value); }
	property bool Fog { bool get(); void set(bool value); }
	property bool NormalizeNormals { bool get(); void set(bool value); }
	property bool Mipmaps { bool get(); void set(bool value); }
	property bool Transparent { bool get(); }

	property List<MaterialLayer^>^ Layer { List<MaterialLayer^>^ get(); }

	virtual String^ ToString() override;

internal:

	static Material^ Wrap(video::SMaterial* ref);
	Material(video::SMaterial* ref);
	Material(const video::SMaterial& copy);
};

} // end namespace Video
} // end namespace IrrlichtLime