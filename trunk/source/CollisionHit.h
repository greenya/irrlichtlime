#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ref class SceneNode;
ref class TriangleSelector;
ref class MeshBuffer;

public ref class CollisionHit : Lime::NativeValue<scene::SCollisionHit>
{
public:

	CollisionHit();
	CollisionHit(CollisionHit^ copy);

	property Vector3Df Intersection
	{
		Vector3Df get();
		void set(Vector3Df value);
	}

	property unsigned int MaterialIndex
	{
		unsigned int get();
		void set(unsigned int value);
	}	

	//is const in native Irrlicht...
	property MeshBuffer^ MeshBuffer
	{
		Scene::MeshBuffer^ get();
		void set(Scene::MeshBuffer^ value);
	}

	property SceneNode^ Node
	{
		SceneNode^ get();
		void set(SceneNode^ value);
	}

	property Triangle3Df Triangle
	{
		Triangle3Df get();
		void set(Triangle3Df value);
	}

	property TriangleSelector^ TriangleSelector
	{
		Scene::TriangleSelector^ get();
		void set(Scene::TriangleSelector^ value);
	}

internal:

	CollisionHit(scene::SCollisionHit& other)
		: Lime::NativeValue<scene::SCollisionHit>(true)
	{
		m_NativeValue = new scene::SCollisionHit(other);
	}

	/*CollisionHit(scene::SCollisionHit* ref)
		: Lime::NativeValue<scene::SCollisionHit>(false)
	{
		LIME_ASSERT(ref != nullptr);
		m_NativeValue = ref;
	}*/
};

} // end namespace Scene
} // end namespace IrrlichtLime