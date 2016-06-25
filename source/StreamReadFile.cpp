#include "stdafx.h"
#include "StreamReadFile.h"
#include "StreamReadFileNative.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace IO {

StreamReadFile^ StreamReadFile::Wrap(StreamReadFileNative* ref)
{
	if (ref == nullptr)
		return nullptr;

	return gcnew StreamReadFile(ref);
}

StreamReadFile::StreamReadFile(StreamReadFileNative* ref)
	: ReadFile(ref)
{
	m_StreamReadFileNative = ref;
}

StreamReadFileNative* StreamReadFile::initialize(Stream^ stream, String^ filename, bool leaveInnerStreamOpen)
{
	if (stream == nullptr)
		throw gcnew ArgumentException("stream", "The inner stream must not be null.");
	if (stream->CanRead == false)
		throw gcnew ArgumentException("stream", "The inner stream must be able to read.");
	if (stream->CanSeek == false)
		throw gcnew ArgumentException("stream", "The inner stream must be able to seek.");

	return new StreamReadFileNative(stream, filename, leaveInnerStreamOpen);
}

} // end namespace IO
} // end namespace IrrlichtLime