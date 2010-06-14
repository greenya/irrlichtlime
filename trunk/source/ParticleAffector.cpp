#include "stdafx.h"
#include "AttributeExchangingObject.h"
#include "Particle.h"
#include "ParticleAffector.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ParticleAffector^ ParticleAffector::Wrap(scene::IParticleAffector* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew ParticleAffector(ref);
}

ParticleAffector::ParticleAffector(scene::IParticleAffector* ref)
	: IO::AttributeExchangingObject(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_ParticleAffector = ref;
}

void ParticleAffector::Affect(unsigned int now, List<Particle^>^ particleList)
{
	LIME_ASSERT(particleList != nullptr);
	LIME_ASSERT(particleList->Count > 0);

	int c = particleList->Count;
	scene::SParticle* a = new scene::SParticle[c];

	for (int i = 0; i < c; i++)
		a[i] = *(particleList[i]->m_NativeValue);

	m_ParticleAffector->affect(now, a, c);

	delete a;
}

bool ParticleAffector::Enabled::get()
{
	return m_ParticleAffector->getEnabled();
}

void ParticleAffector::Enabled::set(bool value)
{
	m_ParticleAffector->setEnabled(value);
}

ParticleAffectorType ParticleAffector::Type::get()
{
	return (ParticleAffectorType)m_ParticleAffector->getType();
}

String^ ParticleAffector::ToString()
{
	return String::Format("ParticleAffector: Type={0}", Type);
}

} // end namespace Scene
} // end namespace IrrlichtLime