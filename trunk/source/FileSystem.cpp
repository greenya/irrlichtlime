#include "stdafx.h"
#include "FileArchive.h"
#include "FileList.h"
#include "FileSystem.h"
#include "ReadFile.h"
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
	LIME_ASSERT(filename != nullptr);

	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths,
		(io::E_FILE_ARCHIVE_TYPE)archiveType,
		Lime::StringToStringC(password));
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType)
{
	LIME_ASSERT(filename != nullptr);

	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths,
		(io::E_FILE_ARCHIVE_TYPE)archiveType);
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths)
{
	LIME_ASSERT(filename != nullptr);

	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase,
		ignorePaths);
}

bool FileSystem::AddFileArchive(String^ filename, bool ignoreCase)
{
	LIME_ASSERT(filename != nullptr);

	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename),
		ignoreCase);
}

bool FileSystem::AddFileArchive(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	return m_FileSystem->addFileArchive(
		Lime::StringToPath(filename));
}

ReadFile^ FileSystem::CreateReadFile(String^ filename)
{
	LIME_ASSERT(filename != nullptr);

	io::IReadFile* f = m_FileSystem->createAndOpenFile(Lime::StringToPath(filename));
	return ReadFile::Wrap(f);
}

FileList^ FileSystem::CreateEmptyFileList(String^ path, bool ignoreCase, bool ignorePaths)
{
	LIME_ASSERT(path != nullptr);

	io::IFileList* l = m_FileSystem->createEmptyFileList(
		Lime::StringToPath(path),
		ignoreCase,
		ignorePaths);

	return FileList::Wrap(l);
}

FileList^ FileSystem::CreateFileList()
{
	io::IFileList* l = m_FileSystem->createFileList();
	return FileList::Wrap(l);
}

ReadFile^ FileSystem::CreateLimitReadFile(String^ filename, ReadFile^ alreadyOpenedFile, long areaPosition, long areaSize)
{
	LIME_ASSERT(filename != nullptr);
	LIME_ASSERT(alreadyOpenedFile != nullptr);
	LIME_ASSERT(areaSize >= 0);

	io::IReadFile* f = m_FileSystem->createLimitReadFile(
		Lime::StringToPath(filename),
		LIME_SAFEREF(alreadyOpenedFile, m_ReadFile),
		areaPosition,
		areaSize);

	return ReadFile::Wrap(f);
}

ReadFile^ FileSystem::CreateMemoryReadFile(String^ filename, array<unsigned char>^ content)
{
	LIME_ASSERT(filename != nullptr);
	LIME_ASSERT(content != nullptr);

	int c = content->Length;
	char* m = new char[c];

	for (int i = 0; i < c; i++)
		m[i] = content[i];

	io::IReadFile* f = m_FileSystem->createMemoryReadFile(
		m,
		c,
		Lime::StringToPath(filename),
		true /* allocated m will be deleted automatically on drop() */);

	return ReadFile::Wrap(f);
}

String^ FileSystem::GetFileAbsolutePath(String^ filename)
{
	LIME_ASSERT(filename != nullptr);
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
	LIME_ASSERT(filename != nullptr);
	return gcnew String(m_FileSystem->getFileBasename(Lime::StringToPath(filename), keepExtension).c_str());
}

String^ FileSystem::GetFileBasename(String^ filename)
{
	LIME_ASSERT(filename != nullptr);
	return gcnew String(m_FileSystem->getFileBasename(Lime::StringToPath(filename)).c_str());
}

String^ FileSystem::GetFileDirectory(String^ filename)
{
	LIME_ASSERT(filename != nullptr);
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
	LIME_ASSERT(filename != nullptr);
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

void FileSystem::WorkingDirectory::set(String^ value)
{
	LIME_ASSERT(value != nullptr);

	m_FileSystem->changeWorkingDirectoryTo(Lime::StringToPath(value));
	// we do not report bool result here; if this in future will be completly necessary --
	// we will provide separate "bool ChangeWorkingDirectory(String^)" method
}

String^ FileSystem::ToString()
{
	return String::Format("FileSystem: WorkingDirectory={0}; FileArchiveCount={1}", WorkingDirectory, FileArchiveCount);
}

} // end namespace IO
} // end namespace IrrlichtLime