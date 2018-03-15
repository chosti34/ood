#pragma once
#include "IOutputDataStream.h"
#include <fstream>
#include <string>

class FileOutputStream : public IOutputDataStream
{
public:
	FileOutputStream(const std::string& filePath);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_fileStream;
};
