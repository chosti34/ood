#include "stdafx.h"
#include "MemoryInputStream.h"

MemoryInputStream::MemoryInputStream(std::vector<uint8_t> && memory)
	: m_memory(std::move(memory))
	, m_offset(0)
{
}

bool MemoryInputStream::IsEOF() const noexcept
{
	return m_offset >= m_memory.size();
}

uint8_t MemoryInputStream::ReadByte()
{
	uint8_t byte;
	if (ReadBlock(std::addressof(byte), 1) == 0u)
	{
		throw std::ios_base::failure("failed to read byte from memory input stream");
	}
	return byte;
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	std::streamsize readBytesCount = 0u;
	uint8_t* destination = reinterpret_cast<uint8_t*>(dstBuffer);
	for (std::streamsize i = 0u; i < size; ++i)
	{
		if (IsEOF())
		{
			return readBytesCount;
		}
		*destination++ = m_memory[m_offset++];
		++readBytesCount;
	}
	return readBytesCount;
}
