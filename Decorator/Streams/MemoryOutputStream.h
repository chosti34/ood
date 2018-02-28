#pragma once
#include "IOutputDataStream.h"
#include <vector>

class MemoryOutputStream : public IOutputDataStream
{
public:
	MemoryOutputStream()
		: m_data()
	{
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(std::addressof(data), 1u);
	}

	void WriteBlock(const void * srcData, std::streamsize size) override
	{
		const uint8_t* buffer = reinterpret_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			m_data.push_back(*buffer++);
		}
	}

private:
	std::vector<uint8_t> m_data;
};
