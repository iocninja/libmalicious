//
// skulk@ioc.ninja
//
#pragma once



#include <Windows.h>
#include <IPHlpApi.h>
#include <Wininet.h>

#include "xDynamicModule.h"



#if !defined X_USE_OS_API_MEMORY_MODULE && !defined X_USE_OS_API_DYNAMIC_MODULE
	#pragma comment (lib, "Iphlpapi")
	#pragma comment (lib, "Kernel32")
	#pragma comment (lib, "Ole32")
	#pragma comment (lib, "OleAut32")
	#pragma comment (lib, "User32")
	#pragma comment (lib, "Ws2_32")	
#endif



template
<
	typename t_base
>
class xOsApi : public t_base
{
private:
	xOsApi()
	{
	}

public:
	static xOsApi<t_base> GetOsApi()
	{
		static xOsApi<t_base> s_self;

		return s_self;
	}
};



#define X_OS_API_MODULE_BEGIN			X_MEMORY_MODULE_BEGIN_FILE
#define X_OS_API_MODULE_FUNCTION_0		X_MEMORY_MODULE_FUNCTION_0
#define X_OS_API_MODULE_FUNCTION_1		X_MEMORY_MODULE_FUNCTION_1
#define X_OS_API_MODULE_FUNCTION_2		X_MEMORY_MODULE_FUNCTION_2
#define X_OS_API_MODULE_FUNCTION_3		X_MEMORY_MODULE_FUNCTION_3
#define X_OS_API_MODULE_FUNCTION_4		X_MEMORY_MODULE_FUNCTION_4
#define X_OS_API_MODULE_FUNCTION_5		X_MEMORY_MODULE_FUNCTION_5
#define X_OS_API_MODULE_FUNCTION_6		X_MEMORY_MODULE_FUNCTION_6
#define X_OS_API_MODULE_FUNCTION_7		X_MEMORY_MODULE_FUNCTION_7
#define X_OS_API_MODULE_FUNCTION_8		X_MEMORY_MODULE_FUNCTION_8
#define X_OS_API_MODULE_FUNCTION_9		X_MEMORY_MODULE_FUNCTION_9
#define X_OS_API_MODULE_FUNCTION_10		X_MEMORY_MODULE_FUNCTION_10
#define X_OS_API_MODULE_FUNCTION_11		X_MEMORY_MODULE_FUNCTION_11
#define X_OS_API_MODULE_FUNCTION_12		X_MEMORY_MODULE_FUNCTION_12
#define X_OS_API_MODULE_END				X_MEMORY_MODULE_END



#define X_OS_API_TRAITS xOsApiTraitsMemoryModule

#include "xOsApiTraits.h"

typedef xOsApi<xOsApiTraitsMemoryModule> xOsApiMemoryModule;

static xOsApiMemoryModule& xGetOsApiMemoryModule() {return xOsApiMemoryModule::GetOsApi();}



#undef X_OS_API_MODULE_BEGIN
#undef X_OS_API_MODULE_FUNCTION_0
#undef X_OS_API_MODULE_FUNCTION_1
#undef X_OS_API_MODULE_FUNCTION_2
#undef X_OS_API_MODULE_FUNCTION_3
#undef X_OS_API_MODULE_FUNCTION_4
#undef X_OS_API_MODULE_FUNCTION_5
#undef X_OS_API_MODULE_FUNCTION_6
#undef X_OS_API_MODULE_FUNCTION_7
#undef X_OS_API_MODULE_FUNCTION_8
#undef X_OS_API_MODULE_FUNCTION_9
#undef X_OS_API_MODULE_FUNCTION_10
#undef X_OS_API_MODULE_FUNCTION_11
#undef X_OS_API_MODULE_FUNCTION_12
#undef X_OS_API_MODULE_END

#undef X_OS_API_TRAITS



#define X_OS_API_MODULE_BEGIN			X_DYNAMIC_MODULE_BEGIN
#define X_OS_API_MODULE_FUNCTION_0		X_DYNAMIC_MODULE_FUNCTION_0
#define X_OS_API_MODULE_FUNCTION_1		X_DYNAMIC_MODULE_FUNCTION_1
#define X_OS_API_MODULE_FUNCTION_2		X_DYNAMIC_MODULE_FUNCTION_2
#define X_OS_API_MODULE_FUNCTION_3		X_DYNAMIC_MODULE_FUNCTION_3
#define X_OS_API_MODULE_FUNCTION_4		X_DYNAMIC_MODULE_FUNCTION_4
#define X_OS_API_MODULE_FUNCTION_5		X_DYNAMIC_MODULE_FUNCTION_5
#define X_OS_API_MODULE_FUNCTION_6		X_DYNAMIC_MODULE_FUNCTION_6
#define X_OS_API_MODULE_FUNCTION_7		X_DYNAMIC_MODULE_FUNCTION_7
#define X_OS_API_MODULE_FUNCTION_8		X_DYNAMIC_MODULE_FUNCTION_8
#define X_OS_API_MODULE_FUNCTION_9		X_DYNAMIC_MODULE_FUNCTION_9
#define X_OS_API_MODULE_FUNCTION_10		X_DYNAMIC_MODULE_FUNCTION_10
#define X_OS_API_MODULE_FUNCTION_11		X_DYNAMIC_MODULE_FUNCTION_11
#define X_OS_API_MODULE_FUNCTION_12		X_DYNAMIC_MODULE_FUNCTION_12
#define X_OS_API_MODULE_END				X_DYNAMIC_MODULE_END



#define X_OS_API_TRAITS xOsApiTraitsDynamicModule

#include "xOsApiTraits.h"

typedef xOsApi<xOsApiTraitsDynamicModule> xOsApiDynamicModule;

static xOsApiDynamicModule& xGetOsApiDynamicModule() {return xOsApiDynamicModule::GetOsApi();}



#undef X_OS_API_MODULE_BEGIN
#undef X_OS_API_MODULE_FUNCTION_0
#undef X_OS_API_MODULE_FUNCTION_1
#undef X_OS_API_MODULE_FUNCTION_2
#undef X_OS_API_MODULE_FUNCTION_3
#undef X_OS_API_MODULE_FUNCTION_4
#undef X_OS_API_MODULE_FUNCTION_5
#undef X_OS_API_MODULE_FUNCTION_6
#undef X_OS_API_MODULE_FUNCTION_7
#undef X_OS_API_MODULE_FUNCTION_8
#undef X_OS_API_MODULE_FUNCTION_9
#undef X_OS_API_MODULE_FUNCTION_10
#undef X_OS_API_MODULE_FUNCTION_11
#undef X_OS_API_MODULE_FUNCTION_12
#undef X_OS_API_MODULE_END

#undef X_OS_API_TRAITS



#define X_ADVAPI32_MEMORY_MODULE_CALL(__Name)	xGetOsApiMemoryModule().GetAdvapi32().##__Name
#define X_IPHLPAPI_MEMORY_MODULE_CALL(__Name)	xGetOsApiMemoryModule().GetIphlpapi().##__Name
#define X_KERNEL32_MEMORY_MODULE_CALL(__Name)	xGetOsApiMemoryModule().GetKernel32().##__Name
#define X_OLE32_MEMORY_MODULE_CALL(__Name)		xGetOsApiMemoryModule().GetOle32().##__Name
#define X_OLEAUT32_MEMORY_MODULE_CALL(__Name)	xGetOsApiMemoryModule().GetOleAut32().##__Name
#define X_USER32_MEMORY_MODULE_CALL(__Name)		xGetOsApiMemoryModule().GetUser32().##__Name
#define X_WININET_MEMORY_MODULE_CALL(__Name)	xGetOsApiMemoryModule().GetWininet().##__Name
#define X_WS2_32_MEMORY_MODULE_CALL(__Name)		xGetOsApiMemoryModule().GetWs2_32().##__Name

#define X_ADVAPI32_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetAdvapi32().##__Name
#define X_IPHLPAPI_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetIphlpapi().##__Name
#define X_KERNEL32_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetKernel32().##__Name
#define X_OLE32_DYNAMIC_MODULE_CALL(__Name)		xGetOsApiDynamicModule().GetOle32().##__Name
#define X_OLEAUT32_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetOleAut32().##__Name
#define X_USER32_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetUser32().##__Name
#define X_WININET_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetWininet().##__Name
#define X_WS2_32_DYNAMIC_MODULE_CALL(__Name)	xGetOsApiDynamicModule().GetWs2_32().##__Name



#ifdef X_USE_OS_API_MEMORY_MODULE
	#define X_ADVAPI32_CALL		X_ADVAPI32_MEMORY_MODULE_CALL
	#define X_IPHLPAPI_CALL		X_IPHLPAPI_MEMORY_MODULE_CALL
	#define X_KERNEL32_CALL		X_KERNEL32_MEMORY_MODULE_CALL
	#define X_OLE32_CALL		X_OLE32_MEMORY_MODULE_CALL
	#define X_OLEAUT32_CALL		X_OLEAUT32_MEMORY_MODULE_CALL
	#define X_USER32_CALL		X_USER32_MEMORY_MODULE_CALL
	#define X_WININET_CALL		X_WININET_MEMORY_MODULE_CALL
	#define X_WS2_32_CALL		X_WS2_32_MEMORY_MODULE_CALL
#elif X_USE_OS_API_DYNAMIC_MODULE
	#define X_ADVAPI32_CALL		X_ADVAPI32_DYNAMIC_MODULE_CALL
	#define X_IPHLPAPI_CALL		X_IPHLPAPI_DYNAMIC_MODULE_CALL
	#define X_KERNEL32_CALL		X_KERNEL32_DYNAMIC_MODULE_CALL
	#define X_OLE32_CALL		X_OLE32_DYNAMIC_MODULE_CALL
	#define X_OLEAUT32_CALL		X_OLEAUT32_DYNAMIC_MODULE_CALL
	#define X_USER32_CALL		X_USER32_DYNAMIC_MODULE_CALL
	#define X_WININET_CALL		X_WININET_DYNAMIC_MODULE_CALL
	#define X_WS2_32_CALL		X_WS2_32_DYNAMIC_MODULE_CALL
#else
	#define X_ADVAPI32_CALL(__Name)	__Name
	#define X_IPHLPAPI_CALL(__Name)	__Name
	#define X_KERNEL32_CALL(__Name)	__Name
	#define X_OLE32_CALL(__Name)	__Name
	#define X_OLEAUT32_CALL(__Name)	__Name
	#define X_USER32_CALL(__Name)	__Name
	#define X_WININET_CALL(__Name)	__Name
	#define X_WS2_32_CALL(__Name)	__Name
#endif