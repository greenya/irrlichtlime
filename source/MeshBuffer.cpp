#include "stdafx.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

MeshBuffer^ MeshBuffer::Wrap(scene::IMeshBuffer* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew MeshBuffer(ref);
}

MeshBuffer::MeshBuffer(scene::IMeshBuffer* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_MeshBuffer = ref;
}

MeshBuffer^ MeshBuffer::Create(Video::VertexType vertexType, Video::IndexType indexType)
{
	switch (indexType)
	{
	case Video::IndexType::_16Bit:
		switch (vertexType)
		{
		case Video::VertexType::Standard:
			return gcnew MeshBuffer(new CMeshBuffer<video::S3DVertex>);

		case Video::VertexType::TTCoords:
			return gcnew MeshBuffer(new CMeshBuffer<video::S3DVertex2TCoords>);

		case Video::VertexType::Tangents:
			return gcnew MeshBuffer(new CMeshBuffer<video::S3DVertexTangents>);
		}

		LIME_ASSERT2(false, "Unexpected vertexType: " + vertexType.ToString());
		return nullptr;

	case Video::IndexType::_32Bit:
		return gcnew MeshBuffer(new CDynamicMeshBuffer((video::E_VERTEX_TYPE)vertexType, (video::E_INDEX_TYPE)indexType));
	}

	LIME_ASSERT2(false, "Unexpected combination of vertexType,indexType: " + vertexType.ToString() + "," + indexType.ToString());
	return nullptr;
}

void MeshBuffer::Append(MeshBuffer^ other)
{
	m_MeshBuffer->append(LIME_SAFEREF(other, m_MeshBuffer));
}

/*
void MeshBuffer::Append(array<Video::Vertex3D^>^ verticesStandard, array<unsigned short>^ indices16bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Standard);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(verticesStandard != nullptr);
	LIME_ASSERT(indices16bit != nullptr);

	int vc = verticesStandard->Length;
	video::S3DVertex* va = new video::S3DVertex[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *verticesStandard[i]->m_NativeValue;

	unsigned short* ia = new unsigned short[indices16bit->Length];
	Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(ia), indices16bit->Length);

	m_MeshBuffer->append(va, vc, ia, indices16bit->Length);

	delete[] ia;
	delete[] va;
}

void MeshBuffer::Append(array<Video::Vertex3DTTCoords^>^ verticesTTCoords, array<unsigned short>^ indices16bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::TTCoords);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(verticesTTCoords != nullptr);
	LIME_ASSERT(indices16bit != nullptr);

	int vc = verticesTTCoords->Length;
	video::S3DVertex* va = new video::S3DVertex2TCoords[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *verticesTTCoords[i]->m_NativeValue;

	unsigned short* ia = new unsigned short[indices16bit->Length];
	Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(ia), indices16bit->Length);

	m_MeshBuffer->append(va, vc, ia, indices16bit->Length);

	delete[] ia;
	delete[] va;
}

void MeshBuffer::Append(array<Video::Vertex3DTangents^>^ verticesTangents, array<unsigned short>^ indices16bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Tangents);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(verticesTangents != nullptr);
	LIME_ASSERT(indices16bit != nullptr);

	int vc = verticesTangents->Length;
	video::S3DVertex* va = new video::S3DVertexTangents[vc];
	for (int i = 0; i < vc; i++)
		va[i] = *verticesTangents[i]->m_NativeValue;

	unsigned short* ia = new unsigned short[indices16bit->Length];
	Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(ia), indices16bit->Length);

	m_MeshBuffer->append(va, vc, ia, indices16bit->Length);

	delete[] ia;
	delete[] va;
}

void MeshBuffer::Append(array<Video::Vertex3D^>^ verticesStandard, array<unsigned int>^ indices32bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Standard);
	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
	LIME_ASSERT(verticesStandard != nullptr);
	LIME_ASSERT(indices32bit != nullptr);

	// as i know:
	// 1) 32bit meshbuffers is only possible with IDynamicMeshBuffer, so i will cast to it
	// 2) append() doesn't have ability to be used with 32 bit indices, so we are going to implement it here manually

	scene::IDynamicMeshBuffer* mb = (scene::IDynamicMeshBuffer*)m_MeshBuffer;
	scene::IIndexBuffer& ib = mb->getIndexBuffer();
	scene::IVertexBuffer& vb = mb->getVertexBuffer();

	unsigned int ibSize = ib.size();
	unsigned int vbSize = vb.size();

	ib.set_used(ibSize + indices32bit->Length);
	for (int i = 0; i < indices32bit->Length; i++)
		ib.setValue(i + ibSize, indices32bit[i] + vbSize); // simple "ib[i + ibSize] = ...;" leads to error C2106: '=' : left operand must be l-value

	vb.set_used(vbSize + verticesStandard->Length);
	for (int i = 0; i < verticesStandard->Length; i++)
		vb[i + vbSize] = *verticesStandard[i]->m_NativeValue;
}

void MeshBuffer::Append(array<Video::Vertex3DTTCoords^>^ verticesTTCoords, array<unsigned int>^ indices32bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::TTCoords);
	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
	LIME_ASSERT(verticesTTCoords != nullptr);
	LIME_ASSERT(indices32bit != nullptr);

	scene::IDynamicMeshBuffer* mb = (scene::IDynamicMeshBuffer*)m_MeshBuffer;
	scene::IIndexBuffer& ib = mb->getIndexBuffer();
	scene::IVertexBuffer& vb = mb->getVertexBuffer();

	unsigned int ibSize = ib.size();
	unsigned int vbSize = vb.size();

	ib.set_used(ibSize + indices32bit->Length);
	for (int i = 0; i < indices32bit->Length; i++)
		ib.setValue(i + ibSize, indices32bit[i] + vbSize);

	vb.set_used(vbSize + verticesTTCoords->Length);
	for (int i = 0; i < verticesTTCoords->Length; i++)
		vb[i + vbSize] = *verticesTTCoords[i]->m_NativeValue;
}

void MeshBuffer::Append(array<Video::Vertex3DTangents^>^ verticesTangents, array<unsigned int>^ indices32bit)
{
	LIME_ASSERT(this->VertexType == Video::VertexType::Tangents);
	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
	LIME_ASSERT(verticesTangents != nullptr);
	LIME_ASSERT(indices32bit != nullptr);

	scene::IDynamicMeshBuffer* mb = (scene::IDynamicMeshBuffer*)m_MeshBuffer;
	scene::IIndexBuffer& ib = mb->getIndexBuffer();
	scene::IVertexBuffer& vb = mb->getVertexBuffer();

	unsigned int ibSize = ib.size();
	unsigned int vbSize = vb.size();

	ib.set_used(ibSize + indices32bit->Length);
	for (int i = 0; i < indices32bit->Length; i++)
		ib.setValue(i + ibSize, indices32bit[i] + vbSize);

	vb.set_used(vbSize + verticesTangents->Length);
	for (int i = 0; i < verticesTangents->Length; i++)
		vb[i + vbSize] = *verticesTangents[i]->m_NativeValue;
}
*/

//generic<typename T>
//where T : Video::IVertex3D, value class
//void MeshBuffer::Append(ICollection<T>^ vertices, array<unsigned short>^ indices16bit)
//{
//	LIME_ASSERT(vertices != nullptr);
//	if (vertices->Count <= 0) return;
//	LIME_ASSERT(this->VertexType == T()->Type);
//	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
//	LIME_ASSERT(indices16bit != nullptr);
//
//	int vc = vertices->Count;
//
//	pin_ptr<void> vpin;	//pin pointer for .net arrays
//	void* va;
//
//	{	//test if it is a .net array
//		try
//		{
//			array<T>^ castResult = safe_cast<array<T>^>(vertices);
//			if (castResult != nullptr)
//			{
//				vpin = &castResult[0];
//				va = vpin;
//			}
//		} catch (...) {}
//	}
//	
//	if (va == 0)	//no .net array! test for our VertexArray class
//	{
//		NativeArray<T>^ castResult = dynamic_cast<NativeArray<T>^>(vertices);
//		if (castResult != nullptr)
//		{
//			void* ptr = castResult->GetPointer();
//			if (ptr != 0)
//				va = ptr;
//		}
//	}
//
//	bool va_delete = false;
//	if (va == 0)	//no .net array and no VertexArray?
//	{
//		va_delete = true;
//		if (T::typeid == Video::Vertex3D::typeid)
//		{
//			Video::Vertex3D* va_typed = (Video::Vertex3D*)new video::S3DVertex[vc];
//			va = va_typed;
//
//			int i = 0;
//			for each(Video::Vertex3D vert in vertices)
//				va_typed[i] = vert;
//		} else if (T::typeid == Video::Vertex3DTTCoords::typeid)
//		{
//			Video::Vertex3DTTCoords* va_typed = (Video::Vertex3DTTCoords*)new video::S3DVertex2TCoords[vc];
//			va = va_typed;
//
//			int i = 0;
//			for each(Video::Vertex3DTTCoords vert in vertices)
//				va_typed[i] = vert;
//		} else if (T::typeid == Video::Vertex3DTangents::typeid)
//		{
//			Video::Vertex3DTangents* va_typed = (Video::Vertex3DTangents*)new video::S3DVertexTangents[vc];
//			va = va_typed;
//
//			int i = 0;
//			for each(Video::Vertex3DTangents vert in vertices)
//				va_typed[i] = vert;
//		} else
//			throw gcnew Exception("Unexpected vertex format");
//	}
//
//	/*video::S3DVertex* va = new video::S3DVertex[vc];
//	for (int i = 0; i < vc; i++)
//		va[i] = *verticesStandard[i]->m_NativeValue;*/
//
//	pin_ptr<unsigned short> ia = &indices16bit[0];
//	/*unsigned short* ia = new unsigned short[indices16bit->Length];
//	Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(ia), indices16bit->Length);*/
//
//	m_MeshBuffer->append(va, vc, ia, indices16bit->Length);
//
//	if (va_delete)
//		delete[] va;
//}

template <typename LimeT, typename NativeT>
void MeshBuffer::AppendInternal(ICollection<LimeT>^ vertices, ICollection<unsigned short>^ indices16bit)
{
	if (vertices->Count <= 0) return;
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(this->VertexType == LimeT().Type);
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(indices16bit != nullptr);

	//Get vertex pointer

	int vc = vertices->Count;
	pin_ptr<LimeT> vpin;	//pin pointer for .net arrays
	NativeT* va = 0;

	{	//test if it is a .net array
		try
		{
			array<LimeT>^ castResult = safe_cast<array<LimeT>^>(vertices);
			if (castResult != nullptr)
			{
				vpin = &castResult[0];
				va = (NativeT*)vpin;
			}
		} catch (...) {}
	}
	
	if (va == 0)	//no .net array! test for our VertexArray class (or another class which can return a pointer)
	{
		NativeArray<LimeT>^ castResult = dynamic_cast<NativeArray<LimeT>^>(vertices);
		if (castResult != nullptr)
		{
			void* ptr = castResult->GetPointer();
			if (ptr != 0)
				va = (NativeT*)ptr;
		}
	}

	bool va_delete = false;	//deleta va in the end?
	if (va == 0)	//no .net array and no VertexArray? copy into a new native array
	{
		va_delete = true;

		LimeT* va_typed = (LimeT*)new NativeT[vc];
		va = (NativeT*)va_typed;

		int i = 0;
		for each (LimeT vert in vertices)
			va_typed[i++] = vert;
	}

	//Get index pointer

	int ic = indices16bit->Count;
	pin_ptr<unsigned short> ipin;
	unsigned short* ia = 0;

	{
		try
		{
			array<unsigned short>^ castResult = safe_cast<array<unsigned short>^>(indices16bit);
			if (castResult != nullptr)
			{
				ipin = &castResult[0];
				ia = ipin;
			}
		} catch (...) {}
	}

	if (ia == 0)
	{
		NativeArray<unsigned short>^ castResult = dynamic_cast<NativeArray<unsigned short>^>(indices16bit);
		if (castResult != nullptr)
		{
			void* ptr = castResult->GetPointer();
			if (ptr != 0)
				ia = (unsigned short*)ptr;
		}
	}

	bool ia_delete = false;
	if (ia == 0)
	{
		ia_delete = true;

		ia = new unsigned short[ic];
		
		int i = 0;
		for each (unsigned short index in indices16bit)
			ia[i++] = index;
	}

	m_MeshBuffer->append(va, vc, ia, ic);

	if (va_delete)
		delete[] va;
	if (ia_delete)
		delete[] ia;
}

void MeshBuffer::Append(ICollection<Video::Vertex3D>^ verticesStandard, ICollection<unsigned short>^ indices16bit)
{
	AppendInternal<Video::Vertex3D, video::S3DVertex>(verticesStandard, indices16bit);
}

void MeshBuffer::Append(ICollection<Video::Vertex3DTTCoords>^ verticesTTCoords, ICollection<unsigned short>^ indices16bit)
{
	AppendInternal<Video::Vertex3DTTCoords, video::S3DVertex2TCoords>(verticesTTCoords, indices16bit);
}

void MeshBuffer::Append(ICollection<Video::Vertex3DTangents>^ verticesTangents, ICollection<unsigned short>^ indices16bit)
{
	AppendInternal<Video::Vertex3DTangents, video::S3DVertexTangents>(verticesTangents, indices16bit);
}

template <typename LimeT, typename NativeT>
void MeshBuffer::AppendInternal(ICollection<LimeT>^ vertices, ICollection<unsigned int>^ indices32bit)
{
	if (vertices->Count <= 0) return;
	LIME_ASSERT(vertices != nullptr);
	LIME_ASSERT(this->VertexType == LimeT().Type);
	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
	LIME_ASSERT(indices32bit != nullptr);

	// as i know:
	// 1) 32bit meshbuffers is only possible with IDynamicMeshBuffer, so i will cast to it
	// 2) append() doesn't have ability to be used with 32 bit indices, so we are going to implement it here manually

	scene::IDynamicMeshBuffer* mb = (scene::IDynamicMeshBuffer*)m_MeshBuffer;
	scene::IIndexBuffer& ib = mb->getIndexBuffer();
	scene::IVertexBuffer& vb = mb->getVertexBuffer();

	unsigned int ibSize = ib.size();
	unsigned int vbSize = vb.size();

	//This implementation should already be nearly as fast as possible

	ib.set_used(ibSize + indices32bit->Count);
	{
		int i = 0;
		for each (unsigned int index in indices32bit)
		{
			ib.setValue(i + ibSize, index + vbSize); // simple "ib[i + ibSize] = ...;" leads to error C2106: '=' : left operand must be l-value
			i++;
		}
	}

	vb.set_used(vbSize + vertices->Count);
	{
		int i = 0;
		LimeT* vertDst = (LimeT*)vb.pointer();
		for each (LimeT vertex in vertices)
		{
			vertDst[i + vbSize] = vertex;
			i++;
		}
	}
}

void MeshBuffer::Append(ICollection<Video::Vertex3D>^ verticesStandard, ICollection<unsigned int>^ indices32bit)
{
	AppendInternal<Video::Vertex3D, video::S3DVertex>(verticesStandard, indices32bit);
}

void MeshBuffer::Append(ICollection<Video::Vertex3DTTCoords>^ verticesTTCoords, ICollection<unsigned int>^ indices32bit)
{
	AppendInternal<Video::Vertex3DTTCoords, video::S3DVertex2TCoords>(verticesTTCoords, indices32bit);
}

void MeshBuffer::Append(ICollection<Video::Vertex3DTangents>^ verticesTangents, ICollection<unsigned int>^ indices32bit)
{
	AppendInternal<Video::Vertex3DTangents, video::S3DVertexTangents>(verticesTangents, indices32bit);
}

//generic<typename T>
//where T : Video::IVertex3D, value class
//void MeshBuffer::Append(array<T>^ vertices, array<unsigned int>^ indices32bit)
//{
//	LIME_ASSERT(vertices != nullptr);
//	if (vertices->Length <= 0) return;
//	LIME_ASSERT(this->VertexType == vertices[0]->Type);
//	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
//	LIME_ASSERT(indices32bit != nullptr);
//
//	// as i know:
//	// 1) 32bit meshbuffers is only possible with IDynamicMeshBuffer, so i will cast to it
//	// 2) append() doesn't have ability to be used with 32 bit indices, so we are going to implement it here manually
//
//	scene::IDynamicMeshBuffer* mb = (scene::IDynamicMeshBuffer*)m_MeshBuffer;
//	scene::IIndexBuffer& ib = mb->getIndexBuffer();
//	scene::IVertexBuffer& vb = mb->getVertexBuffer();
//
//	unsigned int ibSize = ib.size();
//	unsigned int vbSize = vb.size();
//
//	ib.set_used(ibSize + indices32bit->Length);
//	for (int i = 0; i < indices32bit->Length; i++)
//		ib.setValue(i + ibSize, indices32bit[i] + vbSize); // simple "ib[i + ibSize] = ...;" leads to error C2106: '=' : left operand must be l-value
//
//	vb.set_used(vbSize + vertices->Length);
//
//	pin_ptr<T> vertScrPin = &vertices[0];
//
//	if (T::typeid == Video::Vertex3D::typeid)
//	{
//		S3DVertex* vertScr = (S3DVertex*)vertScrPin;
//		S3DVertex* vertDst = (S3DVertex*)vb.pointer();
//		for (int i = 0; i < vertices->Length; i++)
//			vertDst[i + vbSize] = vertScr[i];
//	}
//	else if (T::typeid == Video::Vertex3DTTCoords::typeid)
//	{
//		S3DVertex2TCoords* vertScr = (S3DVertex2TCoords*)vertScrPin;
//		S3DVertex2TCoords* vertDst = (S3DVertex2TCoords*)vb.pointer();
//		for (int i = 0; i < vertices->Length; i++)
//			vertDst[i + vbSize] = vertScr[i];
//	}
//	else if (T::typeid == Video::Vertex3DTangents::typeid)
//	{
//		S3DVertexTangents* vertScr = (S3DVertexTangents*)vertScrPin;
//		S3DVertexTangents* vertDst = (S3DVertexTangents*)vb.pointer();
//		for (int i = 0; i < vertices->Length; i++)
//			vertDst[i + vbSize] = vertScr[i];
//	}
//	else LIME_ASSERT2(false, "Unexpected VertexType: " + T::typeid->ToString());
//}

Vector3Df MeshBuffer::GetNormal(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return Vector3Df(m_MeshBuffer->getNormal(vertexIndex));
}

Vector3Df MeshBuffer::GetPosition(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return Vector3Df(m_MeshBuffer->getPosition(vertexIndex));
}

Vector2Df MeshBuffer::GetTCoords(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);
	return Vector2Df(m_MeshBuffer->getTCoords(vertexIndex));
}

Video::IVertex3D^ MeshBuffer::GetVertex(int vertexIndex)
{
	LIME_ASSERT(vertexIndex >= 0 && vertexIndex < VertexCount);

	void* va = m_MeshBuffer->getVertices();

	switch (m_MeshBuffer->getVertexType())
	{
	case video::EVT_STANDARD:
		return Video::Vertex3D(((video::S3DVertex*)va)[vertexIndex]);

	case video::EVT_2TCOORDS:
		return Video::Vertex3DTTCoords(((video::S3DVertex2TCoords*)va)[vertexIndex]);

	case video::EVT_TANGENTS:
		return Video::Vertex3DTangents(((video::S3DVertexTangents*)va)[vertexIndex]);
	}

	LIME_ASSERT2(false, "Unexpected VertexType: " + this->VertexType.ToString());
	return nullptr;
}

void MeshBuffer::RecalculateBoundingBox()
{
	m_MeshBuffer->recalculateBoundingBox();
}

void MeshBuffer::SetDirty(HardwareBufferType buffer)
{
	m_MeshBuffer->setDirty((scene::E_BUFFER_TYPE)buffer);
}

void MeshBuffer::SetHardwareMappingHint(HardwareMappingHint mappingHint, HardwareBufferType buffer)
{
	m_MeshBuffer->setHardwareMappingHint((scene::E_HARDWARE_MAPPING)mappingHint, (scene::E_BUFFER_TYPE)buffer);
}

void MeshBuffer::SetMaterial(Video::Material^ newMaterialToCopyFrom)
{
	LIME_ASSERT(newMaterialToCopyFrom != nullptr);
	m_MeshBuffer->getMaterial() = *newMaterialToCopyFrom->m_NativeValue;
}

/*void MeshBuffer::UpdateIndices(array<unsigned short>^ indices16bit, int startIndex)
{
	LIME_ASSERT(this->IndexType == Video::IndexType::_16Bit);
	LIME_ASSERT(indices16bit != nullptr);
	LIME_ASSERT(startIndex + indices16bit->Length <= this->IndexCount);

	unsigned short* p = m_MeshBuffer->getIndices();
	Marshal::Copy((array<short>^)indices16bit, 0, IntPtr(p + startIndex), indices16bit->Length);
}

void MeshBuffer::UpdateIndices(array<unsigned int>^ indices32bit, int startIndex)
{
	LIME_ASSERT(this->IndexType == Video::IndexType::_32Bit);
	LIME_ASSERT(indices32bit != nullptr);
	LIME_ASSERT(startIndex + indices32bit->Length <= this->IndexCount);

	unsigned int* p = (unsigned int*)m_MeshBuffer->getIndices();
	Marshal::Copy((array<int>^)indices32bit, 0, IntPtr(p + startIndex), indices32bit->Length);
}*/

AABBox^ MeshBuffer::BoundingBox::get()
{
	return gcnew AABBox(m_MeshBuffer->getBoundingBox());
}

void MeshBuffer::BoundingBox::set(AABBox^ value)
{
	LIME_ASSERT(value != nullptr);
	m_MeshBuffer->setBoundingBox(*value->m_NativeValue);
}

HardwareMappingHint MeshBuffer::HardwareMappingHintForIndex::get()
{
	return (HardwareMappingHint)m_MeshBuffer->getHardwareMappingHint_Index();
}

HardwareMappingHint MeshBuffer::HardwareMappingHintForVertex::get()
{
	return (HardwareMappingHint)m_MeshBuffer->getHardwareMappingHint_Vertex();
}

int MeshBuffer::IndexCount::get()
{
	return m_MeshBuffer->getIndexCount();
}

Video::IndexType MeshBuffer::IndexType::get()
{
	return (Video::IndexType)m_MeshBuffer->getIndexType();
}



NativeArray<unsigned short>^ MeshBuffer::GetIndices16Bit()
{
	if (m_MeshBuffer->getIndexType() == video::EIT_16BIT)
		return gcnew IndexArray<unsigned short>(m_MeshBuffer);

	return nullptr;
}

NativeArray<unsigned int>^ MeshBuffer::GetIndices32Bit()
{
	if (m_MeshBuffer->getIndexType() == video::EIT_32BIT)
		return gcnew IndexArray<unsigned int>(m_MeshBuffer);

	return nullptr;
}

Video::Material^ MeshBuffer::Material::get()
{
	return Video::Material::Wrap(&m_MeshBuffer->getMaterial());
}

int MeshBuffer::VertexCount::get()
{
	return m_MeshBuffer->getVertexCount();
}

Video::VertexType MeshBuffer::VertexType::get()
{
	return (Video::VertexType)m_MeshBuffer->getVertexType();
}

generic<typename T>
where T : Video::IVertex3D, value class
NativeArray<T>^ MeshBuffer::GetVertices()
{
	switch (m_MeshBuffer->getVertexType())
	{
	case video::EVT_STANDARD:
		{
			if (T::typeid != Video::Vertex3D::typeid)
				return nullptr;

			VertexArray<Video::Vertex3D>^ v = gcnew VertexArray<Video::Vertex3D>(m_MeshBuffer);
			return (NativeArray<T>^)v;
		}

	case video::EVT_2TCOORDS:
		{
			if (T::typeid != Video::Vertex3DTTCoords::typeid)
				return nullptr;

			VertexArray<Video::Vertex3DTTCoords>^ v = gcnew VertexArray<Video::Vertex3DTTCoords>(m_MeshBuffer);
			return (NativeArray<T>^)v;
		}

	case video::EVT_TANGENTS:
		{
			if (T::typeid != Video::Vertex3DTangents::typeid)
				return nullptr;

			VertexArray<Video::Vertex3DTangents>^ v = gcnew VertexArray<Video::Vertex3DTangents>(m_MeshBuffer);
			return (NativeArray<T>^)v;
		}
	}

	LIME_ASSERT2(false, "Unexpected VertexType: " + this->VertexType.ToString());
	return nullptr;
}

String^ MeshBuffer::ToString()
{
	return String::Format("MeshBuffer: {0} {1} vertices and {2} {3} indices", VertexCount, VertexType, IndexCount, IndexType);
}

} // end namespace Scene
} // end namespace IrrlichtLime