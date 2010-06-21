#include "stdafx.h"
#include "FileList.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

FileList^ FileList::Wrap(io::IFileList* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew FileList(ref);
}

FileList::FileList(io::IFileList* ref)
	: ReferenceCounted(ref)
{
	m_FileList = ref;
}

unsigned int FileList::AddFile(String^ fullPath, unsigned int size, bool isDirectory, unsigned int id)
{
	return m_FileList->addItem(Lime::StringToPath(fullPath), size, isDirectory, id);
}

unsigned int FileList::AddFile(String^ fullPath, unsigned int size, bool isDirectory)
{
	return m_FileList->addItem(Lime::StringToPath(fullPath), size, isDirectory);
}

int FileList::FindFile(String^ filename, bool isDirectory)
{
	return m_FileList->findFile(Lime::StringToPath(filename), isDirectory);
}

int FileList::FindFile(String^ filename)
{
	return m_FileList->findFile(Lime::StringToPath(filename));
}

unsigned int FileList::GetFileID(unsigned int index)
{
	LIME_ASSERT(index < Count);
	return m_FileList->getID(index);
}

String^ FileList::GetFileName(unsigned int index)
{
	LIME_ASSERT(index < Count);
	return gcnew String(m_FileList->getFileName(index).c_str());
}

unsigned int FileList::GetFileSize(unsigned int index)
{
	LIME_ASSERT(index < Count);
	return m_FileList->getFileSize(index);
}

String^ FileList::GetFullFileName(unsigned int index)
{
	LIME_ASSERT(index < Count);
	return gcnew String(m_FileList->getFullFileName(index).c_str());
}

bool FileList::IsDirectory(unsigned int index)
{
	LIME_ASSERT(index < Count);
	return m_FileList->isDirectory(index);
}

void FileList::Sort()
{
	m_FileList->sort();
}

unsigned int FileList::Count::get()
{
	return m_FileList->getFileCount();
}

String^ FileList::Path::get()
{
	return gcnew String(m_FileList->getPath().c_str());
}

} // end namespace IO
} // end namespace IrrlichtLime