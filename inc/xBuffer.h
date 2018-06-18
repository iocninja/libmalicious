#pragma once

#include <stdint.h>



class xBuffer
{
public:
	xBuffer();
	~xBuffer();

public:
	bool Add(const uint8_t* buffer, const size_t size);
	bool Copy(uint8_t** buffer, size_t* size);
	size_t GetSize();
	void Reset();

private:
	uint8_t* m_buffer;
	size_t m_size;
};
