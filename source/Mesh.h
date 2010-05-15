#pragma once

#include "stdafx.h"
using namespace irr;
using namespace System;

namespace IrrlichtLime
{
namespace Scene
{
	public ref class Mesh
	{
	public:

	internal:

		scene::IMesh* m_Mesh;

		Mesh(scene::IMesh* mesh)
		{
			m_Mesh = mesh;
		}
	};
}
}