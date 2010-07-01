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

	static property int TextureCount { int get() { return video::MATERIAL_MAX_TEXTURES; } }

	Material();

	bool GetFlag(MaterialFlag flag);
	Texture^ GetTexture(int index);
	Matrix^ GetTextureMatrix(int index);
	void SetFlag(MaterialFlag flag, bool value);
	void SetTexture(int index, Texture^ tex);
	void SetTextureMatrix(int index, Matrix^ mat);

	property Video::MaterialType Type { Video::MaterialType get(); void set(Video::MaterialType value); }
	property Color^ AmbientColor { Color^ get(); void set(Color^ value); }
	property Color^ DiffuseColor { Color^ get(); void set(Color^ value); }
	property Color^ EmissiveColor { Color^ get(); void set(Color^ value); }
	property Color^ SpecularColor { Color^ get(); void set(Color^ value); }
	property float Shininess { float get(); void set(float value); }
	property float MaterialTypeParam { float get(); void set(float value); }
	property float MaterialTypeParam2 { float get(); void set(float value); }
	property float Thickness { float get(); void set(float value); }
	property ZBufferCompFunc ZBuffer { ZBufferCompFunc get(); void set(ZBufferCompFunc value); }
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
};

} // end namespace Video
} // end namespace IrrlichtLime