#include "stdafx.h"
#include "EncryptOutputStreamDecorator.h"

EncryptOutputStreamDecorator::EncryptOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output, unsigned seed)
	: m_output(std::move(output))
	, m_encodingTable(seed)
{
}

void EncryptOutputStreamDecorator::WriteByte(uint8_t data)
{
	m_output->WriteByte(m_encodingTable.EncodeByte(data));
}

void EncryptOutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* source = reinterpret_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(*source++);
	}
}
