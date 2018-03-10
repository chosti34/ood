#pragma once
#include "IOutputDataStream.h"
#include "ByteEncodingTable.h"
#include <memory>

class EncryptOutputStreamDecorator : public IOutputDataStream
{
public:
	EncryptOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output, unsigned seed)
		: m_output(std::move(output))
		, m_encodingTable(seed)
	{
	}

	virtual void WriteByte(uint8_t data) override
	{
		m_output->WriteByte(m_encodingTable.EncodeByte(data));
	}

	virtual void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(*source++);
		}
	}

private:
	std::unique_ptr<IOutputDataStream> m_output;
	ByteEncodingTable m_encodingTable;
};
