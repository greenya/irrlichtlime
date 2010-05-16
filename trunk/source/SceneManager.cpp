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
		*((core::vector3df*)position->m_NativeObject),
		*((core::vector3df*)rotation->m_NativeObject),
		*((core::vector3df*)scale->m_NativeObject),
		alsoAddIfMeshPointerZero);

	return n == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale)
{
	return AddAnimatedMeshSceneNode(mesh, parent, id, position, rotation, scale, false);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position, Vector3Df^ rotation)
{
	return AddAnimatedMeshSceneNode(mesh, parent, id, position, rotation, gcnew Vector3Df(1.0f));
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
	Vector3Df^ position)
{
	return AddAnimatedMeshSceneNode(mesh, parent, id, position, gcnew Vector3Df());
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id)
{
	return AddAnimatedMeshSceneNode(mesh, parent, id, gcnew Vector3Df());
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent)
{
	return AddAnimatedMeshSceneNode(mesh, parent, -1);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh)
{
	return AddAnimatedMeshSceneNode(mesh, nullptr);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat,
	Int32 id, bool makeActive)
{
	scene::ICameraSceneNode* n = m_SceneManager->addCameraSceneNode(
		parent == nullptr ? nullptr : parent->m_SceneNode,
		*((core::vector3df*)position->m_NativeObject),
		*((core::vector3df*)lookat->m_NativeObject),
		id,
		makeActive);

	return n == nullptr ? nullptr : gcnew CameraSceneNode(n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat,
	Int32 id)
{
	return AddCameraSceneNode(parent, position, lookat, id, true);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position, Vector3Df^ lookat)
{
	return AddCameraSceneNode(parent, position, lookat, -1);
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent, Vector3Df^ position)
{
	return AddCameraSceneNode(parent, position, gcnew Vector3Df(0, 0, 100));
}

CameraSceneNode^ SceneManager::AddCameraSceneNode(SceneNode^ parent)
{
	return AddCameraSceneNode(parent, gcnew Vector3Df(0, 0, 0));
}

CameraSceneNode^ SceneManager::AddCameraSceneNode()
{
	return AddCameraSceneNode(nullptr);
}

AnimatedMesh^ SceneManager::GetMesh(String^ filename)
{
	scene::IAnimatedMesh* m = m_SceneManager->getMesh(Lime::StringToStringC(filename));
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