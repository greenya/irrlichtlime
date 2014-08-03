#pragma once

using namespace irr;
using namespace System;
using namespace System::IO;

namespace IrrlichtLime {
namespace IO {

ref class ReadFile;

public ref class ReadFileStream : Stream
{
public:

	ReadFileStream();
	ReadFileStream(ReadFile^ readFile);

	//Properties
	property bool CanRead { virtual bool get() override; }
	property bool CanWrite { virtual bool get() override; }
	property bool CanSeek { virtual bool get() override; }
	property long long Length { virtual long long get() override; }
	property long long Position { virtual long long get() override; virtual void set(long long value) override; }
	property ReadFile^ File { ReadFile^ get(); void set(ReadFile^ value); }

#pragma warning (push)
#pragma warning (disable: 4100)
	virtual void SetLength(long long value) override { }	//Not implemented
#pragma warning (pop)
	virtual long long Seek(long long offset, SeekOrigin origin) override;

	virtual int Read(array<Byte>^ buffer, int offset, int count) override;
#pragma warning (push)
#pragma warning (disable: 4100)
	virtual void Write(array<Byte>^ buffer, int offset, int count) override { throw gcnew NotSupportedException(); }
#pragma warning (pop)
	virtual void Flush() override { }	//Not implemented

	~ReadFileStream()
	{
		this->!ReadFileStream();
	}

	!ReadFileStream()
	{
		if (m_ReadFile != nullptr)
		{
			m_ReadFile->drop();
			m_ReadFile = nullptr;
		}
	}

private:

	io::IReadFile* m_ReadFile;

};

} // end namespace IO
} // end namespace IrrlichtLime