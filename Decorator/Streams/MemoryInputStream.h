#pragma once
#include <vector>
#include "IInputDataStream.h"

class MemoryInputStream : public IInputDataStream
{
public:
	MemoryInputStream(std::vector<uint8_t> && memory);

	bool IsEOF() const noexcept override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t> m_memory;
	size_t m_offset;
};
