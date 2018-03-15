#pragma once
#include "IInputDataStream.h"
#include "ByteEncodingTable.h"
#include <memory>

class DecryptInputStreamDecorator : public IInputDataStream
{
public:
	DecryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && input, unsigned seed);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::unique_ptr<IInputDataStream> m_input;
	ByteEncodingTable m_encodingTable;
};
