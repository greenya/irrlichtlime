#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

ref class FileArchive;
ref class FileList;
ref class ReadFile;

public ref class FileSystem : ReferenceCounted
{
public:

	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType, String^ password);
	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType);
	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths);
	bool AddFileArchive(String^ filename, bool ignoreCase);
	bool AddFileArchive(String^ filename);

	ReadFile^ CreateReadFile(String^ filename);

	FileList^ CreateEmptyFileList(String^ path, bool ignoreCase, bool ignorePaths);
	FileList^ CreateFileList();

	ReadFile^ CreateLimitReadFile(String^ filename, ReadFile^ alreadyOpenedFile, long areaPosition, long areaSize);
	ReadFile^ CreateMemoryReadFile(String^ filename, array<unsigned char>^ content);

	String^ GetFileAbsolutePath(String^ filename);
	FileArchive^ GetFileArchive(int index);
	String^ GetFileBasename(String^ filename, bool keepExtension);
	String^ GetFileBasename(String^ filename);
	String^ GetFileDirectory(String^ filename);

	bool MoveFileArchive(int index, int relative);
	bool RemoveFileArchive(int index);
	bool RemoveFileArchive(String^ filename);

	FileSystemType SetFileSystemType(FileSystemType newType);

	property int FileArchiveCount { int get(); }
	property String^ WorkingDirectory { String^ get(); void set(String^ value); }

	virtual String^ ToString() override;

internal:

	static FileSystem^ Wrap(io::IFileSystem* ref);
	FileSystem(io::IFileSystem* ref);

	io::IFileSystem* m_FileSystem;
};

} // end namespace IO
} // end namespace IrrlichtLime