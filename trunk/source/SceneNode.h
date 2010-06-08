#pragma once

#include "stdafx.h"
#include "AttributeExchangingObject.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video { ref class Material; ref class Texture; }
namespace Scene {

ref class SceneManager;
ref class SceneNodeAnimator;
class SceneNodeInheritor;
ref class TriangleSelector;

public ref class SceneNode : IO::AttributeExchangingObject
{
public:

	void AddAnimator(SceneNodeAnimator^ animator);
	void AddChild(SceneNode^ child);

	Video::Material^ GetMaterial(unsigned int num);

	void RegisterSceneNode();

	void Remove();
	void RemoveAll();
	void RemoveAnimator(SceneNodeAnimator^ animator);
	void RemoveAnimators();
	bool RemoveChild(SceneNode^ child);

	void Render();

	void SetMaterialFlag(Video::MaterialFlag flag, bool value);
	void SetMaterialTexture(unsigned int textureLayer, Video::Texture^ texture);
	void SetMaterialType(Video::MaterialType newType);

	void UpdateAbsolutePosition();

	property Vector3Df^ AbsolutePosition { Vector3Df^ get(); }
	property Matrix4f^ AbsoluteTransformation { Matrix4f^ get(); protected: void set(Matrix4f^ value); }
	property List<SceneNodeAnimator^>^ AnimatorList { List<SceneNodeAnimator^>^ get(); }
	property unsigned int AutomaticCulling { unsigned int get(); void set(unsigned int value); }
	property AABBox3Df^ BoundingBox { AABBox3Df^ get(); }
	property AABBox3Df^ BoundingBoxTransformed { AABBox3Df^ get(); }
	property List<SceneNode^>^ ChildList { List<SceneNode^>^ get(); }
	property DebugSceneType DebugDataVisible { DebugSceneType get(); void set(DebugSceneType value); }
	property bool DebugObject { bool get(); void set(bool value); }
	property int ID { int get(); void set(int value); }
	property unsigned int MaterialCount { unsigned int get(); }
	property String^ Name { String^ get(); void set(String^ value); }
	property SceneNode^ Parent { SceneNode^ get(); void set(SceneNode^ value); }
	property Vector3Df^ Position { Vector3Df^ get(); void set(Vector3Df^ value); }
	property Matrix4f^ RelativeTransformation { Matrix4f^ get(); }
	property Vector3Df^ Rotation { Vector3Df^ get(); virtual void set(Vector3Df^ value); }
	property Vector3Df^ Scale { Vector3Df^ get(); void set(Vector3Df^ value); }
	property Scene::SceneManager^ SceneManager { Scene::SceneManager^ get(); protected: void set(Scene::SceneManager^ value); }
	property Scene::TriangleSelector^ TriangleSelector { Scene::TriangleSelector^ get(); void set(Scene::TriangleSelector^ value); }
	property bool TrulyVisible { bool get(); }
	property SceneNodeType Type { SceneNodeType get(); }
	property bool Visible { bool get(); virtual void set(bool value); }

	virtual String^ ToString() override;

	delegate AABBox3Df^ GetBoundingBoxEventHandler();
	delegate unsigned int GetMaterialCountEventHandler();
	delegate Video::Material^ GetMaterialEventHandler(unsigned int index);
	delegate void RegisterSceneNodeEventHandler();
	delegate void RenderEventHandler();

protected:

	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position, Vector3Df^ rotation, Vector3Df^ scale);
	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position, Vector3Df^ rotation);
	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id, Vector3Df^ position);
	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager, int id);
	SceneNode(SceneNode^ parent, Scene::SceneManager^ manager);

	event GetBoundingBoxEventHandler^ OnGetBoundingBox;
	event GetMaterialCountEventHandler^ OnGetMaterialCount;
	event GetMaterialEventHandler^ OnGetMaterial;
	event RegisterSceneNodeEventHandler^ OnRegisterSceneNode;
	event RenderEventHandler^ OnRender;

internal:

	static SceneNode^ Wrap(scene::ISceneNode* ref);
	SceneNode(scene::ISceneNode* ref);

	scene::ISceneNode* m_SceneNode;
	bool m_Inherited;

private:

	void initInheritor(SceneNodeInheritor* i);
};

} // end namespace Scene
} // end namespace IrrlichtLime