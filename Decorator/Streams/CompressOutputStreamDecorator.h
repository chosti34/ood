#pragma once
#include "IOutputDataStream.h"

#include <memory>
#include <vector>
#include <boost/optional.hpp>

// ��������� ��� ��������� ������, ���� ���������� �������� �������.
// ������� �� ���������� ���������� ������ ���������� ��������� RLE-���������,
// ����� ���������� ��� ������ � �������� �����.
class CompressOutputStreamDecorator : public IOutputDataStream
{
	struct Chunk
	{
		uint8_t count;
		uint8_t byte;
	};

public:
	CompressOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output);

	~CompressOutputStreamDecorator();

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	void Flush();

	static const unsigned MAX_CACHE_SIZE;
	std::unique_ptr<IOutputDataStream> m_output;
	std::vector<Chunk> m_cache;
};
