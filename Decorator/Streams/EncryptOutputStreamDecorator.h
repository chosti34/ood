#pragma once
#include "IOutputDataStream.h"
#include "ByteEncodingTable.h"
#include <memory>

class EncryptOutputStreamDecorator : public IOutputDataStream
{
public:
	EncryptOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && output, unsigned seed);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::unique_ptr<IOutputDataStream> m_output;
	ByteEncodingTable m_encodingTable;
};
