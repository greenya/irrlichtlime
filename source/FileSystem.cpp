#include "stdafx.h"
#include "FileArchive.h"
#include "FileList.h"
#include "FileSystem.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

FileSystem^ FileSystem::Wrap(io::IFileSystem* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew FileSystem(ref);
}

FileSystem::FileSystem(io::IFileSystem* ref)
	: ReferenceCounted(ref)
{
	LIME_ASSERT(ref != nullptr);
	m_FileSystem = ref;
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType, String^ password)
{
	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths,
		(io::E_FILE_ARCHIVE_TYPE)archiveType,
		Lime::StringToStringC(password));
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType)
{
	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths,
		(io::E_FILE_ARCHIVE_TYPE)archiveType);
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths)
{
	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths);
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase)
{
	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase);
}

bool FileSystem::AddFileArchive(String^ filename)
{
	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename));
}

bool FileSystem::ChangeWorkingDirectory(String^ newDirectory)
{
	return m_FileSystem->changeWorkingDirectoryTo(Lime::StringToPath(newDirectory));
}

FileList^ FileSystem::CreateEmptyFileList(String^ path, bool ignoreCase, bool ignorePaths)
{
	io::IFileList* l = m_FileSystem->createEmptyFileList(
		Lime::StringToPath(path),
		ignoreCase,
		ignorePaths);

	return FileList::Wrap(l);
}

FileList^ FileSystem::CreateFileListFromWorkingDirectory()
{
	io::IFileList* l = m_FileSystem->createFileList();
	return FileList::Wrap(l);
}

String^ FileSystem::GetFileAbsolutePath(String^ filename)
{
	return gcnew String(m_FileSystem->getAbsolutePath(Lime::StringToPath(filename)).c_str());
}

FileArchive^ FileSystem::GetFileArchive(int index)
{
	LIME_ASSERT(index >= 0 && index < FileArchiveCount);

	io::IFileArchive* a = m_FileSystem->getFileArchive(index);
	return FileArchive::Wrap(a);
}

String^ FileSystem::GetFileBasename(String^ filename, bool keepExtension)
{
	return gcnew String(m_FileSystem->getFileBasename(Lime::StringToPath(filename), keepExtension).c_str());
}

String^ FileSystem::GetFileBasename(String^ filename)
{
	return gcnew String(m_FileSystem->getFileBasename(Lime::StringToPath(filename)).c_str());
}

String^ FileSystem::GetFileDirectory(String^ filename)
{
	return gcnew String(m_FileSystem->getFileDir(Lime::StringToPath(filename)).c_str());
}

bool FileSystem::MoveFileArchive(int index, int relative)
{
	LIME_ASSERT(index >= 0 && index < FileArchiveCount);
	return m_FileSystem->moveFileArchive(index, relative);
}

bool FileSystem::RemoveFileArchive(int index)
{
	LIME_ASSERT(index >= 0 && index < FileArchiveCount);
	return m_FileSystem->removeFileArchive(index);
}

bool FileSystem::RemoveFileArchive(String^ filename)
{
	return m_FileSystem->removeFileArchive(Lime::StringToPath(filename));
}

FileSystemType FileSystem::SetFileSystemType(FileSystemType newType)
{
	return (FileSystemType)m_FileSystem->setFileListSystem((io::EFileSystemType)newType);
}

int FileSystem::FileArchiveCount::get()
{
	return m_FileSystem->getFileArchiveCount();
}

String^ FileSystem::WorkingDirectory::get()
{
	return gcnew String(m_FileSystem->getWorkingDirectory().c_str());
}

String^ FileSystem::ToString()
{
	return String::Format("FileSystem: {0}", WorkingDirectory);
}

} // end namespace IO
} // end namespace IrrlichtLime