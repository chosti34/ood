#include "stdafx.h"
#include "../FileOutputStream.h"
#include "FileUtilities.h"
#include <fstream>
#include <sstream>
#include <vector>

BOOST_AUTO_TEST_SUITE(FileOutputStreamTests)
	BOOST_AUTO_TEST_CASE(stream_can_write_one_byte_into_file)
	{
		{
			FileOutputStream strm("some-non-existing-file-path.txt");
			strm.WriteByte(0x2A);
		}
		BOOST_CHECK_EQUAL(std::string("*"), GetFileContent("some-non-existing-file-path.txt"));
		RemoveFile("some-non-existing-file-path.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_can_write_byte_block_into_file)
	{
		{
			const std::vector<uint8_t> content = { 0x32, 0x2B, 0x32, 0x2A, 0x32, 0x3D, 0x36 };
			FileOutputStream strm("some-non-existing-file-path.txt");
			strm.WriteBlock(content.data(), content.size());
		}
		BOOST_CHECK_EQUAL(std::string("2+2*2=6"), GetFileContent("some-non-existing-file-path.txt"));
		RemoveFile("some-non-existing-file-path.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
