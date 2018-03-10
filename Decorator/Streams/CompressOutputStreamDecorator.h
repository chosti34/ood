#pragma once
#include "IOutputDataStream.h"

#include <memory>
#include <vector>
#include <boost/optional.hpp>

// ƒекоратор дл€ выходного потока, тоже €вл€ющийс€ выходным потоком.
// —начала он производит компрессию данных простейшей вариацией RLE-алгоритма,
// затем записывает эти данные в выходной поток.
class CompressOutputStreamDecorator : public IOutputDataStream
{
	struct Chunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	CompressOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output)
		: m_output(std::move(output))
	{
	}

	~CompressOutputStreamDecorator()
	{
		Flush();
	}

	void WriteByte(uint8_t data) override
	{
		if (m_cache.empty())
		{
			m_cache.push_back(Chunk{ 1u, data });
		}
		else if (m_cache.back().byte == data && m_cache.back().count < 0xFF)
		{
			++m_cache.back().count;
		}
		else
		{
			if (m_cache.size() == MAX_CACHE_SIZE)
			{
				Flush();
			}
			m_cache.push_back(Chunk{ 1u, data });
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
	void Flush()
	{
		m_output->WriteBlock(m_cache.data(), sizeof(Chunk) * m_cache.size());
		m_cache.clear();
	}

	static const unsigned MAX_CACHE_SIZE = 10u;
	std::unique_ptr<IOutputDataStream> m_output;
	std::vector<Chunk> m_cache;
};
