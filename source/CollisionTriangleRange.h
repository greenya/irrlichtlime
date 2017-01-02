#pragma once

#include "stdafx.h"
#include "MeshBuffer.h"
#include "TriangleSelector.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

[StructLayoutAttribute(LayoutKind::Sequential)]
public value class CollisionTriangleRange
{
public:

	property unsigned int RangeStart
	{
		unsigned int get() { return rangeStart; }
	}

	property unsigned int RangeSize
	{
		unsigned int get() { return rangeSize; }
	}

	property TriangleSelector^ Selector
	{
		TriangleSelector^ get() { return TriangleSelector::Wrap(selector); }
	}

	property SceneNode^ SceneNode
	{
		Scene::SceneNode^ get() { return Scene::SceneNode::Wrap(sceneNode); }
	}

	//is const in native Irrlicht...
	property MeshBuffer^ MeshBuffer
	{
		Scene::MeshBuffer^ get() { return Scene::MeshBuffer::Wrap(const_cast<scene::IMeshBuffer*>(meshBuffer)); }
	}

	property unsigned int MaterialIndex
	{
		unsigned int get() { return materialIndex; }
	}

	bool IsIndexInRange(unsigned int triangleIndex)
	{
		return triangleIndex >= rangeStart && triangleIndex < rangeStart+rangeSize;
	}

internal:

	CollisionTriangleRange(const scene::SCollisionTriangleRange& value)
#ifndef FAST_FROM_NATIVE
		: rangeStart(value.RangeStart), rangeSize(value.RangeSize), selector(value.Selector), sceneNode(value.SceneNode), meshBuffer(value.MeshBuffer), materialIndex(value.materialIndex)
#endif
	{
#ifdef FAST_FROM_NATIVE
		*this = (CollisionTriangleRange&)value;
#endif
	}

	operator scene::SCollisionTriangleRange()
	{
#ifdef FAST_TO_NATIVE
		return (scene::SCollisionTriangleRange&)*this;
#else
		scene::SCollisionTriangleRange ret;
		ret.RangeStart =	rangeStart;
		ret.RangeSize =		rangeSize;
		ret.Selector =		selector;
		ret.SceneNode =		sceneNode;
		ret.MeshBuffer =	meshBuffer;
		ret.MaterialIndex =	materialIndex;
		return ret;
#endif		
	}

	scene::SCollisionTriangleRange ToNative()
	{
		return (scene::SCollisionTriangleRange)*this;
	}

	irr::u32 rangeStart;
	irr::u32 rangeSize;
	ITriangleSelector* selector;
	ISceneNode* sceneNode;
	const IMeshBuffer* meshBuffer;
	irr::u32 materialIndex;
};

} // end namespace Scene
} // end namespace IrrlichtLime