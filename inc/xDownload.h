#pragma once

#include <stdint.h>



bool xDownloadToBuffer(const wchar_t* url, uint8_t** buffer, size_t* size);
