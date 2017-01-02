#pragma once

#include <vcclr.h> // for gcroot
#include "stdafx.h"

using namespace irr;
using namespace System;
using namespace System::IO;

namespace IrrlichtLime {
namespace IO {

class StreamReadFileNative : public io::IReadFile
{
public:

	StreamReadFileNative(Stream^ stream, String^ filename, bool leaveInnerStreamOpen)
	{
		this->innerStream = stream;

		if (filename != nullptr)
			this->filename = Lime::StringToPath(filename);
		else
			this->filename = "";
		
		this->leaveInnerStreamOpen = leaveInnerStreamOpen;
		this->readBuffer = nullptr;
	}

	virtual ~StreamReadFileNative()
	{
		if (isOpen() && !leaveInnerStreamOpen)
		{
			Stream^ stream = innerStream;	//unbox
			delete stream;	//call Dispose()
			innerStream = nullptr;
		}
	}

	bool isOpen() const
	{
		return (static_cast<Stream^>(innerStream) != nullptr);
	}

	virtual size_t read(void* buffer, size_t sizeToRead)
	{
		//static casts to make sure it is unboxed from gcroot

		if (!isOpen())
			return 0;

		if (sizeToRead > Int32::MaxValue)	//.net stream read method takes an int parameter
			sizeToRead = Int32::MaxValue;

		if (static_cast<cli::array<unsigned char>^>(readBuffer) == nullptr || readBuffer->Length < (int)sizeToRead)	//make sure read buffer is big enough
			readBuffer = gcnew cli::array<unsigned char>(sizeToRead);

		int readCount = innerStream->Read(readBuffer, 0, (int)sizeToRead);	//cast is safe
		if (readCount == 0)
			return 0;
	

		pin_ptr<unsigned char> readBufferPtr = &static_cast<cli::array<unsigned char>^>(readBuffer)[0];
		memcpy(buffer, readBufferPtr, readCount);	//copy into buffer
		return readCount;
	}

	virtual bool seek(long finalPos, bool relativeMovement)
	{		
		if (!isOpen())
			return false;

		long long resultPosition;
		if (relativeMovement)
			resultPosition = innerStream->Position + finalPos;
		else
			resultPosition = finalPos;
			
		long long actualResultPosition = innerStream->Seek(finalPos, SeekOrigin::Begin);
		return (resultPosition == actualResultPosition);	//success, if we were able to actually seek to the given position
	}

	virtual long getSize() const
	{
		if (!isOpen())
			return 0;

		//long is actually an 32 bit int
		long long size = innerStream->Length;
		if (size > Int32::MaxValue)
			return Int32::MaxValue;
		else
			return (long)size;
	}

	virtual long getPos() const
	{
		if (!isOpen())
			return 0;

		return (long)innerStream->Position;
	}

	virtual const io::path& getFileName() const
	{
		return filename;
	}

private:

	io::path filename;
	gcroot<Stream^> innerStream;
	bool leaveInnerStreamOpen;
	gcroot<cli::array<unsigned char>^> readBuffer;
};

} // end namespace IO
} // end namespace IrrlichtLime