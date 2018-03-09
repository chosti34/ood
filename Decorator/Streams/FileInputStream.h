#pragma once
#include <fstream>
#include <string>
#include "IInputDataStream.h"

class FileInputStream : public IInputDataStream
{
public:
	FileInputStream(const std::string& filePath)
		: m_fileStream(filePath, std::ifstream::binary)
	{
		if (!m_fileStream)
		{
			throw std::runtime_error("failed to create file input stream");
		}
	}

	bool IsEOF() const override
	{
		return m_fileStream.peek() == EOF;
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
		char* destination = reinterpret_cast<char*>(dstBuffer);
		if (!m_fileStream.read(destination, size) && !m_fileStream.eof())
		{
			throw std::ios_base::failure(
				"failed to read " + std::to_string(size) + " bytes from file input stream");
		}
		return m_fileStream.gcount();
	}

private:
	mutable std::ifstream m_fileStream;
};
