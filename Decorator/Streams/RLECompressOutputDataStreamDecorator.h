#pragma once
#include "IOutputDataStream.h"
#include <memory>
#include <vector>
#include <boost/optional.hpp>

class RLECompressOutputDataStreamDecorator : public IOutputDataStream
{
	struct Chunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	RLECompressOutputDataStreamDecorator(std::unique_ptr<IOutputDataStream> && output)
		: m_output(std::move(output))
	{
	}

	~RLECompressOutputDataStreamDecorator()
	{
		m_output->WriteBlock(m_cache.data(), sizeof(Chunk) * m_cache.size());
	}

	void WriteByte(uint8_t data) override
	{
		if (m_cache.empty())
		{
			m_cache.push_back({ 1u, data });
		}
		else if (m_cache.back().byte == data && m_cache.back().count < 0xFF)
		{
			++m_cache.back().count;
		}
		else
		{
			m_cache.push_back({ 1u, data });
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(*source++);
		}
	}

private:
	std::unique_ptr<IOutputDataStream> m_output;
	std::vector<Chunk> m_cache;
};
