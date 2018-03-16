#include "stdafx.h"
#include "MemoryOutputStream.h"

MemoryOutputStream::MemoryOutputStream(std::vector<uint8_t>& memory)
	: m_memory(memory)
{
}

void MemoryOutputStream::WriteByte(uint8_t data)
{
	WriteBlock(std::addressof(data), 1u);
}

void MemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0u; i < size; ++i)
	{
		m_memory.push_back(*source++);
	}
}
