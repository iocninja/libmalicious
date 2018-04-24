//
// skulk@ioc.ninja
//
#pragma once



#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"

#include "xOsApi.h"
#include "xOsReplacementApi.h"



#ifdef X_USE_OBFUSCATED_API
	#define GetNativeSystemInfo		X_KERNEL32_DYNAMIC_MODULE_CALL(GetNativeSystemInfo)
	#define GetProcessHeap			X_KERNEL32_DYNAMIC_MODULE_CALL(GetProcessHeap)
	#define GetThreadLocale			X_KERNEL32_DYNAMIC_MODULE_CALL(GetThreadLocale)
	#define HeapAlloc				X_KERNEL32_DYNAMIC_MODULE_CALL(HeapAlloc)
	#define HeapFree				X_KERNEL32_DYNAMIC_MODULE_CALL(HeapFree)
	#define IsBadReadPtr			X_KERNEL32_DYNAMIC_MODULE_CALL(IsBadReadPtr)
	#define SetLastError			X_KERNEL32_DYNAMIC_MODULE_CALL(SetLastError)
	#define VirtualAlloc			X_KERNEL32_DYNAMIC_MODULE_CALL(VirtualAlloc)
	#define VirtualFree				X_KERNEL32_DYNAMIC_MODULE_CALL(VirtualFree)
	#define VirtualProtect			X_KERNEL32_DYNAMIC_MODULE_CALL(VirtualProtect)
#endif
