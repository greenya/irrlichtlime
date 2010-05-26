#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO { ref class FileSystem; }
namespace GUI { ref class GUIEnvironment; }
namespace Video { ref class VideoDriver; }
namespace Scene {

ref class AnimatedMesh;
ref class AnimatedMeshSceneNode;
ref class CameraSceneNode;
ref class Mesh;
ref class MeshSceneNode;
ref class SceneNode;
ref class SceneNodeAnimator;

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

	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode, bool alsoAddIfMeshPointerZero);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent);
	MeshSceneNode^ AddOctreeSceneNode(Mesh^ mesh);

	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id, Vector3Df^ position);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent);
	MeshSceneNode^ AddSphereSceneNode(float radius, int polyCount);
	MeshSceneNode^ AddSphereSceneNode(float radius);
	MeshSceneNode^ AddSphereSceneNode();

	void Clear();

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

	SceneNodeAnimator^ CreateRotationAnimator(Vector3Df^ rotationSpeed);

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
	property Scene::SceneNodeRenderPass SceneNodeRenderPass { Scene::SceneNodeRenderPass get(); }
	property Video::Coloru^ ShadowColor { Video::Coloru^ get(); void set(Video::Coloru^ value); }
	property Video::VideoDriver^ VideoDriver { Video::VideoDriver^ get(); }

internal:

	SceneManager(scene::ISceneManager* sceneManager);

	scene::ISceneManager* m_SceneManager;
};

} // end namespace Scene
} // end namespace IrrlichtLime