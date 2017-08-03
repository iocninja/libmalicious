#include "xCrash.h"

#include "xLibMaliciousApi.h"
#include "xOsApi.h"



void xCrashAccessViolation()
{
	*((uint32_t*) NULL) = 0xdeadc0de;
}



void xCrashDivideByZero()
{
	volatile uint32_t divisor = 0;

	uint32_t i = 1 / divisor;
}



void xCrashFunctionPointer()
{
	((void(*)())0)();
}



void xCrashIfDebugger()
{
	if (X_LIB_MALICIOUS_CALL(xDebuggerDetectionIsPresent)())
	{
#ifndef _DEBUG
		X_LIB_MALICIOUS_CALL(xCrashRandom)();
#endif
	}
}



class xCrashBase;

void xCrashBaseFunction(xCrashBase* base);

class xCrashBase
{
public:
	virtual void Method() = 0;

	xCrashBase() 
	{
		xCrashBaseFunction(this);
	}
};

class xCrashDerived : xCrashBase
{
	virtual void Method()
	{
	}
};

void xCrashBaseFunction(xCrashBase* base)
{
	if (base)
	{
		base->Method();
	}
}

void xCrashPureVirtual()
{
	xCrashDerived  pvfc;
}



void xCrashRandom()
{
	switch (X_LIB_MALICIOUS_CALL(xRandomNumber)(0, 5))
	{
		case 0:
		{
			X_LIB_MALICIOUS_CALL(xCrashAccessViolation)();
		}
		case 1:
		{
			X_LIB_MALICIOUS_CALL(xCrashDivideByZero)();
		}
		case 2:
		{
			X_LIB_MALICIOUS_CALL(xCrashStackOverflow)();
		}
		case 3:
		{
			X_LIB_MALICIOUS_CALL(xCrashFunctionPointer)();
		}
		case 4:
		{
			X_LIB_MALICIOUS_CALL(xCrashPureVirtual)();
		}
		case 5:
		{
			X_KERNEL32_CALL(ExitProcess)(0);
		}
		default:
		{
			// ?
			return;
		}
	}
}



void xCrashStackOverflow()
{
	while (true)
	{
#pragma warning(push)
#pragma warning(disable: 4101)
		uint8_t buffer[4096];
#pragma warning(pop) 

		X_LIB_MALICIOUS_CALL(xCrashStackOverflow());
	}
}
