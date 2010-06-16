#pragma once

#include "stdafx.h"
#include "ParticleAffector.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

public ref class ParticleFadeOutAffector : ParticleAffector
{
public:

	property float FadeOutTime { float get(); void set(float value); }
	property Video::Coloru^ TargetColor { Video::Coloru^ get(); void set(Video::Coloru^ value); }

internal:

	static ParticleFadeOutAffector^ Wrap(scene::IParticleFadeOutAffector* ref);
	ParticleFadeOutAffector(scene::IParticleFadeOutAffector* ref);

	scene::IParticleFadeOutAffector* m_ParticleFadeOutAffector;
};

} // end namespace Scene
} // end namespace IrrlichtLime