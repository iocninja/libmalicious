//
// skulk@ioc.ninja
//
#include "xCompression.h"

#include "xLibMaliciousApi.h"
#include "xLibMaliciousExternalApi.h"



bool xCompressionCompress(const uint8_t* data, const uint32_t dataSize, uint8_t** compressed, uint32_t* compressedSize)
{
	if (!data || !dataSize || !compressed || !compressedSize)
	{
		return false;
	}

	bool result = false;

	mz_ulong size = X_LIB_MALICIOUS_EXTERNAL_CALL(mz_compressBound)(dataSize);

	uint8_t* buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(size);

	if (buffer)
	{
		if (X_LIB_MALICIOUS_EXTERNAL_CALL(mz_compress2)(buffer, &size, data, dataSize, MZ_BEST_COMPRESSION) == MZ_OK)
		{
			if (size)
			{
				uint8_t* out = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryClone)(buffer, size);

				if (out)
				{
					*compressed = out;

					*compressedSize = size;

					result = true;
				}
			}
		}

		X_LIB_MALICIOUS_CALL(xMemoryFree)(buffer);
	}

	return result;
}

bool xCompressionDecompress(const uint8_t* compressed, const uint32_t compressedSize, uint8_t** decompressed, uint32_t* decompressedSize)
{
	if (!compressed || !compressedSize || !decompressed || !decompressedSize)
	{
		return false;
	}

	bool result = false;

	mz_ulong size = compressedSize;

	uint8_t* buffer = NULL;

	int r = MZ_OK;

	do 
	{
		size *= 2;

		if (buffer)
		{
			X_LIB_MALICIOUS_CALL(xMemoryFree)(buffer);
		}

		if (!(buffer = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(size)))
		{
			return false;
		}
	}
	while ((r = X_LIB_MALICIOUS_EXTERNAL_CALL(mz_uncompress)(buffer, &size, compressed, compressedSize)) == MZ_BUF_ERROR);

	if (r == MZ_OK)
	{
		uint8_t* out = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryClone)(buffer, size);

		if (out)
		{
			*decompressed = out;

			*decompressedSize = size;

			result = true;
		}
	}

	return result;
}

