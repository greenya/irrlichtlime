#include "stdafx.h"
#include "AnimatedMesh.h"
#include "AnimatedMeshSceneNode.h"
#include "CameraSceneNode.h"
#include "FileSystem.h"
#include "GUIEnvironment.h"
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

SceneManager::SceneManager(scene::ISceneManager* sceneManager)
	: ReferenceCounted(sceneManager)
{
	LIME_ASSERT(sceneManager != nullptr);
	m_SceneManager = sceneManager;
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
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

	return LIME_SAFEWRAP(AnimatedMeshSceneNode, n);
}

AnimatedMeshSceneNode^ SceneManager::AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, int id)
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
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

	return LIME_SAFEWRAP(CameraSceneNode, n);
}

CameraSceneNode^ SceneManager::AddCameraSceneNodeFPS(SceneNode^ parent, float rotateSpeed, float moveSpeed, int id)
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

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode, bool alsoAddIfMeshPointerZero)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode,
		alsoAddIfMeshPointerZero);

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id, int minimalPolysPerNode)
{
	scene::IMeshSceneNode* n = m_SceneManager->addOctreeSceneNode(
		LIME_SAFEREF(mesh, m_Mesh),
		LIME_SAFEREF(parent, m_SceneNode),
		id,
		minimalPolysPerNode);

	return LIME_SAFEWRAP(MeshSceneNode, n);
}

MeshSceneNode^ SceneManager::AddOctreeSceneNode(Mesh^ mesh, SceneNode^ parent, int id)
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

void SceneManager::Clear()
{
	m_SceneManager->clear();
}

SceneNodeAnimator^ SceneManager::CreateRotationAnimator(Vector3Df^ rotationSpeed)
{
	LIME_ASSERT(rotationSpeed != nullptr);
	scene::ISceneNodeAnimator* a = m_SceneManager->createRotationAnimator(*rotationSpeed->m_NativeValue);
	return LIME_SAFEWRAP(SceneNodeAnimator, a);
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

SceneNode^ SceneManager::GetSceneNodeFromID(int id, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromId(id, LIME_SAFEREF(start, m_SceneNode));
	return LIME_SAFEWRAP(SceneNode, n);
}

SceneNode^ SceneManager::GetSceneNodeFromID(int id)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromId(id);
	return LIME_SAFEWRAP(SceneNode, n);
}

SceneNode^ SceneManager::GetSceneNodeFromName(String^ name, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromName(Lime::StringToStringC(name).c_str(), LIME_SAFEREF(start, m_SceneNode));
	return LIME_SAFEWRAP(SceneNode, n);
}

SceneNode^ SceneManager::GetSceneNodeFromName(String^ name)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromName(Lime::StringToStringC(name).c_str());
	return LIME_SAFEWRAP(SceneNode, n);
}

SceneNode^ SceneManager::GetSceneNodeFromType(SceneNodeType type, SceneNode^ start)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromType((scene::ESCENE_NODE_TYPE)type, LIME_SAFEREF(start, m_SceneNode));
	return LIME_SAFEWRAP(SceneNode, n);
}

SceneNode^ SceneManager::GetSceneNodeFromType(SceneNodeType type)
{
	scene::ISceneNode* n = m_SceneManager->getSceneNodeFromType((scene::ESCENE_NODE_TYPE)type);
	return LIME_SAFEWRAP(SceneNode, n);
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
	return LIME_SAFEWRAP(CameraSceneNode, n);
}

void SceneManager::ActiveCamera::set(CameraSceneNode^ value)
{
	m_SceneManager->setActiveCamera(LIME_SAFEREF(value, m_CameraSceneNode));
}

SceneNode^ SceneManager::RootSceneNode::get()
{
	scene::ISceneNode* n = m_SceneManager->getRootSceneNode();
	return LIME_SAFEWRAP(SceneNode, n);
}

IO::FileSystem^ SceneManager::FileSystem::get()
{
	return LIME_SAFEWRAP(IO::FileSystem, m_SceneManager->getFileSystem());
}

GUI::GUIEnvironment^ SceneManager::GUIEnvironment::get()
{
	return LIME_SAFEWRAP(GUI::GUIEnvironment, m_SceneManager->getGUIEnvironment());
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
	return LIME_SAFEWRAP(Video::VideoDriver, m_SceneManager->getVideoDriver());
}

} // end namespace Scene
} // end namespace IrrlichtLime