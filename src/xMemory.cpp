//
// skulk@ioc.ninja
//
#include "xMemory.h"

#include "xOsApi.h"



void* xMemoryAlloc(const size_t size)
{
	return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void xMemoryCopy(void* to, const void* from, const size_t size)
{
	memcpy(to, from, size);
}

void xMemoryFree(void* memory)
{
	VirtualFree(memory, 0, MEM_RELEASE);
}

void xMemoryZero(void* memory, const size_t size)
{
	memset(memory, 0, size);
}