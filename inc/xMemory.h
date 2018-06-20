//
// skulk@ioc.ninja
//
#pragma once



#include <stdint.h>



void* xMemoryAlloc(const size_t size);

void* xMemoryClone(const void* memory, const size_t size);

void xMemoryCopy(void* to, const void* from, const size_t size);

void xMemoryFree(void* memory);

void xMemoryZero(void* memory, const size_t size);
