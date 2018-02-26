//
// skulk@ioc.ninja
//
#pragma once



#include "xMemoryModule.h"



class xPayloadApi
{
private:
	xPayloadApi()
	{
	}

public:
	static xPayloadApi& GetPayloadApi()
	{
		static xPayloadApi s_payloadApi;

		return s_payloadApi;
	}

public:
	// Payload
	X_MEMORY_MODULE_BEGIN(Payload)
		X_MEMORY_MODULE_FUNCTION_0(void, Execute)
	X_MEMORY_MODULE_END(Payload)
};

static xPayloadApi& xGetPayloadApi() { return xPayloadApi::GetPayloadApi(); }



#define X_PAYLOAD_INIT(__Buffer, __Size)	xGetPayloadApi().GetPayload().Load(__Buffer, __Size)

#define X_PAYLOAD_CALL(__Name)				xGetPayloadApi().GetPayload().##__Name
