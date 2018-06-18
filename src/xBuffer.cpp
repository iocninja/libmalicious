#pragma once

#include "xBuffer.h"
#include "xMemory.h"



xBuffer::xBuffer()
{
	m_buffer = NULL;

	m_size = 0;
}

xBuffer::~xBuffer()
{
	Reset();
}

bool xBuffer::Add(const uint8_t* buffer, const size_t size)
{
	if (!buffer || !size)
	{
		return false;
	}

	const size_t required = m_size + size;

	uint8_t* temp = (uint8_t*) xMemoryAlloc(required);

	if (!temp)
	{
		return false;
	}

	if (m_buffer && m_size)
	{
		xMemoryCopy(temp, m_buffer, m_size);
	}

	xMemoryCopy(temp + m_size, buffer, size);

	Reset();

	m_buffer = temp;

	m_size = required;

	return true;
}

bool xBuffer::Copy(uint8_t** buffer, size_t* size)
{
	if (!buffer || !size)
	{
		return false;
	}

	uint8_t* temp = (uint8_t* ) xMemoryClone(m_buffer, m_size);

	if (!temp)
	{
		return false;
	}

	*buffer = temp;

	*size = m_size;

	return true;
}

size_t xBuffer::GetSize()
{
	return m_size;
}

void xBuffer::Reset()
{
	if (m_buffer)
	{
		xMemoryFree(m_buffer);

		m_buffer = NULL;
	}

	m_size = 0;
}
