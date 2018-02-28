#pragma once
#include "IInputDataStream.h"
#include <fstream>
#include <string>

class FileInputStream : public IInputDataStream
{
public:
	FileInputStream(const std::string& filePath)
		: m_fileStream(filePath)
	{
		if (!m_fileStream)
		{
			throw std::runtime_error("failed to create file input stream");
		}
	}

	bool IsEOF() const override
	{
		return m_fileStream.eof();
	}

	uint8_t ReadByte() override
	{
		uint8_t byte;
		if (ReadBlock(std::addressof(byte), 1) == 0u)
		{
			throw std::ios_base::failure("failed to read byte from file input stream");
		}
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		char* buffer = reinterpret_cast<char*>(dstBuffer);
		if (!m_fileStream.read(buffer, size))
		{
			throw std::ios_base::failure("failed to read bytes from stream");
		}
		return m_fileStream.gcount();
	}

private:
	std::ifstream m_fileStream;
};
