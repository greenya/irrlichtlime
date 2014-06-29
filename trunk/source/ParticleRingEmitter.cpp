#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ParticleRingEmitter.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ParticleRingEmitter^ ParticleRingEmitter::Wrap(scene::IParticleRingEmitter* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew ParticleRingEmitter(ref);
}

ParticleRingEmitter::ParticleRingEmitter(scene::IParticleRingEmitter* ref)
	: ParticleEmitter(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_ParticleRingEmitter = ref;
}

Vector3Df ParticleRingEmitter::Center::get()
{
	return Vector3Df(m_ParticleRingEmitter->getCenter());
}

void ParticleRingEmitter::Center::set(Vector3Df value)
{
	m_ParticleRingEmitter->setCenter(value);
}

float ParticleRingEmitter::Radius::get()
{
	return m_ParticleRingEmitter->getRadius();
}

void ParticleRingEmitter::Radius::set(float value)
{
	m_ParticleRingEmitter->setRadius(value);
}

float ParticleRingEmitter::Thickness::get()
{
	return m_ParticleRingEmitter->getRingThickness();
}

void ParticleRingEmitter::Thickness::set(float value)
{
	m_ParticleRingEmitter->setRingThickness(value);
}

} // end namespace Scene
} // end namespace IrrlichtLime