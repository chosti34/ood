#include "stdafx.h"
#include "../FileInputStream.h"
#include "FileUtilities.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(FileInputStreamTests)
	BOOST_AUTO_TEST_CASE(stream_throws_exception_when_not_existing_file_path_is_specified)
	{
		BOOST_REQUIRE_THROW(FileInputStream("not-existing-file.txt"), std::runtime_error);
		{
			// Stream must free file so we have permission to delete it
			std::ofstream file("existing-file.txt");
			BOOST_REQUIRE_NO_THROW(FileInputStream("existing-file.txt"));
		}
		RemoveFile("existing-file.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_eof_flag_is_set_automatically_when_empty_file_is_opened)
	{
		{
			// Stream must free file so we have permission to delete it
			std::ofstream file("empty.txt");
			FileInputStream strm("empty.txt");
			BOOST_CHECK(strm.IsEOF());
			BOOST_REQUIRE_THROW(strm.ReadByte(), std::ios_base::failure);
		}
		RemoveFile("empty.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_can_correctly_read_whole_file_content_per_one_byte)
	{
		const std::vector<uint8_t> content = { 0xEF, 0xBB, 0xBF, 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x0A };
		{
			std::ofstream file("some-file-with-content.txt", std::ofstream::binary);
			for (auto byte : content)
			{
				file << byte;
			}
		}
		{
			FileInputStream strm("some-file-with-content.txt");
			for (auto byte : content)
			{
				BOOST_CHECK_EQUAL(byte, strm.ReadByte());
			}
			BOOST_CHECK(strm.IsEOF());
		}
		RemoveFile("some-file-with-content.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_can_correctly_read_whole_file_content_per_byte_blocks)
	{
		const std::vector<uint8_t> content = { 0xEF, 0xBB, 0xBF, 0x57, 0x4F, 0x52, 0x4C, 0x44, 0x0A };
		{
			std::ofstream file("some-file-with-content.txt", std::ofstream::binary);
			for (auto byte : content)
			{
				file << byte;
			}
		}
		{
			std::vector<uint8_t> memory(content.size());
			FileInputStream strm("some-file-with-content.txt");
			strm.ReadBlock(memory.data(), 9u);
			strm.ReadBlock(memory.data() + 9u, 1u);
			for (size_t i = 0; i < memory.size(); ++i)
			{
				BOOST_CHECK_EQUAL(content[i], memory[i]);
			}
			BOOST_CHECK(strm.IsEOF());
		}
		RemoveFile("some-file-with-content.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_throws_exception_when_user_tries_to_read_byte_but_there_is_no_more_left)
	{
		{
			const std::vector<uint8_t> content = { 0xFF };
			std::ofstream file("some-file-with-one-byte.txt", std::ofstream::binary);
			file << content.front();
		}
		{
			FileInputStream strm("some-file-with-one-byte.txt");
			auto byte = strm.ReadByte();
			BOOST_REQUIRE_THROW(strm.ReadByte(), std::ios_base::failure);
			BOOST_CHECK(strm.IsEOF());
		}
		RemoveFile("some-file-with-one-byte.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
