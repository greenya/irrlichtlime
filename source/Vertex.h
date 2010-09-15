#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

public ref class Vertex3D : Lime::NativeValue<video::S3DVertex>
{
public:

	Vertex3D()
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		m_NativeValue = new video::S3DVertex();
	}

	Vertex3D(float x, float y, float z, float nx, float ny, float nz, Color^ c, float tu, float tv)
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		LIME_ASSERT(c != nullptr);
		m_NativeValue = new video::S3DVertex(x, y, z, nx, ny, nz, *c->m_NativeValue, tu, tv);
	}

	Vertex3D(Vector3Df^ pos, Vector3Df^ normal, Color^ color, Vector2Df^ tcoords)
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		LIME_ASSERT(pos != nullptr);
		LIME_ASSERT(normal != nullptr);
		LIME_ASSERT(color != nullptr);
		LIME_ASSERT(tcoords != nullptr);

		m_NativeValue = new video::S3DVertex(*pos->m_NativeValue, *normal->m_NativeValue, *color->m_NativeValue, *tcoords->m_NativeValue);
	}

	Vertex3D^ GetInterpolated(Vertex3D^ other, float d)
	{
		LIME_ASSERT(other != nullptr);
		LIME_ASSERT(d >= 0.0f && d <= 1.0f);

		return gcnew Vertex3D(m_NativeValue->getInterpolated(*other->m_NativeValue, d));
	}

	property Vector3Df^ Position
	{
		Vector3Df^ get()
		{
			return gcnew Vector3Df(m_NativeValue->Pos);
		}
		void set(Vector3Df^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->Pos = *value->m_NativeValue;
		}
	}

	property Vector3Df^ Normal
	{
		Vector3Df^ get()
		{
			return gcnew Vector3Df(m_NativeValue->Normal);
		}
		void set(Vector3Df^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->Normal = *value->m_NativeValue;
		}
	}

	property Video::Color^ Color
	{
		Video::Color^ get()
		{
			return gcnew Video::Color(m_NativeValue->Color);
		}
		void set(Video::Color^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->Color = *value->m_NativeValue;
		}
	}

	property Vector2Df^ TCoords
	{
		Vector2Df^ get()
		{
			return gcnew Vector2Df(m_NativeValue->TCoords);
		}
		void set(Vector2Df^ value)
		{
			LIME_ASSERT(value != nullptr);
			m_NativeValue->TCoords = *value->m_NativeValue;
		}
	}

	property VertexType Type
	{
		VertexType get() { return (VertexType)m_NativeValue->getType(); }
	}

	virtual String^ ToString() override
	{
		return String::Format("Vertex3D: Type={0}; Position={1}", Type, Position);
	}

internal:

	Vertex3D(const video::S3DVertex& other)
		: Lime::NativeValue<video::S3DVertex>(true)
	{
		m_NativeValue = new video::S3DVertex(other);
	}
};

} // end namespace Video
} // end namespace IrrlichtLime