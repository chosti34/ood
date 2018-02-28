#pragma once
#include "IInputDataStream.h"
#include <vector>

class MemoryInputStream : public IInputDataStream
{
public:
	MemoryInputStream(std::vector<uint8_t> && data)
		: m_data(std::move(data))
		, m_offset(0)
	{
	}

	bool IsEOF() const override
	{
		return m_offset >= m_data.size();
	}

	uint8_t ReadByte() override
	{
		uint8_t byte;
		if (ReadBlock(std::addressof(byte), 1) == 0u)
		{
			throw std::ios_base::failure("failed to read byte from memory stream");
		}
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		std::streamsize read = 0u;
		uint8_t* buffer = reinterpret_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0u; i < size; ++i)
		{
			if (IsEOF())
			{
				return read;
			}
			*buffer++ = m_data[m_offset++];
			++read;
		}
		return read;
	}

private:
	std::vector<uint8_t> m_data;
	size_t m_offset;
};
