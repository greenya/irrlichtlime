#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Video { ref class Material; }
namespace Scene {

public ref class MeshBuffer : ReferenceCounted
{
public:

	static MeshBuffer^ Create(Video::VertexType vertexType, Video::IndexType indexType);

	void Append(MeshBuffer^ other);
	/*void Append(array<Video::Vertex3D^>^ verticesStandard, array<unsigned short>^ indices16bit);
	void Append(array<Video::Vertex3DTTCoords^>^ verticesTTCoords, array<unsigned short>^ indices16bit);
	void Append(array<Video::Vertex3DTangents^>^ verticesTangents, array<unsigned short>^ indices16bit);
	void Append(array<Video::Vertex3D^>^ verticesStandard, array<unsigned int>^ indices32bit);
	void Append(array<Video::Vertex3DTTCoords^>^ verticesTTCoords, array<unsigned int>^ indices32bit);
	void Append(array<Video::Vertex3DTangents^>^ verticesTangents, array<unsigned int>^ indices32bit);*/
	//generic<typename T> where T : Video::IVertex3D, value class void Append(ICollection<T>^ vertices, array<unsigned short>^ indices16bit);
	void Append(ICollection<Video::Vertex3D>^ verticesStandard, ICollection<unsigned short>^ indices16bit);
	void Append(ICollection<Video::Vertex3DTTCoords>^ verticesTTCoords, ICollection<unsigned short>^ indices16bit);
	void Append(ICollection<Video::Vertex3DTangents>^ verticesTangents, ICollection<unsigned short>^ indices16bit);
	//generic<typename T> where T : Video::IVertex3D, value class void Append(array<T>^ vertices, array<unsigned int>^ indices32bit);
	void Append(ICollection<Video::Vertex3D>^ verticesStandard, ICollection<unsigned int>^ indices32bit);
	void Append(ICollection<Video::Vertex3DTTCoords>^ verticesTTCoords, ICollection<unsigned int>^ indices32bit);
	void Append(ICollection<Video::Vertex3DTangents>^ verticesTangents, ICollection<unsigned int>^ indices32bit);

	NativeArray<unsigned short>^ GetIndices16Bit();
	NativeArray<unsigned int>^ GetIndices32Bit();
	Vector3Df GetNormal(int vertexIndex);
	Vector3Df GetPosition(int vertexIndex);
	Vector2Df GetTCoords(int vertexIndex);
	Video::IVertex3D^ GetVertex(int vertexIndex);
	generic<typename T> where T : Video::IVertex3D, value class NativeArray<T>^ GetVertices();

	void RecalculateBoundingBox();

	void SetDirty(HardwareBufferType buffer);
	void SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer);

	void SetMaterial(Video::Material^ newMaterialToCopyFrom);

	//void UpdateIndices(array<unsigned short>^ indices16bit, int startIndex);
	//void UpdateIndices(array<unsigned int>^ indices32bit, int startIndex);

	property AABBox^ BoundingBox { AABBox^ get(); void set(AABBox^ value); }
	property HardwareMappingHint HardwareMappingHintForIndex { HardwareMappingHint get(); }
	property HardwareMappingHint HardwareMappingHintForVertex { HardwareMappingHint get(); }
	property int IndexCount { int get(); }
	property Video::IndexType IndexType { Video::IndexType get(); }
	//property Object^ Indices { Object^ get(); }
	property Video::Material^ Material { Video::Material^ get(); }
	property unsigned int PrimitiveCount { unsigned int get(); }
	property Scene::PrimitiveType PrimitiveType { Scene::PrimitiveType get(); void set(Scene::PrimitiveType value); }
	property int VertexCount { int get(); }
	property Video::VertexType VertexType { Video::VertexType get(); }

	virtual String^ ToString() override;

private:

	template <typename T>
	ref class IndexArray sealed : public NativeArray<T>
	{
	
	internal:

		IndexArray(IMeshBuffer* meshBuffer)
		{
			this->meshBuffer = meshBuffer;
			indexPointer = (T*)meshBuffer->getIndices();
	#ifdef DEBUG
			if (T::typeid == (unsigned short)::typeid)
				indexType = Video::IndexType::_16Bit;
			else if (T::typeid == (unsigned int)::typeid)
				indexType = Video::IndexType::_32Bit;
			else
				LIME_ASSERT2(false, "Unexpected IndexType");
	#endif
		}

		virtual void* GetPointer() override sealed
		{
			return indexPointer;
		}

	public:

		property T default [int]
		{
			virtual T get(int index) override sealed
			{
	#ifdef DEBUG	//doesn't make any sense, as LIME_ASSERT is compiled, only if debug is enabled. but the compiler doesn't accept it. weird
				LIME_ASSERT(indexType == (Video::IndexType)meshBuffer->getIndexType());
	#endif
				LIME_ASSERT(index >= 0 && index < Count);
				return indexPointer[index];
			}

			virtual void set(int index, T value) override sealed
			{
	#ifdef DEBUG
				LIME_ASSERT(indexType == (Video::IndexType)meshBuffer->getIndexType());
	#endif
				LIME_ASSERT(index >= 0 && index < Count);
				indexPointer[index] = value;
			}
		}

		property int Count
		{
			virtual int get() override sealed
			{
				return meshBuffer->getIndexCount();
			}
		}

		property bool IsReadOnly
		{
			virtual bool get() override sealed
			{
				return false;
			}
		}

	internal:
	
		IMeshBuffer* meshBuffer;
		T* indexPointer;
	#ifdef DEBUG
		Video::IndexType indexType;
	#endif
	};

	//This class provides direct access to the vertices of a mesh buffer
	//In debug builds, it checks, whether the vertex type changed and performs range checks
	template <typename T>
	ref class VertexArray sealed : public NativeArray<T>
	{

	internal:

		VertexArray(IMeshBuffer* meshBuffer)
		{
			this->meshBuffer = meshBuffer;
			vertexPointer = (T*)meshBuffer->getVertices();
	#ifdef DEBUG
			if (T::typeid == Video::Vertex3D::typeid)
				vertexType = Video::VertexType::Standard;
			else if (T::typeid == Video::Vertex3DTTCoords::typeid)
				vertexType = Video::VertexType::TTCoords;
			else if (T::typeid == Video::Vertex3DTangents::typeid)
				vertexType = Video::VertexType::Tangents;
			else
				LIME_ASSERT2(false, "Unexpected VertexType");
	#endif
		}

		virtual void* GetPointer() override sealed
		{
			return vertexPointer;
		}

	public:

		property T default [int]
		{
			virtual T get(int index) override sealed
			{
	#ifdef DEBUG	//doesn't make any sense, as LIME_ASSERT is compiled, only if debug is enabled. but the compiler doesn't accept it. weird
				LIME_ASSERT(vertexType == (Video::VertexType)meshBuffer->getVertexType());
	#endif
				LIME_ASSERT(index >= 0 && index < Count);
				return vertexPointer[index];
			}

			virtual void set(int index, T value) override sealed
			{
	#ifdef DEBUG
				LIME_ASSERT(vertexType == (Video::VertexType)meshBuffer->getVertexType());
	#endif
				LIME_ASSERT(index >= 0 && index < Count);
				vertexPointer[index] = value;
			}
		}

		property int Count
		{
			virtual int get() override sealed
			{
				return meshBuffer->getVertexCount();
			}
		}

		property bool IsReadOnly
		{
			virtual bool get() override sealed
			{
				return false;
			}
		}

	internal:
	
		IMeshBuffer* meshBuffer;
		T* vertexPointer;
	#ifdef DEBUG
		Video::VertexType vertexType;
	#endif
	};

	template <typename LimeT, typename NativeT>
	void AppendInternal(ICollection<LimeT>^ vertices, ICollection<unsigned short>^ indices16bit);
	template <typename LimeT, typename NativeT>
	void AppendInternal(ICollection<LimeT>^ vertices, ICollection<unsigned int>^ indices32bit);

internal:

	static MeshBuffer^ Wrap(scene::IMeshBuffer* ref);
	MeshBuffer(scene::IMeshBuffer* ref);

	scene::IMeshBuffer* m_MeshBuffer;
};

} // end namespace Scene
} // end namespace IrrlichtLime