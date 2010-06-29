#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

ref class TriangleSelector;

public ref class MetaTriangleSelector : ReferenceCounted
{
public:

	void AddTriangleSelector(TriangleSelector^ selector);
	void RemoveAllTriangleSelectors();
	bool RemoveTriangleSelector(TriangleSelector^ selector);

internal:

	static MetaTriangleSelector^ Wrap(scene::IMetaTriangleSelector* ref);
	MetaTriangleSelector(scene::IMetaTriangleSelector* ref);

	scene::IMetaTriangleSelector* m_MetaTriangleSelector;
};

} // end namespace Scene
} // end namespace IrrlichtLime