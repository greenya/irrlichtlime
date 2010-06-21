#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

public ref class FileList : ReferenceCounted
{
public:

	unsigned int AddFile(String^ fullPath, unsigned int size, bool isDirectory, unsigned int id);
	unsigned int AddFile(String^ fullPath, unsigned int size, bool isDirectory);

	int FindFile(String^ filename, bool isDirectory);
	int FindFile(String^ filename);

	unsigned int GetFileID(unsigned int index);
	String^ GetFileName(unsigned int index);
	unsigned int GetFileSize(unsigned int index);
	String^ GetFullFileName(unsigned int index);

	bool IsDirectory(unsigned int index);

	void Sort();

	property unsigned int Count { unsigned int get(); }
	property String^ Path { String^ get(); }

internal:

	static FileList^ Wrap(io::IFileList* ref);
	FileList(io::IFileList* ref);

	io::IFileList* m_FileList;
};

} // end namespace IO
} // end namespace IrrlichtLime