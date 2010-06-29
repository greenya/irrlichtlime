#pragma once

#include "stdafx.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

ref class DynamicMeshBuffer;
ref class Mesh;
ref class MeshBuffer;

public ref class TerrainSceneNode : SceneNode
{
public:

	AABBox3Df^ GetPatchBoundingBox(int patchX, int patchZ);
	//virtual const core::aabbox3d<f32>& getBoundingBox() const =0 // TODO: check in 12.TerrainRendering example if SceneNode.BoundingBox returns the same, if yes - remove comment, otherwise reimplement it here as prop-get and make SceneNode' one virtual.
	List<int>^ GetCurrentLODOfPatches();
	float GetHeight(float x, float z);
	List<int>^ GetIndicesForPatch(int patchX, int patchZ, int lodLevel);
	List<int>^ GetIndicesForPatch(int patchX, int patchZ);
	DynamicMeshBuffer^ GetMeshBufferForLOD(int lodLevel);
	DynamicMeshBuffer^ GetMeshBufferForLOD();

	//bool loadHeightMap(io::IReadFile *file, video::SColor vertexColor=video::SColor(255, 255, 255, 255), s32 smoothFactor=0);
	//bool loadHeightMapRAW(io::IReadFile *file, s32 bitsPerPixel=16, bool signedData=false, bool floatVals=false, s32 width=0, video::SColor vertexColor=video::SColor(255, 255, 255, 255), s32 smoothFactor=0);

	bool OverrideLODDistance(int lodLevel, double newDistance);
	void ScaleTexture(float scale, float scale2);
	void ScaleTexture(float scale);
	void SetCameraMovementDelta(float delta);
	void SetCameraRotationDelta(float delta);
	void SetDynamicSelectorUpdate(bool flag);
	void SetLODOfPatch(int patchX, int patchZ, int lodLevel);

	property int IndexCount { int get(); }
	property Scene::Mesh^ Mesh { Scene::Mesh^ get(); }
	property MeshBuffer^ RenderBuffer { MeshBuffer^ get(); }
	property Vector3Df^ TerrainCenter { Vector3Df^ get(); }

internal:

	static TerrainSceneNode^ Wrap(scene::ITerrainSceneNode* ref);
	TerrainSceneNode(scene::ITerrainSceneNode* ref);

	scene::ITerrainSceneNode* m_TerrainSceneNode;
};

} // end namespace Scene
} // end namespace IrrlichtLime