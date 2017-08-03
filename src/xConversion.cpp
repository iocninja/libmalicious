#include "xConversion.h"

#include <stdio.h>
#include <string.h>

#include "xLibMaliciousApi.h"



bool xConversionHexStringToByte(const char* s, uint8_t** buffer, uint32_t* bufferSize)
{
	if (!s || !buffer || !bufferSize)
	{
		return false;
	}

	const size_t length = strlen(s);

	uint8_t* temp = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(length / 2);

	if (!temp)
	{
		return false;
	}

	for (uint32_t i = 0; i < length; i++)
	{
		sscanf(s, "%2hhx", &temp[i]);

		s += 2;
	}

	*buffer = temp;

	*bufferSize = (uint32_t) length / 2;

	return true;
}



static const char g_encodingTable[] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};



bool xConversionBase64Encode(const uint8_t* data, const size_t dataSize, char** output, size_t* outputSize)
{
	if (!data || !dataSize || !output || !outputSize)
	{
		return false;
	}

	const size_t size = 4 * ((dataSize + 2) / 3);

	char* encodedData = (char*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(size);

	if (!encodedData)
	{
		return false;
	}

	for (uint32_t i = 0, j = 0; i < dataSize;)
	{
		uint32_t octet1 = i < dataSize ? (unsigned char) data[i++] : 0;

		uint32_t octet2 = i < dataSize ? (unsigned char) data[i++] : 0;
		
		uint32_t octet3 = i < dataSize ? (unsigned char) data[i++] : 0;

		uint32_t triple = (octet1 << 0x10) + (octet2 << 0x08) + octet3;

		encodedData[j++] = g_encodingTable[(triple >> 3 * 6) & 0x3F];
		
		encodedData[j++] = g_encodingTable[(triple >> 2 * 6) & 0x3F];
		
		encodedData[j++] = g_encodingTable[(triple >> 1 * 6) & 0x3F];
		
		encodedData[j++] = g_encodingTable[(triple >> 0 * 6) & 0x3F];
	}

	const int modTable[] = {0, 2, 1};

	for (int i = 0; i < modTable[dataSize % 3]; i++)
	{
		encodedData[size - 1 - i] = '=';
	}

	*outputSize = size;

	*output = encodedData;

	return true;
}


bool xConversionBase64Decode(const char* data, const size_t dataSize, uint8_t** output, size_t* outputSize)
{
	if (!data || !dataSize || !output || !outputSize)
	{
		return false;
	}

	char decodingTable[256];

	for (int i = 0; i < 64; i++)
	{
		decodingTable[(unsigned char) g_encodingTable[i]] = i;
	}

	if (dataSize % 4 != 0)
	{
		return false;
	}

	size_t size = dataSize / 4 * 3;

	if (data[dataSize - 1] == '=') (size)--;

	if (data[dataSize - 2] == '=') (size)--;

	uint8_t* decodedData = (uint8_t*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(size);

	if (!decodedData)
	{
		return false;
	}

	for (uint32_t i = 0, j = 0; i < dataSize;)
	{
		uint32_t sextet1 = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];

		uint32_t sextet2 = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];

		uint32_t sextet3 = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];

		uint32_t sextet4 = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];

		uint32_t triple = (sextet1 << 3 * 6) + (sextet2 << 2 * 6) + (sextet3 << 1 * 6) + (sextet4 << 0 * 6);

		if (j < size)
		{
			decodedData[j++] = (triple >> 2 * 8) & 0xff;
		}

		if (j < size)
		{
			decodedData[j++] = (triple >> 1 * 8) & 0xff;
		}

		if (j < size)
		{
			decodedData[j++] = (triple >> 0 * 8) & 0xff;
		}
	}

	*outputSize = size;

	*output = decodedData;

	return true;
}
