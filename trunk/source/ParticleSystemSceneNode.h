#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class AnimatedMeshSceneNode;
ref class ParticleAffector;
ref class ParticleAnimatedMeshSceneNodeEmitter;
ref class ParticleAttractionAffector;
ref class ParticleBoxEmitter;
ref class ParticleCylinderEmitter;
ref class ParticleEmitter;
ref class ParticleFadeOutAffector;
ref class ParticleGravityAffector;

public ref class ParticleSystemSceneNode : SceneNode
{
public:

	void AddAffector(ParticleAffector^ affector);

	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex, bool everyMeshVertex);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier, int meshBufferIndex);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction, float normalDirectionModifier);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection, Vector3Df^ direction);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode, bool useNormalDirection);
	ParticleAnimatedMeshSceneNodeEmitter^ CreateAnimatedMeshSceneNodeEmitter(AnimatedMeshSceneNode^ particleNode);

	ParticleAttractionAffector^ CreateAttractionAffector(Vector3Df^ point, float speed, bool attract, bool affectX, bool affectY, bool affectZ);
	ParticleAttractionAffector^ CreateAttractionAffector(Vector3Df^ point, float speed, bool attract);
	ParticleAttractionAffector^ CreateAttractionAffector(Vector3Df^ point, float speed);
	ParticleAttractionAffector^ CreateAttractionAffector(Vector3Df^ point);

	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box, Vector3Df^ direction);
	ParticleBoxEmitter^ CreateBoxEmitter(AABBox3Df^ box);
	ParticleBoxEmitter^ CreateBoxEmitter();

	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees, Dimension2Df^ minStartSize, Dimension2Df^ maxStartSize);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax, int maxAngleDegrees);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor, unsigned int lifeTimeMin, unsigned int lifeTimeMax);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond, Video::Coloru^ minStartColor, Video::Coloru^ maxStartColor);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction, unsigned int minParticlesPerSecond, unsigned int maxParticlesPerSecond);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly, Vector3Df^ direction);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length, bool outlineOnly);
	ParticleCylinderEmitter^ CreateCylinderEmitter(Vector3Df^ center, float radius, Vector3Df^ normal, float length);

	ParticleFadeOutAffector^ CreateFadeOutParticleAffector(Video::Coloru^ targetColor, float timeNeededToFadeOut);
	ParticleFadeOutAffector^ CreateFadeOutParticleAffector(Video::Coloru^ targetColor);
	ParticleFadeOutAffector^ CreateFadeOutParticleAffector();

	ParticleGravityAffector^ CreateGravityAffector(Vector3Df^ gravity, float timeForceLost);
	ParticleGravityAffector^ CreateGravityAffector(Vector3Df^ gravity);
	ParticleGravityAffector^ CreateGravityAffector();

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