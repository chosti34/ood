#include "stdafx.h"
#include "../FileInputStream.h"

BOOST_AUTO_TEST_SUITE(FileInputStreamTests)
	BOOST_AUTO_TEST_CASE(stream_throws_exception_when_not_existing_file_path_is_specified)
	{
		BOOST_REQUIRE_THROW(FileInputStream("not-existing-file.txt"), std::runtime_error);
		{
			std::ofstream file("existing-file.txt");
			BOOST_REQUIRE_NO_THROW(FileInputStream("existing-file.txt"));
		}
		int removed = std::remove("existing-file.txt");
		BOOST_CHECK_EQUAL(removed, 0);
	}

	BOOST_AUTO_TEST_CASE(stream_reached_eof_automatically_when_empty_file_is_opened)
	{
		{
			std::ofstream file("empty.txt");
			FileInputStream strm("empty.txt");
			BOOST_CHECK(strm.IsEOF());
			BOOST_REQUIRE_THROW(strm.ReadByte(), std::ios_base::failure);
		}
		int removed = std::remove("empty.txt");
		BOOST_CHECK_EQUAL(removed, 0);
	}

	BOOST_AUTO_TEST_CASE(stream_can_correcly_read_whole_file_content_per_one_byte)
	{
		// TODO: implement this
	}

	BOOST_AUTO_TEST_CASE(stream_can_correctly_read_whole_content_per_byte_blocks)
	{
		// TODO: implement this
	}
BOOST_AUTO_TEST_SUITE_END()
