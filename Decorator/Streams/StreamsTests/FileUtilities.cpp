#include "stdafx.h"
#include "FileUtilities.h"

void RemoveFile(const std::string & path)
{
	int removedStatus = std::remove(path.c_str());
	BOOST_CHECK_EQUAL(removedStatus, 0);
}

std::string GetFileContent(const std::string & path)
{
	std::ifstream file(path, std::ifstream::binary);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
