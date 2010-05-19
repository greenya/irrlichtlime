#pragma once

#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"
#include "CameraSceneNode.h"
#include "Mesh.h"
#include "MeshSceneNode.h"
#include "SceneManager.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

SceneManager::SceneManager(scene::ISceneManager* sceneManager)
{
	LIME_ASSERT(sceneManager != nullptr);
	m_SceneManager = sceneManager;
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		*position->m_NativeValue);

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh),
		LIME_SAFEREF(parent, m_SceneNode));

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		LIME_SAFEREF(mesh, m_AnimatedMesh));

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, Int32 id, bool makeActive)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id,
		makeActive);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, Int32 id)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat)
{
	LIME_ASSERT(position != nullptr);
	LIME_ASSERT(lookat != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue,
		*lookat->m_NativeValue);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position)
{
	LIME_ASSERT(position != nullptr);

	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode),
		*position->m_NativeValue);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		LIME_SAFEREF(parent, m_SceneNode));

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode()
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode();
	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse, bool makeActive)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed, bool invertMouse)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id, KeyMap^ keyMap, bool noVerticalMovement, float jumpSpeed)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id, KeyMap^ keyMap, bool noVerticalMovement)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id, KeyMap^ keyMap)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, Int32 id)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed,
		id);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed,
		moveSpeed);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode),
		rotateSpeed);

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS(
		LIME_SAFEREF(parent, m_SceneNode));

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS()
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNodeFPS();
	return LIME_SAFEWRAP(CameraSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, Int32 id, Int32 minimalPolysPerNode, bool alsoAddIfMeshPointerZero)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode,
		alsoAddIfMeshPointerZero);

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, Int32 id, Int32 minimalPolysPerNode)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode);

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, Int32 id)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id);

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode));

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh));

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

void SceneManager::DrawAll()
{
	m_SceneManager->drawAll();
}

AnimatedMesh^ SceneManager::GetMesh(String^ filename)
{
	scene::IAnimatedMesh* m = m_SceneManager->getMesh(Lime::StringToPath(filename));
	return LIME_SAFEWRAP(AnimatedMesh, m);
}

SceneNode^ SceneManager::RootSceneNode::get()
{
	scene::ISceneNode* n = m_SceneManager->getRootSceneNode();
	return LIME_SAFEWRAP(SceneNode, n);
}

} // end namespace Scene
} // end namespace IrrlichtLime