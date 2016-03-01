#include "stdafx.h"
#include "ContextManager.h"
#include "ExposedVideoData.h"
#include "IrrlichtCreationParameters.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace Video {

ContextManager^ ContextManager::Wrap(video::IContextManager* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew ContextManager(ref);
}

ContextManager::ContextManager(video::IContextManager* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_ContextManager = ref;
}

bool ContextManager::ActivateContext(ExposedVideoData^ videoData)
{
	LIME_ASSERT(videoData != nullptr);

	return m_ContextManager->activateContext(
		*videoData->m_NativeValue);
}

void ContextManager::DestroyContext()
{
	m_ContextManager->destroyContext();
}

void ContextManager::DestroySurface()
{
	m_ContextManager->destroySurface();
}

bool ContextManager::GenerateContext()
{
	return m_ContextManager->generateContext();
}

bool ContextManager::GenerateSurface()
{
	return m_ContextManager->generateSurface();
}

bool ContextManager::Initialize(IrrlichtCreationParameters^ params, ExposedVideoData^ data)
{
	LIME_ASSERT(params != nullptr);
	LIME_ASSERT(data != nullptr);

	return m_ContextManager->initialize(
		*params->m_NativeValue,
		*data->m_NativeValue);
}

void ContextManager::Terminate()
{
	m_ContextManager->terminate();
}

bool ContextManager::SwapBuffers()
{
	return m_ContextManager->swapBuffers();
}

ExposedVideoData^ ContextManager::Context::get()
{
	return gcnew ExposedVideoData(m_ContextManager->getContext());
}

} // end namespace Video
} // end namespace IrrlichtLime