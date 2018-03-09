#pragma once
#include "IOutputDataStream.h"
#include <vector>

class MemoryOutputStream : public IOutputDataStream
{
public:
	MemoryOutputStream()
		: m_memory()
	{
	}

	MemoryOutputStream(std::vector<uint8_t> && memory)
		: m_memory(std::move(memory))
	{
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(std::addressof(data), 1u);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0u; i < size; ++i)
		{
			m_memory.push_back(*source++);
		}
	}

private:
	std::vector<uint8_t> m_memory;
};
