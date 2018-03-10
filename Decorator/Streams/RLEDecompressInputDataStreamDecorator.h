#pragma once
#include "IInputDataStream.h"
#include <memory>
#include <deque>

class RLEDecompressInputDataStreamDecorator : public IInputDataStream
{
	struct ByteChunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	RLEDecompressInputDataStreamDecorator(std::unique_ptr<IInputDataStream> && input)
		: m_input(std::move(input))
	{
	}

	bool IsEOF() const override
	{
		return m_input->IsEOF();
	}

	uint8_t ReadByte() override
	{
		uint8_t byte;
		if (ReadBlock(&byte, 1u) == 0u)
		{
			throw std::ios_base::failure("failed to read byte from rle-compressed bytes stream");
		}
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		while (m_decompressed.size() < size_t(size))
		{
			ByteChunk chunk;
			auto bytesReadCount = m_input->ReadBlock(&chunk, 2u);
			if (bytesReadCount == 0u && m_input->IsEOF())
			{
				// Нечего читать дальше, это всё что мы можем записать dstBuffer
				break;
			}
			if (bytesReadCount == 1u || chunk.count == 0u)
			{
				// Такие ситуации не должны возникнуть в потоке данных сжатых этой программой
				throw std::runtime_error("corrupted compression");
			}
			for (uint8_t i = 0; i < chunk.count; ++i)
			{
				m_decompressed.push_back(chunk.byte);
			}
		}

		std::streamsize readBytesCount = 0u;
		uint8_t* destination = reinterpret_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; ++i)
		{
			if (m_decompressed.empty())
			{
				return readBytesCount;
			}
			*destination++ = m_decompressed.front();
			m_decompressed.pop_front();
			++readBytesCount;
		}
		return readBytesCount;
	}

private:
	std::unique_ptr<IInputDataStream> m_input;
	std::deque<uint8_t> m_decompressed;
};
