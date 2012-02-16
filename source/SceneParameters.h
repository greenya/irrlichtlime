#pragma once

#include "stdafx.h"

using namespace irr;
using namespace scene;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

public ref class SceneParameters abstract sealed
{
public:

	static property String^ AllowZWriteOnTransparent { String^ get() { return gcnew String(ALLOW_ZWRITE_ON_TRANSPARENT); }}
	
	static property String^ B3D_IgnoreMipmapFlag { String^ get() { return gcnew String(B3D_LOADER_IGNORE_MIPMAP_FLAG); }}
	static property String^ B3D_TexturePath { String^ get() { return gcnew String(B3D_TEXTURE_PATH); }}
	
	static property String^ COLLADA_CreateSceneInstances { String^ get() { return gcnew String(COLLADA_CREATE_SCENE_INSTANCES); }}
	
	static property String^ CSM_TexturePath { String^ get() { return gcnew String(CSM_TEXTURE_PATH); }}
	
	static property String^ DebugNormalColor { String^ get() { return gcnew String(DEBUG_NORMAL_COLOR); }}
	static property String^ DebugNormalLength { String^ get() { return gcnew String(DEBUG_NORMAL_LENGTH); }}

	static property String^ DMF_AlphaChannelRef { String^ get() { return gcnew String(DMF_ALPHA_CHANNEL_REF); }}
	static property String^ DMF_FlipAlphaTextures { String^ get() { return gcnew String(DMF_FLIP_ALPHA_TEXTURES); }}
	static property String^ DMF_IgnoreMaterialsDir { String^ get() { return gcnew String(DMF_IGNORE_MATERIALS_DIRS); }}
	static property String^ DMF_TexturePath { String^ get() { return gcnew String(DMF_TEXTURE_PATH); }}
	
	static property String^ IRR_Editor { String^ get() { return gcnew String(IRR_SCENE_MANAGER_IS_EDITOR); }}
	
	static property String^ LMTS_TexturePath { String^ get() { return gcnew String(LMTS_TEXTURE_PATH); }}
	
	static property String^ MY3D_TexturePath { String^ get() { return gcnew String(MY3D_TEXTURE_PATH); }}
	
	static property String^ OBJ_IgnoreGroups { String^ get() { return gcnew String(OBJ_LOADER_IGNORE_GROUPS); }}
	static property String^ OBJ_IgnoreMaterialFiles { String^ get() { return gcnew String(OBJ_LOADER_IGNORE_MATERIAL_FILES); }}
	static property String^ OBJ_TexturePath { String^ get() { return gcnew String(OBJ_TEXTURE_PATH); }}
};

} // end namespace Scene
} // end namespace IrrlichtLime