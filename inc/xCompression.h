//
// skulk@ioc.ninja
//
#pragma once

#include <stdint.h>



bool xCompressionCompress(const uint8_t* data, const uint32_t dataSize, uint8_t** compressed, uint32_t* compressedSize);

bool xCompressionDecompress(const uint8_t* compressed, const uint32_t compressedSize, uint8_t** decompressed, uint32_t* decompressedSize);
