#pragma once
#include "IOutputDataStream.h"
#include <memory>
#include <boost/optional.hpp>

class RLECompressOutputDataStreamDecorator : public IOutputDataStream
{
	struct ByteChunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	RLECompressOutputDataStreamDecorator(std::unique_ptr<IOutputDataStream> && output)
		: m_output(std::move(output))
	{
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(&data, 1);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		boost::optional<ByteChunk> chunk = boost::none;
		const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0u; i < size; ++i)
		{
			uint8_t byte = *source++;
			if (!chunk)
			{
				chunk = ByteChunk{ 1u, byte };
			}
			else if (chunk->byte == byte && chunk->count < 0xFF)
			{
				++chunk->count;
			}
			else
			{
				m_output->WriteBlock(chunk.get_ptr(), 2u);
				chunk = ByteChunk{ 1u, byte };
			}
		}
		// We can have unhandled byte chunk at the end
		if (chunk)
		{
			m_output->WriteBlock(chunk.get_ptr(), 2u);
		}
	}

private:
	std::unique_ptr<IOutputDataStream> m_output;
};
