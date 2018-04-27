//
// skulk@ioc.ninja
//
#pragma once


#include "xStaticModule.h"

#include "aes256.h"
#include "MemoryModule.h"
#include "miniz.h"



class xLibMaliciousExternalApi
{
private:
	xLibMaliciousExternalApi()
	{
	}

public:
	static xLibMaliciousExternalApi& GetLibMaliciousExternalApi()
	{
		static xLibMaliciousExternalApi s_libMaliciousExternalApi;

		return s_libMaliciousExternalApi;
	}

public:
	// libmalicious external
	X_STATIC_MODULE_BEGIN(LibMaliciousExternal)
		// aes256
		X_STATIC_MODULE_FUNCTION_1(void, aes256_done, aes256_context*)
		X_STATIC_MODULE_FUNCTION_2(void, aes256_encrypt_ecb, aes256_context*, uint8_t*)
		X_STATIC_MODULE_FUNCTION_2(void, aes256_decrypt_ecb, aes256_context*, uint8_t*)
		X_STATIC_MODULE_FUNCTION_2(void, aes256_init, aes256_context*, uint8_t*)

		// MemoryModule
		X_STATIC_MODULE_FUNCTION_1(int, MemoryCallEntryPoint, HMEMORYMODULE)
		X_STATIC_MODULE_FUNCTION_5(LPVOID, MemoryDefaultAlloc, LPVOID, SIZE_T, DWORD, DWORD, LPVOID)
		X_STATIC_MODULE_FUNCTION_4(BOOL, MemoryDefaultFree, LPVOID, SIZE_T, DWORD, LPVOID)
		X_STATIC_MODULE_FUNCTION_2(void, MemoryDefaultFreeLibrary, HCUSTOMMODULE, LPVOID)
		X_STATIC_MODULE_FUNCTION_3(int, MemoryDefaultGetProcAddress, HCUSTOMMODULE, LPCSTR, LPVOID)
		X_STATIC_MODULE_FUNCTION_2(HCUSTOMMODULE, MemoryDefaultLoadLibrary, LPCSTR, LPVOID)
		X_STATIC_MODULE_FUNCTION_1(void, MemoryFreeLibrary, HMEMORYMODULE)
		X_STATIC_MODULE_FUNCTION_2(FARPROC, MemoryGetProcAddress, HMEMORYMODULE, const char*)
		X_STATIC_MODULE_FUNCTION_2(HMEMORYMODULE, MemoryLoadLibrary, const void*, size_t)
		X_STATIC_MODULE_FUNCTION_8(HMEMORYMODULE, MemoryLoadLibraryEx, const void*, size_t, CustomAllocFunc, CustomFreeFunc, CustomLoadLibraryFunc, CustomGetProcAddressFunc, CustomFreeLibraryFunc, void*)

		// miniz
		X_STATIC_MODULE_FUNCTION_1(mz_ulong, mz_compressBound, mz_ulong)
		X_STATIC_MODULE_FUNCTION_5(int, mz_compress2, unsigned char*, mz_ulong*, const unsigned char*, mz_ulong, int)
		X_STATIC_MODULE_FUNCTION_4(int, mz_uncompress, unsigned char*, mz_ulong*, const unsigned char*, mz_ulong)

	X_STATIC_MODULE_END(LibMaliciousExternal)
};

static xLibMaliciousExternalApi& xGetLibMaliciousExternalApi() { return xLibMaliciousExternalApi::GetLibMaliciousExternalApi(); }



#ifdef X_USE_LIB_MALICIOUS_EXTERNAL_API
	#define X_LIB_MALICIOUS_EXTERNAL_CALL(__Name)	xGetLibMaliciousExternalApi().GetLibMaliciousExternal().##__Name
#else
	#define X_LIB_MALICIOUS_EXTERNAL_CALL(__Name)	__Name
#endif

