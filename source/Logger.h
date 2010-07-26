#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

public ref class Logger : ReferenceCounted
{
public:

	void Log(String^ text, String^ hint, IrrlichtLime::LogLevel level);
	void Log(String^ text, IrrlichtLime::LogLevel level);
	void Log(String^ text);

	property IrrlichtLime::LogLevel LogLevel { IrrlichtLime::LogLevel get(); void set(IrrlichtLime::LogLevel value); }

	virtual String^ ToString() override;

internal:

	static Logger^ Wrap(irr::ILogger* ref);
	Logger(irr::ILogger* ref);

	irr::ILogger* m_Logger;
};

} // end namespace IrrlichtLime