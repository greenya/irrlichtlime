#pragma once

#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

public ref class FileSystem
{
public:

	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType, String^ password);
	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths, FileArchiveType archiveType);
	bool AddFileArchive(String^ filename, bool ignoreCase, bool ignorePaths);
	bool AddFileArchive(String^ filename, bool ignoreCase);
	bool AddFileArchive(String^ filename);

	bool ChangeWorkingDirectory(String^ newDirectory);

	String^ GetFileAbsolutePath(String^ filename);
	String^ GetFileBasename(String^ filename, bool keepExtension);
	String^ GetFileBasename(String^ filename);
	String^ GetFileDirectory(String^ filename);

	bool MoveFileArchive(unsigned int sourceIndex, int relative);
	bool RemoveFileArchive(unsigned int index);
	bool RemoveFileArchive(String^ filename);

	property unsigned int FileArchiveCount { unsigned int get(); }
	property String^ WorkingDirectory { String^ get(); }

internal:

	FileSystem(io::IFileSystem* fileSystem);

	io::IFileSystem* m_FileSystem;
};

} // end namespace IO
} // end namespace IrrlichtLime