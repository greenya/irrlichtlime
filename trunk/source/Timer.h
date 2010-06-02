#pragma once

#include "stdafx.h"
#include "ReferenceCounted.h"

using namespace irr;
using namespace System;
using namespace IrrlichtLime::Core;

namespace IrrlichtLime {

public ref class Timer : ReferenceCounted
{
public:

	void Start();
	void Stop();
	void Tick();

	property bool IsStopped { bool get(); }
	property unsigned int RealTime { unsigned int get(); }
	property float Speed { float get(); void set(float value); }
	property unsigned int Time { unsigned int get(); void set(unsigned int value); }

	virtual String^ ToString() override;

internal:

	static Timer^ Wrap(irr::ITimer* ref);
	Timer(irr::ITimer* ref);

	irr::ITimer* m_Timer;
};

} // end namespace IrrlichtLime