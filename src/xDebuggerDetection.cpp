#include "xDebuggerDetection.h"

#include <Windows.h>

#include "xLibMaliciousApi.h"
#include "xOsApi.h"



extern "C" void __x_int2d();

bool xDebuggerDetectionInt2d()
{
	__try
	{
		__x_int2d();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}



bool xDebuggerDetectionIsPresent()
{
#if defined _DEBUG
	return false;
#else
	return X_LIB_MALICIOUS_CALL(xDebuggerDetectionInt2d)();
#endif
}
