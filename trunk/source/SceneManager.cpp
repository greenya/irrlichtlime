#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"
#include "BillboardSceneNode.h"
#include "CameraSceneNode.h"
#include "FileSystem.h"
#include "GUIEnvironment.h"
#include "LightSceneNode.h"
#include "Mesh.h"
#include "MeshSceneNode.h"
#include "ReferenceCounted.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "SceneNodeAnimator.h"
#include "VideoDriver.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

SceneManager^ SceneManager::Wrap(scene::ISceneManager* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew SceneManager(ref);
}

SceneManager::SceneManager(scene::ISceneManager* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SceneManager = ref;
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale, bool alsoAddIfMeshPointerZero)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);
	LIME_ASSERT(scale != nullptr);

	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue,
		alsoAddIfMeshPointerZero);

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);
	LIME_ASSERT(scale != nullptr);

	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue);

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id,
	Vector3Df^ position, Vector3Df^ rotation)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);

	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue);

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id,
	Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue);

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode));

	return AnimatedMeshSceneNode::Wrap(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh));

	return AnimatedMeshSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id,
	Video::Coloru^ colorTop, Video::Coloru^ colorBottom)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(colorTop != nullptr);
	LIME_ASSERT(colorBottom != nullptr);

	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*size->m_NativeValue,
		*position->m_NativeValue,
		id,
		*colorTop->m_NativeValue,
		*colorBottom->m_NativeValue);

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id,
	Video::Coloru^ colorTop)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(colorTop != nullptr);

	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*size->m_NativeValue,
		*position->m_NativeValue,
		id,
		*colorTop->m_NativeValue);

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position, int id)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(position != nullptr);

	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*size->m_NativeValue,
		*position->m_NativeValue,
		id);

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size, Vector3Df^ position)
{
	LIME_ASSERT(size != nullptr);
	LIME_ASSERT(position != nullptr);

	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*size->m_NativeValue,
		*position->m_NativeValue);

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent, Dimension2Df^ size)
{
	LIME_ASSERT(size != nullptr);

	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*size->m_NativeValue);

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode(SceneNode^ parent)
{
	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode(
		LIME_SAFEREF(parent, m_SceneNode));

	return BillboardSceneNode::Wrap(n);
}

BillboardSceneNode^ SceneManager::AddBillboardSceneNode()
{
	scene::IBillboardSceneNode* n = m_SceneManager->addBillboardSceneNode();
	return BillboardSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, int id, bool makeActive)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id,
		makeActive);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, int id)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode));

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode()
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode();
	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse, bool makeActive)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;
	
	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id,
		keyMapArray, keyMapSize,
		noVerticalMovement,
		jumpSpeed,
		invertMouse,
		makeActive);

	if (keyMapArray != 0)
		delete keyMapArray;

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;
	
	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id,
		keyMapArray, keyMapSize,
		noVerticalMovement,
		jumpSpeed,
		invertMouse);

	if (keyMapArray != 0)
		delete keyMapArray;

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;
	
	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id,
		keyMapArray, keyMapSize,
		noVerticalMovement,
		jumpSpeed);

	if (keyMapArray != 0)
		delete keyMapArray;

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap, bool noVerticalMovement)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;
	
	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id,
		keyMapArray, keyMapSize,
		noVerticalMovement);

	if (keyMapArray != 0)
		delete keyMapArray;

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id, KeyMap^ keyMap)
{
	SKeyMap* keyMapArray = 0;
	int keyMapSize = 0;
	
	if (keyMap != nullptr)
		keyMapSize = keyMap->GetSKeyMapArray(keyMapArray); // allocates keyMapArray

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id,
		keyMapArray, keyMapSize);

	if (keyMapArray != 0)
		delete keyMapArray;

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed);

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode));

	return CameraSceneNode::Wrap(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS()
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS();
	return CameraSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);
	LIME_ASSERT(scale != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(
		size,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position, Vector3Df^ rotation)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(
		size,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size, SceneNode^ parent, int id, Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(
		size,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size, SceneNode^ parent, int id)
{
	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(
		size,
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size, SceneNode^ parent)
{
	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(
		size,
		LIME_SAFEREF(parent, m_SceneNode));

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode(float size)
{
	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode(size);
	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddCubeSceneNode()
{
	scene::IMeshSceneNode* n = m_SceneManager->addCubeSceneNode();
	return MeshSceneNode::Wrap(n);
}

LightSceneNode^ SceneManager::AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color, float radius, int id)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(color != nullptr);

	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*color->m_NativeValue,
		radius,
		id);

	return LightSceneNode::Wrap(l);
}

LightSceneNode^ SceneManager::AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color, float radius)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(color != nullptr);

	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*color->m_NativeValue,
		radius);

	return LightSceneNode::Wrap(l);
}

LightSceneNode^ SceneManager::AddLightSceneNode(SceneNode^ parent, Vector3Df^ position, Video::Colorf^ color)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(color != nullptr);

	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*color->m_NativeValue);

	return LightSceneNode::Wrap(l);
}

LightSceneNode^ SceneManager::AddLightSceneNode(SceneNode^ parent, Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue);

	return LightSceneNode::Wrap(l);
}

LightSceneNode^ SceneManager::AddLightSceneNode(SceneNode^ parent)
{
	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode(
		LIME_SAFEREF(parent, m_SceneNode));

	return LightSceneNode::Wrap(l);
}

LightSceneNode^ SceneManager::AddLightSceneNode()
{
	scene::ILightSceneNode* l = m_SceneManager->addLightSceneNode();
	return LightSceneNode::Wrap(l);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode, bool alsoAddIfMeshPointerZero)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode,
		alsoAddIfMeshPointerZero);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode));

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh));

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
{
	LIME_ASSERT(polyCount < 256);
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);
	LIME_ASSERT(scale != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(
		radius,
		polyCount,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id,
	Vector3Df^ position, Vector3Df^ rotation)
{
	LIME_ASSERT(polyCount < 256);
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(rotation != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(
		radius,
		polyCount,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id,
	Vector3Df^ position)
{
	LIME_ASSERT(polyCount < 256);
	LIME_ASSERT(position != nullptr);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(
		radius,
		polyCount,
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent, int id)
{
	LIME_ASSERT(polyCount < 256);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(
		radius,
		polyCount,
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount, SceneNode^ parent)
{
	LIME_ASSERT(polyCount < 256);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(
		radius,
		polyCount,
		LIME_SAFEREF(parent, m_SceneNode));

	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius, int polyCount)
{
	LIME_ASSERT(polyCount < 256);

	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(radius, polyCount);
	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode(float radius)
{
	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode(radius);
	return MeshSceneNode::Wrap(n);
}

MeshSceneNode^ SceneManager::AddSphereSceneNode()
{
	scene::IMeshSceneNode* n = m_SceneManager->addSphereSceneNode();
	return MeshSceneNode::Wrap(n);
}

void SceneManager::Clear()
{
	m_SceneManager->clear();
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction, float startPosition, float radiusEllipsoid)
{
	LIME_ASSERT(center != nullptr);
	LIME_ASSERT(direction != nullptr);
	
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(
		*center->m_NativeValue,
		radius,
		speed,
		*direction->m_NativeValue,
		startPosition,
		radiusEllipsoid);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction, float startPosition)
{
	LIME_ASSERT(center != nullptr);
	LIME_ASSERT(direction != nullptr);
	
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(
		*center->m_NativeValue,
		radius,
		speed,
		*direction->m_NativeValue,
		startPosition);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed, Vector3Df^ direction)
{
	LIME_ASSERT(center != nullptr);
	LIME_ASSERT(direction != nullptr);
	
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(
		*center->m_NativeValue,
		radius,
		speed,
		*direction->m_NativeValue);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center, float radius, float speed)
{
	LIME_ASSERT(center != nullptr);
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(*center->m_NativeValue, radius, speed);
	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center, float radius)
{
	LIME_ASSERT(center != nullptr);
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(*center->m_NativeValue, radius);
	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator(Vector3Df^ center)
{
	LIME_ASSERT(center != nullptr);
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator(*center->m_NativeValue);
	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyCircleAnimator()
{
	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyCircleAnimator();
	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay, bool loop, bool pingpong)
{
	LIME_ASSERT(startPoint != nullptr);
	LIME_ASSERT(endPoint != nullptr);

	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyStraightAnimator(
		*startPoint->m_NativeValue,
		*endPoint->m_NativeValue,
		timeForWay,
		loop,
		pingpong);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay, bool loop)
{
	LIME_ASSERT(startPoint != nullptr);
	LIME_ASSERT(endPoint != nullptr);

	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyStraightAnimator(
		*startPoint->m_NativeValue,
		*endPoint->m_NativeValue,
		timeForWay,
		loop);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateFlyStraightAnimator(Vector3Df^ startPoint, Vector3Df^ endPoint, unsigned int timeForWay)
{
	LIME_ASSERT(startPoint != nullptr);
	LIME_ASSERT(endPoint != nullptr);

	scene::ISceneNodeAnimator* a = m_SceneManager->createFlyStraightAnimator(
		*startPoint->m_NativeValue,
		*endPoint->m_NativeValue,
		timeForWay);

	return SceneNodeAnimator::Wrap(a);
}

SceneNodeAnimator^ SceneManager::CreateRotationAnimator(Vector3Df^ rotationSpeed)
{
	LIME_ASSERT(rotationSpeed != nullptr);
	scene::ISceneNodeAnimator* a = m_SceneManager->createRotationAnimator(*rotationSpeed->m_NativeValue);
	return SceneNodeAnimator::Wrap(a);
}

void SceneManager::DrawAll()
{
	m_SceneManager->drawAll();
}

AnimatedMesh^ SceneManager::GetMesh(String^ filename)
{
	scene::IAnimatedMesh* m = m_SceneManager->getMesh(Lime::StringToPath(filename));
	return AnimatedMesh::Wrap(m);
}

SceneNode^ SceneManager::GetSceneNodeFromID(int id, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromId(id, LIME_SAFEREF(start, m_SceneNode));
	return SceneNode::Wrap(n);
}

SceneNode^ SceneManager::GetSceneNodeFromID(int id)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromId(id);
	return SceneNode::Wrap(n);
}

SceneNode^ SceneManager::GetSceneNodeFromName(String^ name, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromName(Lime::StringToStringC(name).c_str(), LIME_SAFEREF(start, m_SceneNode));
	return SceneNode::Wrap(n);
}

SceneNode^ SceneManager::GetSceneNodeFromName(String^ name)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromName(Lime::StringToStringC(name).c_str());
	return SceneNode::Wrap(n);
}

SceneNode^ SceneManager::GetSceneNodeFromType(SceneNodeType type, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromType((scene::ESCENE_NODE_TYPE)type, LIME_SAFEREF(start, m_SceneNode));
	return SceneNode::Wrap(n);
}

SceneNode^ SceneManager::GetSceneNodeFromType(SceneNodeType type)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromType((scene::ESCENE_NODE_TYPE)type);
	return SceneNode::Wrap(n);
}

String^ SceneManager::GetAnimatorTypeName(SceneNodeAnimatorType type)
{
	return gcnew String(m_SceneManager->getAnimatorTypeName((scene::ESCENE_NODE_ANIMATOR_TYPE)type));
}

String^ SceneManager::GetSceneNodeTypeName(SceneNodeType type)
{
	return gcnew String(m_SceneManager->getSceneNodeTypeName((scene::ESCENE_NODE_TYPE)type));
}

unsigned int SceneManager::RegisterNodeForRendering(SceneNode^ node, Scene::SceneNodeRenderPass pass)
{
	return m_SceneManager->registerNodeForRendering(LIME_SAFEREF(node, m_SceneNode), (E_SCENE_NODE_RENDER_PASS)pass);
}

unsigned int SceneManager::RegisterNodeForRendering(SceneNode^ node)
{
	return m_SceneManager->registerNodeForRendering(LIME_SAFEREF(node, m_SceneNode));
}

bool SceneManager::SaveScene(String^ filename)
{
	return m_SceneManager->saveScene(Lime::StringToPath(filename));
}

bool SceneManager::LoadScene(String^ filename)
{
	return m_SceneManager->loadScene(Lime::StringToPath(filename));
}

CameraSceneNode^ SceneManager::ActiveCamera::get()
{
	scene::ICameraSceneNode* n = m_SceneManager->getActiveCamera();
	return CameraSceneNode::Wrap(n);
}

void SceneManager::ActiveCamera::set(CameraSceneNode^ value)
{
	m_SceneManager->setActiveCamera(LIME_SAFEREF(value, m_CameraSceneNode));
}

SceneNode^ SceneManager::RootSceneNode::get()
{
	scene::ISceneNode* n = m_SceneManager->getRootSceneNode();
	return SceneNode::Wrap(n);
}

IO::FileSystem^ SceneManager::FileSystem::get()
{
	return IO::FileSystem::Wrap(m_SceneManager->getFileSystem());
}

GUI::GUIEnvironment^ SceneManager::GUIEnvironment::get()
{
	return GUI::GUIEnvironment::Wrap(m_SceneManager->getGUIEnvironment());
}

Scene::SceneNodeRenderPass SceneManager::SceneNodeRenderPass::get()
{
	return (Scene::SceneNodeRenderPass)m_SceneManager->getSceneNodeRenderPass();
}

Video::Coloru^ SceneManager::ShadowColor::get()
{
	return gcnew Video::Coloru(m_SceneManager->getShadowColor());
}

void SceneManager::ShadowColor::set(Video::Coloru^ value)
{
	LIME_ASSERT(value != nullptr);
	m_SceneManager->setShadowColor(*value->m_NativeValue);
}

Video::VideoDriver^ SceneManager::VideoDriver::get()
{
	return Video::VideoDriver::Wrap(m_SceneManager->getVideoDriver());
}

} // end namespace Scene
} // end namespace IrrlichtLime