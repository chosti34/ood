#include "stdafx.h"
#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(const std::string& filePath)
	: m_fileStream(filePath, std::ofstream::binary)
{
	if (!m_fileStream)
	{
		throw std::runtime_error("failed to create file output stream");
	}
}

void FileOutputStream::WriteByte(uint8_t data)
{
	WriteBlock(std::addressof(data), 1);
}

void FileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const char* source = reinterpret_cast<const char*>(srcData);
	if (!m_fileStream.write(source, size))
	{
		throw std::ios_base::failure(
			"failed to write " + std::to_string(size) + " bytes to output file stream");
	}
}
