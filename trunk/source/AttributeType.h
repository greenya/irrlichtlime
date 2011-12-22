#pragma once

#include "stdafx.h"

using namespace irr;
using namespace io;
using namespace System;

namespace IrrlichtLime {
namespace IO {

public enum class AttributeType
{
	Int = EAT_INT,
	Float = EAT_FLOAT,
	String = EAT_STRING,
	Bool = EAT_BOOL,
	Enum = EAT_ENUM, // read-only type; i don't have clear solution for implementation of adding and modifying values; read more in Attributes::AddValue() in proper switch-case region
	Color = EAT_COLOR,
	Colorf = EAT_COLORF,
	Vector3Df = EAT_VECTOR3D,
	Vector2Di = EAT_POSITION2D,
	Vector2Df = EAT_VECTOR2D,
	Recti = EAT_RECT,
	Matrix = EAT_MATRIX,
	Quaternion = EAT_QUATERNION,
	AABBox = EAT_BBOX,
	Plane3Df = EAT_PLANE,
	Triangle3Df = EAT_TRIANGLE3D,
	// EAT_LINE2D // we don't support it, because we do not have Line2Df type
	Line3Df = EAT_LINE3D,
	StringArray = EAT_STRINGWARRAY,
	// EAT_FLOATARRAY // i have no idea how to add/read/write this type using io::IAttributes :(
	// EAT_INTARRAY // (either)
	ByteArray = EAT_BINARY,
	Texture = EAT_TEXTURE,
	// EAT_USER_POINTER // we don't support it
	// EAT_DIMENSION2D // we don't have Dimension2Du type; for holding Dimension2Di-type-like value user can use Vector2Di
	// EAT_COUNT
	Unknown = EAT_UNKNOWN
};

} // end namespace IO
} // end namespace IrrlichtLime