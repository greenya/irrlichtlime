#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class ParticleAffector;
ref class ParticleEmitter;

public ref class ParticleSystemSceneNode : SceneNode
{
public:

	void AddAffector(ParticleAffector^ affector);

	void RemoveAllAffectors();

	void SetParticlesAreGlobal(bool global);
	void SetParticlesAreGlobal();

	void SetParticleSize(Dimension2Df^ size);
	void SetParticleSize();

	property ParticleEmitter^ Emitter { ParticleEmitter^ get(); void set(ParticleEmitter^ value); }

internal:

	static ParticleSystemSceneNode^ Wrap(scene::IParticleSystemSceneNode* ref);
	ParticleSystemSceneNode(scene::IParticleSystemSceneNode* ref);

	scene::IParticleSystemSceneNode* m_ParticleSystemSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime