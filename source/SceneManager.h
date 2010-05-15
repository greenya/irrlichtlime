#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Scene
{
	public ref class SceneManager
	{
	public:

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
				Core::Vector3Df^ position, Core::Vector3Df^ rotation, Core::Vector3Df^ scale,
				bool alsoAddIfMeshPointerZero)
		{
			scene::IAnimatedMeshSceneNode* m = m_SceneManager->addAnimatedMeshSceneNode(
				mesh->m_AnimatedMesh,
				parent == nullptr ? nullptr : parent->m_SceneNode,
				id,
				*((core::vector3df*)position->m_NativeObject),
				*((core::vector3df*)rotation->m_NativeObject),
				*((core::vector3df*)scale->m_NativeObject),
				alsoAddIfMeshPointerZero);

			return m == nullptr ? nullptr : gcnew AnimatedMeshSceneNode(m);
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
				Core::Vector3Df^ position, Core::Vector3Df^ rotation, Core::Vector3Df^ scale)
		{
			return AddAnimatedMeshSceneNode(mesh, parent, id, position, rotation, scale, false);
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
				Core::Vector3Df^ position, Core::Vector3Df^ rotation)
		{
			return AddAnimatedMeshSceneNode(mesh, parent, id, position, rotation, gcnew Core::Vector3Df(1.0f));
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id,
				Core::Vector3Df^ position)
		{
			return AddAnimatedMeshSceneNode(mesh, parent, id, position, gcnew Core::Vector3Df());
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent, Int32 id)
		{
			return AddAnimatedMeshSceneNode(mesh, parent, id, gcnew Core::Vector3Df());
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh, SceneNode^ parent)
		{
			return AddAnimatedMeshSceneNode(mesh, parent, -1);
		}

		AnimatedMeshSceneNode^ AddAnimatedMeshSceneNode(AnimatedMesh^ mesh)
		{
			return AddAnimatedMeshSceneNode(mesh, nullptr);
		}

		AnimatedMesh^ GetMesh(String^ filename)
		{
			scene::IAnimatedMesh* m = m_SceneManager->getMesh(Lime::StringToStringC(filename));
			return m == nullptr ? nullptr : gcnew AnimatedMesh(m);
		}

		property SceneNode^ RootSceneNode
		{
			SceneNode^ get()
			{
				scene::ISceneNode* n = m_SceneManager->getRootSceneNode();
				return n == nullptr ? nullptr : gcnew SceneNode(n);
			}
		}

	internal:

		scene::ISceneManager* m_SceneManager;

		SceneManager(scene::ISceneManager* sceneManager)
		{
			m_SceneManager = sceneManager;
		}
	};
}
}