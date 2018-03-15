#include "stdafx.h"
#include "CompressOutputStreamDecorator.h"

const unsigned CompressOutputStreamDecorator::MAX_CACHE_SIZE = 10u;

CompressOutputStreamDecorator::CompressOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output)
	: m_output(std::move(output))
{
}

CompressOutputStreamDecorator::~CompressOutputStreamDecorator()
{
	Flush();
}

void CompressOutputStreamDecorator::WriteByte(uint8_t data)
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

void CompressOutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(*source++);
	}
}

void CompressOutputStreamDecorator::Flush()
{
	m_output->WriteBlock(m_cache.data(), sizeof(Chunk) * m_cache.size());
	m_cache.clear();
}
