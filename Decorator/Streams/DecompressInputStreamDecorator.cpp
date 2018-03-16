#include "stdafx.h"
#include "DecompressInputStreamDecorator.h"

DecompressInputStreamDecorator::DecompressInputStreamDecorator(std::unique_ptr<IInputDataStream> && input)
	: m_input(std::move(input))
{
}

bool DecompressInputStreamDecorator::IsEOF() const
{
	return m_input->IsEOF() && m_decompressedBuffer.empty();
}

uint8_t DecompressInputStreamDecorator::ReadByte()
{
	uint8_t byte;
	if (ReadBlock(&byte, 1u) == 0u)
	{
		throw std::ios_base::failure("failed to read byte from rle compressed stream");
	}
	return byte;
}

std::streamsize DecompressInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	UnpackDataFromStreamAndFillBuffer(size);
	uint8_t* destination = reinterpret_cast<uint8_t*>(dstBuffer);

	std::streamsize read = 0u;
	for (std::streamsize i = 0; i < size; ++i)
	{
		if (m_decompressedBuffer.empty())
		{
			// «апросили данных больше чем есть в потоке
			return read;
		}
		*destination++ = m_decompressedBuffer.front();
		m_decompressedBuffer.pop_front();
		++read;
	}
	return read;
}

std::streamsize DecompressInputStreamDecorator::UnpackDataFromStreamAndFillBuffer(std::streamsize size)
{
	std::streamsize unpacked = 0u;
	while (std::streamsize(m_decompressedBuffer.size()) < size)
	{
		auto chunk = TryReadNextChunk();
		if (!chunk) // EOF
		{
			break;
		}
		m_decompressedBuffer.insert(m_decompressedBuffer.end(), chunk->count, chunk->byte);
		unpacked += chunk->count;
	}
	return unpacked;
}

boost::optional<ByteChunk> DecompressInputStreamDecorator::TryReadNextChunk()
{
	ByteChunk chunk;
	auto read = m_input->ReadBlock(&chunk, 2u);
	if (read == 0)
	{
		// „итать дальше некуда, достигли конца потока
		assert(m_input->IsEOF());
		return boost::none;
	}
	if (read == 1u || chunk.count == 0)
	{
		throw std::runtime_error("corrupted compression");
	}
	return chunk;
}
