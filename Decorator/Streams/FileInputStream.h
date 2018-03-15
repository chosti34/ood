#pragma once
#include <fstream>
#include <string>
#include "IInputDataStream.h"

class FileInputStream : public IInputDataStream
{
public:
	FileInputStream(const std::string& filePath);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	mutable std::ifstream m_fileStream;
};
