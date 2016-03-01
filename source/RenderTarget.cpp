#include "stdafx.h"
#include "Texture.h"
#include "RenderTarget.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

RenderTarget^ RenderTarget::Wrap(video::IRenderTarget* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew RenderTarget(ref);
}

RenderTarget::RenderTarget(video::IRenderTarget* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_RenderTarget = ref;
}

Texture^ RenderTarget::GetDepthStencil()
{
	return Texture::Wrap(m_RenderTarget->getDepthStencil());
}

NativeArray<Texture^>^ RenderTarget::GetTexture()
{
	return gcnew NativeArrayReadOnlyTemplate<Texture^, Texture, video::ITexture*>(&m_RenderTarget->getTexture());
}

void RenderTarget::SetTexture(array<Texture^>^ textures, Texture^ depthStencil)
{
	video::ITexture* depthStencilNative = LIME_SAFEREF(depthStencil, m_Texture);	//I think it could also be null
	if (textures == nullptr || textures->Length == 0)	//Allow the texture to be null, not entirely sure whether this is right. TODO: check if textures are allowed to be null
	{
		core::array<video::ITexture*> a(0);
		m_RenderTarget->setTexture(
			a,
			depthStencilNative);
	} else {	//textures array is not empty?
		core::array<video::ITexture*> a(textures->Length);
		for (int i = 0; i < textures->Length; i++)
			a.push_back(LIME_SAFEREF(textures[i], m_Texture));
		m_RenderTarget->setTexture(
			a,
			depthStencilNative);
	}
}

void RenderTarget::SetTexture(Texture^ texture, Texture^ depthStencil)
{
	m_RenderTarget->setTexture(
		LIME_SAFEREF(texture, m_Texture),
		LIME_SAFEREF(depthStencil, m_Texture));
}

Video::DriverType RenderTarget::DriverType::get()
{
	return (Video::DriverType)m_RenderTarget->getDriverType();
}

String^ RenderTarget::ToString()
{
	return String::Format("RenderTarget: DebugName={0}; DriverType={1}", DebugName, DriverType);
}


} // end namespace Video
} // end namespace IrrlichtLime