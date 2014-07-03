#include "stdafx.h"
#include "CameraSceneNode.h"
#include "SceneCollisionManager.h"
#include "SceneNode.h"
#include "TriangleSelector.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

SceneCollisionManager^ SceneCollisionManager::Wrap(scene::ISceneCollisionManager* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew SceneCollisionManager(ref);
}

SceneCollisionManager::SceneCollisionManager(scene::ISceneCollisionManager* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_SceneCollisionManager = ref;
}

bool SceneCollisionManager::GetCollisionPoint(Line3Df ray, TriangleSelector^ selector, [Out] Vector3Df% collisionPoint,
	[Out] Triangle3Df^% collisionTriangle, [Out] SceneNode^% collisionNode)
{
	core::vector3df cp;
	core::triangle3df ct;
	scene::ISceneNode* cn;

	bool b = m_SceneCollisionManager->getCollisionPoint(
		ray,
		LIME_SAFEREF(selector, m_TriangleSelector),
		cp, ct, cn);

	if (b)
	{
		collisionPoint = Vector3Df(cp);
		collisionTriangle = gcnew Triangle3Df(ct);
		collisionNode = SceneNode::Wrap(cn);
	}

	return b;
}

Vector3Df SceneCollisionManager::GetCollisionResultPosition(TriangleSelector^ selector, Vector3Df ellipsoidPosition, Vector3Df ellipsoidRadius,
	Vector3Df ellipsoidDirectionAndSpeed, [Out] Triangle3Df^% collisionTriangle, [Out] Vector3Df% collisionPosition, [Out] bool% falling,
	[Out] SceneNode^% collisionNode, float slidingSpeed, Vector3Df gravityDirectionAndSpeed)
{
	core::triangle3df ct;
	core::vector3df cp;
	bool f;
	scene::ISceneNode* cn;

	core::vector3df v = m_SceneCollisionManager->getCollisionResultPosition(
		LIME_SAFEREF(selector, m_TriangleSelector),
		ellipsoidPosition,
		ellipsoidRadius,
		ellipsoidDirectionAndSpeed,
		ct, cp, f, cn,
		slidingSpeed,
		gravityDirectionAndSpeed);

	collisionTriangle = gcnew Triangle3Df(ct);
	collisionPosition = Vector3Df(cp);
	falling = f;
	collisionNode = SceneNode::Wrap(cn);

	return Vector3Df(v);
}

Vector3Df SceneCollisionManager::GetCollisionResultPosition(TriangleSelector^ selector, Vector3Df ellipsoidPosition, Vector3Df ellipsoidRadius,
	Vector3Df ellipsoidDirectionAndSpeed, [Out] Triangle3Df^% collisionTriangle, [Out] Vector3Df% collisionPosition, [Out] bool% falling,
	[Out] SceneNode^% collisionNode, float slidingSpeed)
{
	core::triangle3df ct;
	core::vector3df cp;
	bool f;
	scene::ISceneNode* cn;

	core::vector3df v = m_SceneCollisionManager->getCollisionResultPosition(
		LIME_SAFEREF(selector, m_TriangleSelector),
		ellipsoidPosition,
		ellipsoidRadius,
		ellipsoidDirectionAndSpeed,
		ct, cp, f, cn,
		slidingSpeed);

	collisionTriangle = gcnew Triangle3Df(ct);
	collisionPosition = Vector3Df(cp);
	falling = f;
	collisionNode = SceneNode::Wrap(cn);

	return Vector3Df(v);
}

Vector3Df SceneCollisionManager::GetCollisionResultPosition(TriangleSelector^ selector, Vector3Df ellipsoidPosition, Vector3Df ellipsoidRadius,
	Vector3Df ellipsoidDirectionAndSpeed, [Out] Triangle3Df^% collisionTriangle, [Out] Vector3Df% collisionPosition, [Out] bool% falling,
	[Out] SceneNode^% collisionNode)
{
	core::triangle3df ct;
	core::vector3df cp;
	bool f;
	scene::ISceneNode* cn;

	core::vector3df v = m_SceneCollisionManager->getCollisionResultPosition(
		LIME_SAFEREF(selector, m_TriangleSelector),
		ellipsoidPosition,
		ellipsoidRadius,
		ellipsoidDirectionAndSpeed,
		ct, cp, f, cn);

	collisionTriangle = gcnew Triangle3Df(ct);
	collisionPosition = Vector3Df(cp);
	falling = f;
	collisionNode = SceneNode::Wrap(cn);

	return Vector3Df(v);
}

Line3Df SceneCollisionManager::GetRayFromScreenCoordinates(Vector2Di pos, CameraSceneNode^ camera)
{
	return Line3Df(m_SceneCollisionManager->getRayFromScreenCoordinates(pos, LIME_SAFEREF(camera, m_CameraSceneNode)));
}

Line3Df SceneCollisionManager::GetRayFromScreenCoordinates(Vector2Di pos)
{
	return Line3Df(m_SceneCollisionManager->getRayFromScreenCoordinates(pos));
}

SceneNode^ SceneCollisionManager::GetSceneNodeAndCollisionPointFromRay(Line3Df ray, [Out] Vector3Df% collisionPoint,
	[Out] Triangle3Df^% collisionTriangle, int idBitMask, SceneNode^ collisionRootNode, bool noDebugObjects)
{
	core::vector3df cp;
	core::triangle3df ct;

	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeAndCollisionPointFromRay(
		ray,
		cp, ct,
		idBitMask,
		LIME_SAFEREF(collisionRootNode, m_SceneNode),
		noDebugObjects);

	collisionPoint = Vector3Df(cp);
	collisionTriangle = gcnew Triangle3Df(ct);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeAndCollisionPointFromRay(Line3Df ray, [Out] Vector3Df% collisionPoint,
	[Out] Triangle3Df^% collisionTriangle, int idBitMask, SceneNode^ collisionRootNode)
{
	core::vector3df cp;
	core::triangle3df ct;

	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeAndCollisionPointFromRay(
		ray,
		cp, ct,
		idBitMask,
		LIME_SAFEREF(collisionRootNode, m_SceneNode));

	collisionPoint = Vector3Df(cp);
	collisionTriangle = gcnew Triangle3Df(ct);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeAndCollisionPointFromRay(Line3Df ray, [Out] Vector3Df% collisionPoint,
	[Out] Triangle3Df^% collisionTriangle, int idBitMask)
{
	core::vector3df cp;
	core::triangle3df ct;

	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeAndCollisionPointFromRay(
		ray,
		cp, ct,
		idBitMask);

	collisionPoint = Vector3Df(cp);
	collisionTriangle = gcnew Triangle3Df(ct);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeAndCollisionPointFromRay(Line3Df ray, [Out] Vector3Df% collisionPoint,
	[Out] Triangle3Df^% collisionTriangle)
{
	core::vector3df cp;
	core::triangle3df ct;

	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeAndCollisionPointFromRay(
		ray,
		cp, ct);

	collisionPoint = Vector3Df(cp);
	collisionTriangle = gcnew Triangle3Df(ct);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromCameraBB(CameraSceneNode^ camera, int idBitMask, bool noDebugObjects)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromCameraBB(
		LIME_SAFEREF(camera, m_CameraSceneNode),
		idBitMask,
		noDebugObjects);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromCameraBB(CameraSceneNode^ camera, int idBitMask)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromCameraBB(
		LIME_SAFEREF(camera, m_CameraSceneNode),
		idBitMask);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromCameraBB(CameraSceneNode^ camera)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromCameraBB(LIME_SAFEREF(camera, m_CameraSceneNode));
	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromRayBB(Line3Df ray, int idBitMask, SceneNode^ collisionRootNode, bool noDebugObjects)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromRayBB(
		ray,
		idBitMask,
		noDebugObjects,
		LIME_SAFEREF(collisionRootNode, m_SceneNode));

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromRayBB(Line3Df ray, int idBitMask, SceneNode^ collisionRootNode)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromRayBB(
		ray,
		idBitMask,
		false,
		LIME_SAFEREF(collisionRootNode, m_SceneNode));

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromRayBB(Line3Df ray, int idBitMask)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromRayBB(
		ray,
		idBitMask);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromRayBB(Line3Df ray)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromRayBB(ray);
	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromScreenCoordinatesBB(Vector2Di pos, int idBitMask, SceneNode^ collisionRootNode, bool noDebugObjects)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromScreenCoordinatesBB(
		pos,
		idBitMask,
		noDebugObjects,
		LIME_SAFEREF(collisionRootNode, m_SceneNode));

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromScreenCoordinatesBB(Vector2Di pos, int idBitMask, SceneNode^ collisionRootNode)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromScreenCoordinatesBB(
		pos,
		idBitMask,
		false,
		LIME_SAFEREF(collisionRootNode, m_SceneNode));

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromScreenCoordinatesBB(Vector2Di pos, int idBitMask)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromScreenCoordinatesBB(
		pos,
		idBitMask);

	return SceneNode::Wrap(n);
}

SceneNode^ SceneCollisionManager::GetSceneNodeFromScreenCoordinatesBB(Vector2Di pos)
{
	scene::ISceneNode* n = m_SceneCollisionManager->getSceneNodeFromScreenCoordinatesBB(pos);
	return SceneNode::Wrap(n);
}

Vector2Di SceneCollisionManager::GetScreenCoordinatesFrom3DPosition(Vector3Df pos, CameraSceneNode^ camera, bool useViewPort)
{
	return Vector2Di(
		m_SceneCollisionManager->getScreenCoordinatesFrom3DPosition(
			pos, LIME_SAFEREF(camera, m_CameraSceneNode), useViewPort));
}

Vector2Di SceneCollisionManager::GetScreenCoordinatesFrom3DPosition(Vector3Df pos, CameraSceneNode^ camera)
{
	return Vector2Di(m_SceneCollisionManager->getScreenCoordinatesFrom3DPosition(pos, LIME_SAFEREF(camera, m_CameraSceneNode)));
}

Vector2Di SceneCollisionManager::GetScreenCoordinatesFrom3DPosition(Vector3Df pos)
{
	return Vector2Di(m_SceneCollisionManager->getScreenCoordinatesFrom3DPosition(pos));
}

} // end namespace Scene
} // end namespace IrrlichtLime