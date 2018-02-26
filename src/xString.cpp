//
// skulk@ioc.ninja
//
#include "xString.h"

#include <string.h>

#include "xMemory.h"



wchar_t* xStringAppend(const wchar_t* s1, const wchar_t* s2)
{
	if (s1 && s2)
	{
		const size_t size = wcslen(s1) + wcslen(s2) + sizeof(wchar_t);

		wchar_t* result = (wchar_t*) xMemoryAlloc(size);

		if (result)
		{
			wcscat(result, s1);

			wcscat(result, s2);

			return result;
		}
	}

	return NULL;
}
