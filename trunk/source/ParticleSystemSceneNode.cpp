#include "stdafx.h"
#include "ParticleAffector.h"
#include "ParticleEmitter.h"
#include "ParticleSystemSceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ParticleSystemSceneNode^ ParticleSystemSceneNode::Wrap(scene::IParticleSystemSceneNode* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew ParticleSystemSceneNode(ref);
}

ParticleSystemSceneNode::ParticleSystemSceneNode(scene::IParticleSystemSceneNode* ref)
	: SceneNode(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_ParticleSystemSceneNode = ref;
}

void ParticleSystemSceneNode::AddAffector(ParticleAffector^ affector)
{
	m_ParticleSystemSceneNode->addAffector(LIME_SAFEREF(affector, m_ParticleAffector));
}

void ParticleSystemSceneNode::RemoveAllAffectors()
{
	m_ParticleSystemSceneNode->removeAllAffectors();
}

void ParticleSystemSceneNode::SetParticlesAreGlobal(bool global)
{
	m_ParticleSystemSceneNode->setParticlesAreGlobal(global);
}

void ParticleSystemSceneNode::SetParticlesAreGlobal()
{
	m_ParticleSystemSceneNode->setParticlesAreGlobal();
}

void ParticleSystemSceneNode::SetParticleSize(Dimension2Df^ size)
{
	LIME_ASSERT(size != nullptr);
	m_ParticleSystemSceneNode->setParticleSize(*size->m_NativeValue);
}

void ParticleSystemSceneNode::SetParticleSize()
{
	m_ParticleSystemSceneNode->setParticleSize();
}

ParticleEmitter^ ParticleSystemSceneNode::Emitter::get()
{
	scene::IParticleEmitter* e = m_ParticleSystemSceneNode->getEmitter();
	return ParticleEmitter::Wrap(e);
}

void ParticleSystemSceneNode::Emitter::set(ParticleEmitter^ value)
{
	m_ParticleSystemSceneNode->setEmitter(LIME_SAFEREF(value, m_ParticleEmitter));
}

} // end namespace Scene
} // end namespace IrrlichtLime