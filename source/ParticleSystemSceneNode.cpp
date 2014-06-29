#include "stdafx.h"
#include "AnimatedMeshSceneNode.h"
#include "Mesh.h"
#include "ParticleAffector.h"
#include "ParticleAnimatedMeshSceneNodeEmitter.h"
#include "ParticleAttractionAffector.h"
#include "ParticleBoxEmitter.h"
#include "ParticleCylinderEmitter.h"
#include "ParticleEmitter.h"
#include "ParticleFadeOutAffector.h"
#include "ParticleGravityAffector.h"
#include "ParticleMeshEmitter.h"
#include "ParticleRingEmitter.h"
#include "ParticleRotationAffector.h"
#include "ParticleSphereEmitter.h"
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

void ParticleSystemSceneNode::ClearParticles()
{
	m_ParticleSystemSceneNode->clearParticles();
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex,
	int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier, int meshBufferIndex)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here

	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction, float normalDirectionModifier)
{
	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction,
		normalDirectionModifier);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection, Vector3Df direction)
{
	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection,
		direction);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode,
	bool useNormalDirection)
{
	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode),
		useNormalDirection);

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAnimatedMeshSceneNodeEmitter^ ParticleSystemSceneNode::CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode)
{
	scene::IParticleAnimatedMeshSceneNodeEmitter* e = m_ParticleSystemSceneNode->createAnimatedMeshSceneNodeEmitter(
		LIME_SAFEREF(particleNode, m_AnimatedMeshSceneNode));

	return ParticleAnimatedMeshSceneNodeEmitter::Wrap(e);
}

ParticleAttractionAffector^ ParticleSystemSceneNode::CreateAttractionAffector(Vector3Df point, float speed, bool attract, bool affectX, bool affectY, bool affectZ)
{
	scene::IParticleAttractionAffector* a = m_ParticleSystemSceneNode->createAttractionAffector(
		point,
		speed,
		attract,
		affectX,
		affectY,
		affectZ);

	return ParticleAttractionAffector::Wrap(a);
}

ParticleAttractionAffector^ ParticleSystemSceneNode::CreateAttractionAffector(Vector3Df point, float speed, bool attract)
{
	scene::IParticleAttractionAffector* a = m_ParticleSystemSceneNode->createAttractionAffector(
		point,
		speed,
		attract);

	return ParticleAttractionAffector::Wrap(a);
}

ParticleAttractionAffector^ ParticleSystemSceneNode::CreateAttractionAffector(Vector3Df point, float speed)
{
	scene::IParticleAttractionAffector* a = m_ParticleSystemSceneNode->createAttractionAffector(
		point,
		speed);

	return ParticleAttractionAffector::Wrap(a);
}

ParticleAttractionAffector^ ParticleSystemSceneNode::CreateAttractionAffector(Vector3Df point)
{
	scene::IParticleAttractionAffector* a = m_ParticleSystemSceneNode->createAttractionAffector(
		point);

	return ParticleAttractionAffector::Wrap(a);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction, int minParticlesPerSecond,
	int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax,
	int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction, int minParticlesPerSecond,
	int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax,
	int maxAngleDegrees)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction, int minParticlesPerSecond,
	int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction, int minParticlesPerSecond,
	int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction, int minParticlesPerSecond,
	int maxParticlesPerSecond)
{
	LIME_ASSERT(box != nullptr);
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box, Vector3Df direction)
{
	LIME_ASSERT(box != nullptr);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(
		*box->m_NativeValue,
		direction);

	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter(AABBox^ box)
{
	LIME_ASSERT(box != nullptr);

	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter(*box->m_NativeValue);
	return ParticleBoxEmitter::Wrap(e);
}

ParticleBoxEmitter^ ParticleSystemSceneNode::CreateBoxEmitter()
{
	scene::IParticleBoxEmitter* e = m_ParticleSystemSceneNode->createBoxEmitter();
	return ParticleBoxEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly,
	Vector3Df direction)
{
	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly,
		direction);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length, bool outlineOnly)
{
	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length,
		outlineOnly);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleCylinderEmitter^ ParticleSystemSceneNode::CreateCylinderEmitter(Vector3Df center, float radius, Vector3Df normal, float length)
{
	scene::IParticleCylinderEmitter* e = m_ParticleSystemSceneNode->createCylinderEmitter(
		center,
		radius,
		normal,
		length);

	return ParticleCylinderEmitter::Wrap(e);
}

ParticleFadeOutAffector^ ParticleSystemSceneNode::CreateFadeOutParticleAffector(Video::Color targetColor, float timeNeededToFadeOut)
{
	LIME_ASSERT(timeNeededToFadeOut >= 0.0f);

	scene::IParticleFadeOutAffector* a = m_ParticleSystemSceneNode->createFadeOutParticleAffector(
		targetColor,
		(u32)(timeNeededToFadeOut * 1000)); // "* 1000" because it takes u32 (value in milliseconds), but scene::IParticleFadeOutAffector operates with float

	return ParticleFadeOutAffector::Wrap(a);
}

ParticleFadeOutAffector^ ParticleSystemSceneNode::CreateFadeOutParticleAffector(Video::Color targetColor)
{
	scene::IParticleFadeOutAffector* a = m_ParticleSystemSceneNode->createFadeOutParticleAffector(
		targetColor);

	return ParticleFadeOutAffector::Wrap(a);
}

ParticleFadeOutAffector^ ParticleSystemSceneNode::CreateFadeOutParticleAffector()
{
	scene::IParticleFadeOutAffector* a = m_ParticleSystemSceneNode->createFadeOutParticleAffector();
	return ParticleFadeOutAffector::Wrap(a);
}

ParticleGravityAffector^ ParticleSystemSceneNode::CreateGravityAffector(Vector3Df gravity, unsigned int timeForceLost)
{
	scene::IParticleGravityAffector* a = m_ParticleSystemSceneNode->createGravityAffector(
		gravity,
		timeForceLost);

	return ParticleGravityAffector::Wrap(a);
}

ParticleGravityAffector^ ParticleSystemSceneNode::CreateGravityAffector(Vector3Df gravity)
{
	scene::IParticleGravityAffector* a = m_ParticleSystemSceneNode->createGravityAffector(
		gravity);

	return ParticleGravityAffector::Wrap(a);
}

ParticleGravityAffector^ ParticleSystemSceneNode::CreateGravityAffector()
{
	scene::IParticleGravityAffector* a = m_ParticleSystemSceneNode->createGravityAffector();
	return ParticleGravityAffector::Wrap(a);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees,
	Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex,
		everyMeshVertex);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier, int meshBufferIndex)
{
	LIME_ASSERT(meshBufferIndex >= -1); // -1 is valid value here

	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier,
		meshBufferIndex);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction,
	float normalDirectionModifier)
{
	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction,
		normalDirectionModifier);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection, Vector3Df direction)
{
	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection,
		direction);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh, bool useNormalDirection)
{
	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(
		LIME_SAFEREF(particleMesh, m_Mesh),
		useNormalDirection);

	return ParticleMeshEmitter::Wrap(e);
}

ParticleMeshEmitter^ ParticleSystemSceneNode::CreateMeshEmitter(Mesh^ particleMesh)
{
	scene::IParticleMeshEmitter* e = m_ParticleSystemSceneNode->createMeshEmitter(LIME_SAFEREF(particleMesh, m_Mesh));
	return ParticleMeshEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees,
	Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleEmitter::Wrap(e); // IParticlePointEmitter is synonim for IParticleEmitter
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond,
	Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction, int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter(Vector3Df direction)
{
	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter(direction);
	return ParticleEmitter::Wrap(e);
}

ParticleEmitter^ ParticleSystemSceneNode::CreatePointEmitter()
{
	scene::IParticlePointEmitter* e = m_ParticleSystemSceneNode->createPointEmitter();
	return ParticleEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness, Vector3Df direction)
{
	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness,
		direction);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRingEmitter^ ParticleSystemSceneNode::CreateRingEmitter(Vector3Df ringCenter, float ringRadius, float ringThickness)
{
	scene::IParticleRingEmitter* e = m_ParticleSystemSceneNode->createRingEmitter(
		ringCenter,
		ringRadius,
		ringThickness);

	return ParticleRingEmitter::Wrap(e);
}

ParticleRotationAffector^ ParticleSystemSceneNode::CreateRotationAffector(Vector3Df speed, Vector3Df pivot)
{
	scene::IParticleRotationAffector* a = m_ParticleSystemSceneNode->createRotationAffector(
		speed,
		pivot);

	return ParticleRotationAffector::Wrap(a);
}

ParticleRotationAffector^ ParticleSystemSceneNode::CreateRotationAffector(Vector3Df speed)
{
	scene::IParticleRotationAffector* a = m_ParticleSystemSceneNode->createRotationAffector(speed);
	return ParticleRotationAffector::Wrap(a);
}

ParticleRotationAffector^ ParticleSystemSceneNode::CreateRotationAffector()
{
	scene::IParticleRotationAffector* a = m_ParticleSystemSceneNode->createRotationAffector();
	return ParticleRotationAffector::Wrap(a);
}

ParticleAffector^ ParticleSystemSceneNode::CreateScaleParticleAffector(Dimension2Df^ scaleTo)
{
	LIME_ASSERT(scaleTo != nullptr);

	scene::IParticleAffector* a = m_ParticleSystemSceneNode->createScaleParticleAffector(*scaleTo->m_NativeValue);
	return ParticleAffector::Wrap(a);
}

ParticleAffector^ ParticleSystemSceneNode::CreateScaleParticleAffector()
{
	scene::IParticleAffector* a = m_ParticleSystemSceneNode->createScaleParticleAffector();
	return ParticleAffector::Wrap(a);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);
	LIME_ASSERT(minStartSize != nullptr);
	LIME_ASSERT(maxStartSize != nullptr);

	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees,
		*minStartSize->m_NativeValue,
		*maxStartSize->m_NativeValue);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax,
		maxAngleDegrees);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor,
	unsigned int lifeTimeMin, unsigned int lifeTimeMax)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);
	LIME_ASSERT(lifeTimeMin <= lifeTimeMax);

	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor,
		lifeTimeMin,
		lifeTimeMax);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond, Video::Color minStartColor, Video::Color maxStartColor)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond,
		minStartColor,
		maxStartColor);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction,
	int minParticlesPerSecond, int maxParticlesPerSecond)
{
	LIME_ASSERT(minParticlesPerSecond >= 0);
	LIME_ASSERT(maxParticlesPerSecond >= 0);
	LIME_ASSERT(minParticlesPerSecond <= maxParticlesPerSecond);

	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction,
		minParticlesPerSecond,
		maxParticlesPerSecond);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius, Vector3Df direction)
{
	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius,
		direction);

	return ParticleSphereEmitter::Wrap(e);
}

ParticleSphereEmitter^ ParticleSystemSceneNode::CreateSphereEmitter(Vector3Df sphereCenter, float sphereRadius)
{
	scene::IParticleSphereEmitter* e = m_ParticleSystemSceneNode->createSphereEmitter(
		sphereCenter,
		sphereRadius);

	return ParticleSphereEmitter::Wrap(e);
}

void ParticleSystemSceneNode::DoParticleSystem(unsigned int time)
{
	m_ParticleSystemSceneNode->doParticleSystem(time);
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

List<ParticleAffector^>^ ParticleSystemSceneNode::AffectorList::get()
{
	List<ParticleAffector^>^ l = gcnew List<ParticleAffector^>();

	core::list<scene::IParticleAffector*> a = m_ParticleSystemSceneNode->getAffectors();
	for (core::list<scene::IParticleAffector*>::ConstIterator i = a.begin(); i != a.end(); ++i)
		l->Add(ParticleAffector::Wrap(*i));

	return l;
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

Scene::ParticleBehavior ParticleSystemSceneNode::ParticleBehavior::get()
{
	return (Scene::ParticleBehavior)m_ParticleSystemSceneNode->getParticleBehavior();
}

void ParticleSystemSceneNode::ParticleBehavior::set(Scene::ParticleBehavior value)
{
	m_ParticleSystemSceneNode->setParticleBehavior((EParticleBehavior)value);
}

} // end namespace Scene
} // end namespace IrrlichtLime