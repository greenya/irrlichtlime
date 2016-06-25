#pragma once

#include "stdafx.h"
#include "StreamReadFileNative.h"
#include "ReadFile.h"

using namespace irr;
using namespace System;
using namespace System::IO;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {
namespace IO {

public ref class StreamReadFile : ReadFile
{
public:

	StreamReadFile(Stream^ stream, String^ filename, bool leaveInnerStreamOpen)
		: m_StreamReadFileNative(initialize(stream, filename, leaveInnerStreamOpen)), ReadFile(m_StreamReadFileNative)
	{
	}

	StreamReadFile(Stream^ stream, String^ filename)
		: m_StreamReadFileNative(initialize(stream, filename, false)), ReadFile(m_StreamReadFileNative)
	{
	}

	StreamReadFile(Stream^ stream)
		: m_StreamReadFileNative(initialize(stream, nullptr, false)), ReadFile(m_StreamReadFileNative)
	{
	}

private:

	StreamReadFileNative* initialize(Stream^ stream, String^ filename, bool leaveInnerStreamOpen);

internal:

	static StreamReadFile^ Wrap(StreamReadFileNative* ref);
	StreamReadFile(StreamReadFileNative* ref);

	StreamReadFileNative* m_StreamReadFileNative;
};

} // end namespace IO
} // end namespace IrrlichtLime