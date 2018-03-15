#include "stdafx.h"
#include "DecryptInputStreamDecorator.h"

DecryptInputStreamDecorator::DecryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && input, unsigned seed)
	: m_input(std::move(input))
	, m_encodingTable(seed)
{
}

bool DecryptInputStreamDecorator::IsEOF()const
{
	return m_input->IsEOF();
}

uint8_t DecryptInputStreamDecorator::ReadByte()
{
	return m_encodingTable.DecodeByte(m_input->ReadByte());
}

std::streamsize DecryptInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	std::streamsize readBytesCount = m_input->ReadBlock(dstBuffer, size);
	uint8_t* destination = reinterpret_cast<uint8_t*>(dstBuffer);
	for (std::streamsize i = 0; i < readBytesCount; ++i)
	{
		uint8_t& byte = *destination++;
		byte = m_encodingTable.DecodeByte(byte);
	}
	return readBytesCount;
}
