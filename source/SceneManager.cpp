#pragma once

#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"
#include "CameraSceneNode.h"
#include "SceneManager.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale, bool alsoAddIfMeshPointerZero)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode,
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue,
		alsoAddIfMeshPointerZero);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode,
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue,
		*scale->m_NativeValue);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position, Vector3Df^ rotation)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode,
		id,
		*position->m_NativeValue,
		*rotation->m_NativeValue);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode,
		id,
		*position->m_NativeValue);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode,
		id);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh,
		parent == nullptr ? nullptr : parent->m_SceneNode);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh)
{
	scene::IAnimatedMeshSceneNode* n = m_SceneManager->addAnimatedMeshSceneNode(
		mesh == nullptr ? nullptr : mesh->m_AnimatedMesh);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, Int32 id, bool makeActive)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode,
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id,
		makeActive);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat, Int32 id)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode,
		*position->m_NativeValue,
		*lookat->m_NativeValue,
		id);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode,
		*position->m_NativeValue,
		*lookat->m_NativeValue);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode,
		*position->m_NativeValue);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode()
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode();
	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

void SceneManager::DrawAll()
{
	m_SceneManager->drawAll();
}

AnimatedMesh^ SceneManager::GetMesh(String^ filename)
{
	scene::IAnimatedMesh* m = m_SceneManager->getMesh(Lime::StringToPath(filename));
	return m == nullptr ? nullptr : gcnew AnimatedMesh(m);
}

SceneNode^ SceneManager::RootSceneNode::get()
{
	scene::ISceneNode* n = m_SceneManager->getRootSceneNode();
	return n == nullptr ? nullptr : gcnew SceneNode(n);
}

SceneManager::SceneManager(scene::ISceneManager* sceneManager)
{
	LIME_ASSERT(sceneManager != nullptr);
	m_SceneManager = sceneManager;
}

} // end namespace Scene
} // end namespace IrrlichtLime