//
// skulk@ioc.ninja
//
#include "xDynamicModule.h"



xDynamicModule::xDynamicModule()
{
	m_module = NULL;
}



xDynamicModule::xDynamicModule(const wchar_t* fileName) : m_module(NULL)
{
	m_module = LoadLibraryW(fileName);
}



xDynamicModule::xDynamicModule(HMODULE module) : m_module(module)
{
}



xDynamicModule::~xDynamicModule()
{
	if (m_module)
	{
		FreeLibrary(m_module);
	}
}



HMODULE xDynamicModule::GetModule()
{
	return m_module;
}



void* xDynamicModule::GetFunction(const char* name)
{
	return X_LIB_MALICIOUS_CALL(xOsReplacementApiGetProcAddress)(GetModule(), name);
}
