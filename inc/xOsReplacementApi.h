//
// skulk@ioc.ninja
//
#pragma once

#include <Windows.h>



void* xOsReplacementApiGetProcAddress(HANDLE module, const char* name);

HMODULE xOsReplacementApiLoadLibraryW(const wchar_t* name);

HMODULE xOsReplacementApiLoadLibraryA(const char* name);

bool xOsReplacementApiFreeLibrary(HMODULE module);
