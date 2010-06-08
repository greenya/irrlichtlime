#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ref class SceneNode;

public ref class TriangleSelector : ReferenceCounted
{
public:

	SceneNode^ GetSceneNodeForTriangle(unsigned int triangleIndex);

	List<Triangle3Df^>^ GetTriangles(AABBox3Df^ box, unsigned int maxTriangleCount, Matrix4f^ transform);
	List<Triangle3Df^>^ GetTriangles(AABBox3Df^ box, unsigned int maxTriangleCount);
	List<Triangle3Df^>^ GetTriangles(Line3Df^ line, unsigned int maxTriangleCount, Matrix4f^ transform);
	List<Triangle3Df^>^ GetTriangles(Line3Df^ line, unsigned int maxTriangleCount);
	List<Triangle3Df^>^ GetTriangles(unsigned int maxTriangleCount, Matrix4f^ transform);
	List<Triangle3Df^>^ GetTriangles(unsigned int maxTriangleCount);

	property unsigned int TriangleCount { unsigned int get(); }

internal:

	static TriangleSelector^ Wrap(scene::ITriangleSelector* ref);
	TriangleSelector(scene::ITriangleSelector* ref);

	scene::ITriangleSelector* m_TriangleSelector;
};

} // end namespace Scene
} // end namespace IrrlichtLime