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

	bool MoveFileArchive(UInt32 sourceIndex, Int32 relative);
	bool RemoveFileArchive(UInt32 index);
	bool RemoveFileArchive(String^ filename);

	property UInt32 FileArchiveCount { UInt32 get(); }
	property String^ WorkingDirectory { String^ get(); }

internal:

	FileSystem(io::IFileSystem* fileSystem);

	io::IFileSystem* m_FileSystem;
};

} // end namespace IO
} // end namespace IrrlichtLime