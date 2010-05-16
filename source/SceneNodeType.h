#pragma once
#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public enum class SceneNodeType : UInt32
{
	Cube = ESNT_CUBE,
	Sphere = ESNT_SPHERE,
	Text = ESNT_TEXT,
	WaterSurface = ESNT_WATER_SURFACE,
	Terrain = ESNT_TERRAIN,
	SkyBox = ESNT_SKY_BOX,
	SkyDome = ESNT_SKY_DOME,
	ShadowVolume = ESNT_SHADOW_VOLUME,
	Octree = ESNT_OCTREE,
	Mesh = ESNT_MESH,
	Light = ESNT_LIGHT,
	Empty = ESNT_EMPTY,
	DummyTransformation = ESNT_DUMMY_TRANSFORMATION,
	Camera = ESNT_CAMERA,
	Billboard = ESNT_BILLBOARD,
	AnimatedMesh = ESNT_ANIMATED_MESH,
	ParticleSystem = ESNT_PARTICLE_SYSTEM,
	Quake3_Shader = ESNT_Q3SHADER_SCENE_NODE,
	Quake3_Model = ESNT_MD3_SCENE_NODE,
	VolumeLight = ESNT_VOLUME_LIGHT,
	Camera_Maya = ESNT_CAMERA_MAYA,
	Camera_FPS = ESNT_CAMERA_FPS,
	Unknown = ESNT_UNKNOWN,
	Any = ESNT_ANY
};

} // end namespace Scene
} // end namespace IrrlichtLime