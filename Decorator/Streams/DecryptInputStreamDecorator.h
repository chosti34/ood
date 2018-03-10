#pragma once
#include "IInputDataStream.h"
#include "ByteEncodingTable.h"
#include <memory>

class DecryptInputStreamDecorator : public IInputDataStream
{
public:
	DecryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && input, unsigned seed)
		: m_input(std::move(input))
		, m_encodingTable(seed)
	{
	}

	bool IsEOF() const override
	{
		return m_input->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_encodingTable.DecodeByte(m_input->ReadByte());
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
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

private:
	std::unique_ptr<IInputDataStream> m_input;
	ByteEncodingTable m_encodingTable;
};
