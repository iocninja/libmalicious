#pragma once



#include <stdint.h>



bool xConversionHexStringToByte(const char* s, uint8_t** buffer, uint32_t* bufferSize);

bool xConversionBase64Encode(const uint8_t* data, const size_t dataSize, char** output, size_t* outputSize);

bool xConversionBase64Decode(const char* data, const size_t dataSize, uint8_t** output, size_t* outputSize);
