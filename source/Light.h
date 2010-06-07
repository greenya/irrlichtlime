#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video {

public ref class Light : Lime::NativeValue<video::SLight, Lime::NativeValueKind::Ref>
{
public:

	Light();

	property Colorf^ AmbientColor { Colorf^ get(); void set(Colorf^ value); }
	property Vector3Df^ Attenuation { Vector3Df^ get(); void set(Vector3Df^ value); }
	property bool CastShadows { bool get(); }
	property Colorf^ DiffuseColor { Colorf^ get(); void set(Colorf^ value); }
	property Vector3Df^ Direction { Vector3Df^ get(); }
	property float Falloff { float get(); void set(float value); }
	property float InnerCone { float get(); void set(float value); }
	property float OuterCone { float get(); void set(float value); }
	property Vector3Df^ Position { Vector3Df^ get(); }
	property float Radius { float get(); }
	property Colorf^ SpecularColor { Colorf^ get(); void set(Colorf^ value); }
	property LightType Type { LightType get(); }

	virtual String^ ToString() override;

internal:

	Light(video::SLight* ref);
};

} // end namespace Video
} // end namespace IrrlichtLime