#pragma once
#include "IOutputDataStream.h"
#include <fstream>
#include <string>

class FileOutputStream : public IOutputDataStream
{
public:
	FileOutputStream(const std::string& filePath)
		: m_fileStream(filePath, std::ofstream::binary)
	{
		if (!m_fileStream)
		{
			throw std::runtime_error("failed to create file output stream");
		}
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(std::addressof(data), 1);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const char* source = reinterpret_cast<const char*>(srcData);
		if (!m_fileStream.write(source, size))
		{
			throw std::ios_base::failure(
				"failed to write " + std::to_string(size) + " bytes to output file stream");
		}
	}

private:
	std::ofstream m_fileStream;
};
