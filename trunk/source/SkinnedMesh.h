#pragma once

#include "stdafx.h"
#include "AnimatedMesh.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Scene {

public ref class SkinnedMesh : AnimatedMesh
{
public:

	void AnimateMesh(float frame, float blend);
	void ConvertMeshToTangents();
	void FinalizeMeshPopulation();

	String^ GetJointName(int index);
	int GetJointIndex(String^ name);

	bool SetHardwareSkinning(bool turnOn);
	void SetInterpolationMode(InterpolationMode mode);

	void SkinMesh();

	void UpdateNormalsWhenAnimating(bool turnOn);

	bool UseAnimationFrom(SkinnedMesh^ mesh);

	property int JointCount { int get(); }
	property bool Static { bool get(); }

internal:

	static SkinnedMesh^ Wrap(scene::ISkinnedMesh* ref);
	SkinnedMesh(scene::ISkinnedMesh* ref);

	scene::ISkinnedMesh* m_SkinnedMesh;
};

} // end namespace Scene
} // end namespace IrrlichtLime