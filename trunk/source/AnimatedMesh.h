#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Scene
{
	public ref class AnimatedMesh : Mesh
	{
	public:

	internal:

		scene::IAnimatedMesh* m_AnimatedMesh;

		AnimatedMesh(scene::IAnimatedMesh* animatedMesh)
			: Mesh(animatedMesh)
		{
			m_AnimatedMesh = animatedMesh;
		}
	};
}
}