#include "stdafx.h"
#include "GUIButton.h"
#include "GUIElement.h"
#include "GUIFileOpenDialog.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace GUI {

GUIFileOpenDialog^ GUIFileOpenDialog::Wrap(gui::IGUIFileOpenDialog* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew GUIFileOpenDialog(ref);
}

GUIFileOpenDialog::GUIFileOpenDialog(gui::IGUIFileOpenDialog* ref)
	: GUIElement(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_GUIFileOpenDialog = ref;
}

String^ GUIFileOpenDialog::DirectoryName::get()
{
	const wchar_t* dirname = m_GUIFileOpenDialog->getDirectoryNameW();
	return dirname == nullptr ? nullptr : gcnew String(dirname);
}


String^ GUIFileOpenDialog::FileName::get()
{
	const wchar_t* filename = m_GUIFileOpenDialog->getFileName(); // Note: gui::IGUIFileOpenDialog::getFileName() returns wchar_t*
	return filename == nullptr ? nullptr : gcnew String(filename);
}

} // end namespace GUI
} // end namespace IrrlichtLime