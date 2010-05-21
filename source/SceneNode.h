#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video { ref class Texture; }
namespace Scene {

ref class SceneManager;

public ref class SceneNode
{
public:

	void AddChild(SceneNode^ child);
	void Drop();
	void Remove();
	void RemoveAll();
	bool RemoveChild(SceneNode^ child);
	void Render();
	void SetMaterialFlag(Video::MaterialFlag flag, bool value);
	void SetMaterialTexture(unsigned int textureLayer, Video::Texture^ texture);
	void UpdateAbsolutePosition();

	property Vector3Df^ AbsolutePosition { Vector3Df^ get(); }
	property unsigned int AutomaticCulling { unsigned int get(); void set(unsigned int value); }
	property bool DebugObject { bool get(); void set(bool value); }
	property int ID { int get(); void set(int value); }
	property String^ Name { String^ get(); void set(String^ value); }
	property SceneNode^ Parent { SceneNode^ get(); void set(SceneNode^ value); }
	property Vector3Df^ Position { Vector3Df^ get(); void set(Vector3Df^ value); }
	property Vector3Df^ Rotation { Vector3Df^ get(); void set(Vector3Df^ value); }
	property Vector3Df^ Scale { Vector3Df^ get(); void set(Vector3Df^ value); }
	property Scene::SceneManager^ SceneManager { Scene::SceneManager^ get(); }
	property bool TrulyVisible { bool get(); }
	property SceneNodeType Type { SceneNodeType get(); }
	property bool Visible { bool get(); void set(bool value); }

	virtual String^ ToString() override;

	delegate void RenderEventHandler();

protected:

	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);

	event RenderEventHandler^ OnRender;

internal:

	SceneNode(scene::ISceneNode* sceneNode);

	scene::ISceneNode* m_SceneNode;
	bool m_isInherited;
};

} // end namespace Scene
} // end namespace IrrlichtLime