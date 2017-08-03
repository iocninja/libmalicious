#include "xMemoryModule.h"

#include "MemoryModule.h"

#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"
#include "xOsApi.h"



xMemoryModule::xMemoryModule()
{
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



bool xMemoryModule::Load(const void* buffer, const size_t size)
{
	Free();

	return !!(m_module = X_LIB_MALICIOUS_EXTERNAL_CALL(MemoryLoadLibrary)(buffer, size));
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