#pragma once
#include "IInputDataStream.h"

#include <deque>
#include <memory>
#include <cassert>
#include <boost/optional/optional.hpp>

// Декоратор для входного потока, тоже являющийся входным потоком.
// Сначала считывает данные при помощи декорируемого объекта, затем
//  производит компрессию данных простейшей вариацией RLE-алгоритма.
class DecompressInputStreamDecorator : public IInputDataStream
{
	struct Chunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	DecompressInputStreamDecorator(std::unique_ptr<IInputDataStream> && input)
		: m_input(std::move(input))
	{
	}

	bool IsEOF() const override
	{
		return m_input->IsEOF() && m_decompressedBuffer.empty();
	}

	uint8_t ReadByte() override
	{
		uint8_t byte;
		if (ReadBlock(&byte, 1u) == 0u)
		{
			throw std::ios_base::failure("failed to read byte from rle compressed stream");
		}
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		UnpackDataFromStreamAndFillBuffer(size);
		uint8_t* destination = reinterpret_cast<uint8_t*>(dstBuffer);

		std::streamsize read = 0u;
		for (std::streamsize i = 0; i < size; ++i)
		{
			if (m_decompressedBuffer.empty())
			{
				// Запросили данных больше чем есть в потоке
				return read;
			}
			*destination++ = m_decompressedBuffer.front();
			m_decompressedBuffer.pop_front();
			++read;
		}
		return read;
	}

private:
	// Пытается распаковать size байт в исходное состояние и записать их в буфер.
	// Возвращает реальное количество распакованных байт.
	std::streamsize UnpackDataFromStreamAndFillBuffer(std::streamsize size)
	{
		std::streamsize unpacked = 0u;
		while (std::streamsize(m_decompressedBuffer.size()) < size)
		{
			auto chunk = TryReadNextChunk();
			if (!chunk) // EOF
			{
				break;
			}
			for (uint8_t i = 0; i < chunk->count; ++i)
			{
				m_decompressedBuffer.push_back(chunk->byte);
				++unpacked;
			}
		}
		return unpacked;
	}

	boost::optional<Chunk> TryReadNextChunk()
	{
		Chunk chunk;
		auto read = m_input->ReadBlock(&chunk, 2u);
		if (read == 0)
		{
			// Читать дальше некуда, достигли конца потока
			assert(m_input->IsEOF());
			return boost::none;
		}
		if (read == 1u || chunk.count == 0)
		{
			throw std::runtime_error("corrupted compression");
		}
		return chunk;
	}

	std::unique_ptr<IInputDataStream> m_input;
	std::deque<uint8_t> m_decompressedBuffer;
};
