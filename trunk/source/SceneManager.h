#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO { ref class FileSystem; }
namespace GUI { ref class GUIEnvironment; }
namespace Video { ref class Texture; ref class VideoDriver; }
namespace Scene {

ref class AnimatedMesh;
ref class AnimatedMeshSceneNode;
ref class BillboardSceneNode;
ref class CameraSceneNode;
ref class CollisionResponseSceneNodeAnimator;
ref class LightSceneNode;
ref class Mesh;
ref class MeshManipulator;
ref class MeshSceneNode;
ref class ParticleSystemSceneNode;
ref class SceneCollisionManager;
ref class SceneNode;
ref class SceneNodeAnimator;
ref class TriangleSelector;
ref class VolumeLightSceneNode;

public ref class SceneManager : ReferenceCounted
{
public:

	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale, bool alsoAddIfMeshPointerZero);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id, Vector3Df^ position);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent);
	AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh);

	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id, Video::Coloru^ colorTop, Video::Coloru^ colorBottom);
	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id, Video::Coloru^ colorTop);
	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id);
	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position);
	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size);
	BillboardSceneNode^ AddBillboardSceneNode(SceneNode^ parent);
	BillboardSceneNode^ AddBillboardSceneNode();

	CameraSceneNode^ AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, int id, bool makeActive);
	CameraSceneNode^ AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, int id);
	CameraSceneNode^ AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat);
	CameraSceneNode^ AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position);
	CameraSceneNode^ AddCameraSceneNode(SceneNode^ parent);
	CameraSceneNode^ AddCameraSceneNode();

	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse, bool makeActive);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed);
	CameraSceneNode^ AddCameraSceneNodeFPS(SceneNode^ parent);
	CameraSceneNode^ AddCameraSceneNodeFPS();

	MeshSceneNode^ AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	MeshSceneNode^ AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	MeshSceneNode^ AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position);
	MeshSceneNode^ AddCubeSceneNode(float size, SceneNode^ parent, int id);
	MeshSceneNode^ AddCubeSceneNode(float size, SceneNode^ parent);
	MeshSceneNode^ AddCubeSceneNode(float size);
	MeshSceneNode^ AddCubeSceneNode();

	AnimatedMesh^ AddHillPlaneMesh(String^ name, Dimension2Df^ tileSize, Dimension2Du^ tileCount, Video::Material^ material, float hillHeight, Dimension2Df^ countHills, Dimension2Df^ textureRepeatCount);
	AnimatedMesh^ AddHillPlaneMesh(String^ name, Dimension2Df^ tileSize, Dimension2Du^ tileCount, Video::Material^ material, float hillHeight, Dimension2Df^ countHills);
	AnimatedMesh^ AddHillPlaneMesh(String^ name, Dimension2Df^ tileSize, Dimension2Du^ tileCount, Video::Material^ material, float hillHeight);
	AnimatedMesh^ AddHillPlaneMesh(String^ name, Dimension2Df^ tileSize, Dimension2Du^ tileCount, Video::Material^ material);
	AnimatedMesh^ AddHillPlaneMesh(String^ name, Dimension2Df^ tileSize, Dimension2Du^ tileCount);

	LightSceneNode^ AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color, float radius, int id);
	LightSceneNode^ AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color, float radius);
	LightSceneNode^ AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color);
	LightSceneNode^ AddLightSceneNode(SceneNode^ parent, Vector3Df^ position);
	LightSceneNode^ AddLightSceneNode(SceneNode^ parent);
	LightSceneNode^ AddLightSceneNode();

	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode, bool alsoAddIfMeshPointerZero);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh);

	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter, SceneNode^ parent, int id, Vector3Df^ position);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter, SceneNode^ parent, int id);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter, SceneNode^ parent);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode(bool withDefaultEmitter);
	ParticleSystemSceneNode^ AddParticleSystemSceneNode();

	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount);
	MeshSceneNode^ AddSphereSceneNode(float radius);
	MeshSceneNode^ AddSphereSceneNode();

	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV, Video::Coloru^ foot, Video::Coloru^ tail, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV, Video::Coloru^ foot, Video::Coloru^ tail, Vector3Df^ position, Vector3Df^ rotation);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV, Video::Coloru^ foot, Video::Coloru^ tail, Vector3Df^ position);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV, Video::Coloru^ foot, Video::Coloru^ tail);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV, Video::Coloru^ foot);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU, unsigned int subdivV);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id, unsigned int subdivU);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent, int id);
	VolumeLightSceneNode^ AddVolumeLightSceneNode(SceneNode^ parent);
	VolumeLightSceneNode^ AddVolumeLightSceneNode();

	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength, SceneNode^ parent, int id, Vector3Df^ position);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength, SceneNode^ parent, int id);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength, SceneNode^ parent);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed, float waveLength);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight, float waveSpeed);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh, float waveHeight);
	SceneNode^ AddWaterSurfaceSceneNode(Mesh^ mesh);

	void Clear();

	CollisionResponseSceneNodeAnimator^ CreateCollisionResponseAnimator(TriangleSelector^ world, SceneNode^ node, Vector3Df^ ellipsoidRadius, Vector3Df^ gravityPerSecond, Vector3Df^ ellipsoidTranslation, float slidingValue);
	CollisionResponseSceneNodeAnimator^ CreateCollisionResponseAnimator(TriangleSelector^ world, SceneNode^ node, Vector3Df^ ellipsoidRadius, Vector3Df^ gravityPerSecond, Vector3Df^ ellipsoidTranslation);
	CollisionResponseSceneNodeAnimator^ CreateCollisionResponseAnimator(TriangleSelector^ world, SceneNode^ node, Vector3Df^ ellipsoidRadius, Vector3Df^ gravityPerSecond);
	CollisionResponseSceneNodeAnimator^ CreateCollisionResponseAnimator(TriangleSelector^ world, SceneNode^ node, Vector3Df^ ellipsoidRadius);
	CollisionResponseSceneNodeAnimator^ CreateCollisionResponseAnimator(TriangleSelector^ world, SceneNode^ node);

	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction, float startPosition, float radiusEllipsoid);
	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction, float startPosition);
	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction);
	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed);
	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center, float radius);
	SceneNodeAnimator^ CreateFlyCircleAnimator(Vector3Df^ center);
	SceneNodeAnimator^ CreateFlyCircleAnimator();

	SceneNodeAnimator^ CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay, bool loop, bool pingpong);
	SceneNodeAnimator^ CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay, bool loop);
	SceneNodeAnimator^ CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay);

	TriangleSelector^ CreateOctreeTriangleSelector(Mesh^ mesh, SceneNode^ node, int minimalPolysPerNode);
	TriangleSelector^ CreateOctreeTriangleSelector(Mesh^ mesh, SceneNode^ node);

	SceneNodeAnimator^ CreateRotationAnimator(Vector3Df^ rotationSpeed);

	SceneNodeAnimator^ CreateTextureAnimator(List<Video::Texture^>^ textures, float timePerFrame, bool loop);
	SceneNodeAnimator^ CreateTextureAnimator(List<Video::Texture^>^ textures, float timePerFrame);

	TriangleSelector^ CreateTriangleSelector(AnimatedMeshSceneNode^ node);
	TriangleSelector^ CreateTriangleSelector(Mesh^ mesh, SceneNode^ node);

	void DrawAll();

	AnimatedMesh^ GetMesh(String^ filename);

	SceneNode^ GetSceneNodeFromID(int id, SceneNode^ start);
	SceneNode^ GetSceneNodeFromID(int id);
	SceneNode^ GetSceneNodeFromName(String^ name, SceneNode^ start);
	SceneNode^ GetSceneNodeFromName(String^ name);
	SceneNode^ GetSceneNodeFromType(SceneNodeType type, SceneNode^ start);
	SceneNode^ GetSceneNodeFromType(SceneNodeType type);

	String^ GetAnimatorTypeName(SceneNodeAnimatorType type);
	String^ GetSceneNodeTypeName(SceneNodeType type);

	unsigned int RegisterNodeForRendering(SceneNode^ node, SceneNodeRenderPass pass);
	unsigned int RegisterNodeForRendering(SceneNode^ node);

	bool SaveScene(String^ filename); // 2nd argument ISceneUserDataSerializer* currently not supported
	bool LoadScene(String^ filename); // *same here*

	property CameraSceneNode^ ActiveCamera { CameraSceneNode^ get(); void set(CameraSceneNode^ value); }
	property SceneNode^ RootSceneNode { SceneNode^ get(); }
	property IO::FileSystem^ FileSystem { IO::FileSystem^ get(); }
	property GUI::GUIEnvironment^ GUIEnvironment { GUI::GUIEnvironment^ get(); }
	property Scene::MeshManipulator^ MeshManipulator { Scene::MeshManipulator^ get(); }
	property Scene::SceneCollisionManager^ SceneCollisionManager { Scene::SceneCollisionManager^ get(); }
	property Scene::SceneNodeRenderPass SceneNodeRenderPass { Scene::SceneNodeRenderPass get(); }
	property Video::Coloru^ ShadowColor { Video::Coloru^ get(); void set(Video::Coloru^ value); }
	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }

internal:

	static SceneManager^ Wrap(scene::ISceneManager* ref);
	SceneManager(scene::ISceneManager* ref);

	scene::ISceneManager* m_SceneManager;
};

} // end namespace Scene
} // end namespace IrrlichtLime