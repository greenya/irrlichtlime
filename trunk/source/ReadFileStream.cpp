#include "stdafx.h"
#include "ReadFileStream.h"
#include "IReadFile.h"
#include "ReadFile.h"

using namespace irr;
using namespace System;
using namespace System::IO;

namespace IrrlichtLime {
namespace IO {

ReadFileStream::ReadFileStream()
{
	m_ReadFile = nullptr;
}

ReadFileStream::ReadFileStream(ReadFile^ readFile)
{
	m_ReadFile = LIME_SAFEREF(readFile, m_ReadFile);
	if (m_ReadFile != nullptr)
		m_ReadFile->grab();
}

bool ReadFileStream::CanRead::get()
{
	if (m_ReadFile == nullptr)
		return false;
	return m_ReadFile->getPos() < m_ReadFile->getSize();
}

bool ReadFileStream::CanWrite::get()
{
	return false;
}

bool ReadFileStream::CanSeek::get()
{
	if (m_ReadFile == nullptr)
		return false;
	return true;
}

long long ReadFileStream::Length::get()
{
	if (m_ReadFile == nullptr)
		throw gcnew InvalidOperationException("File is null!");
	return m_ReadFile->getSize();
}

long long ReadFileStream::Position::get()
{
	if (m_ReadFile == nullptr)
		throw gcnew InvalidOperationException("File is null!");
	return m_ReadFile->getPos();
}

void ReadFileStream::Position::set(long long value)
{
	if (m_ReadFile == nullptr)
		throw gcnew InvalidOperationException("File is null!");
	m_ReadFile->seek(value);
}

ReadFile^ ReadFileStream::File::get()
{
	return ReadFile::Wrap(m_ReadFile);
}

void ReadFileStream::File::set(ReadFile^ value)
{
	if (m_ReadFile != nullptr)
		m_ReadFile->drop();
	m_ReadFile = LIME_SAFEREF(value, m_ReadFile);
	if (m_ReadFile != nullptr)
		m_ReadFile->grab();
}

long long ReadFileStream::Seek(long long offset, SeekOrigin origin)
{
	if (m_ReadFile == nullptr)
		throw gcnew InvalidOperationException("File is null!");
	switch (origin)
    {
	case SeekOrigin::Begin:
		m_ReadFile->seek((int)offset);
		break;
	case SeekOrigin::Current:
		m_ReadFile->seek((int)offset, true);
		break;
	case SeekOrigin::End:
		m_ReadFile->seek((int)(offset + (long)m_ReadFile->getSize()));
		break;
    }
    return Position;
}

int ReadFileStream::Read(array<Byte>^ buffer, int offset, int count)
{
	if (m_ReadFile == nullptr)
		throw gcnew InvalidOperationException("File is null!");

	if (buffer == nullptr)
		throw gcnew ArgumentNullException("buffer");

	if (Position == Length || count + offset > buffer->Length)
		return 0;

	pin_ptr<Byte> bufferPtr = &buffer[0];
	Byte* offsettedPtr = &bufferPtr[offset];
	int s = (int)m_ReadFile->read(offsettedPtr, count);	//cast is safe, because count is int too
	return s;
}

} // end namespace IO
} // end namespace IrrlichtLime
