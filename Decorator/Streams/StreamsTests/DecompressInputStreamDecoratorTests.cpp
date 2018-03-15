#include "stdafx.h"
#include "../DecompressInputStreamDecorator.h"
#include "../FileInputStream.h"
#include "FileUtilities.h"

BOOST_AUTO_TEST_SUITE(DecompressInputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(throws_exception_on_corrupted_compression)
	{
		{
			std::ofstream file("some-file.txt", std::ofstream::binary);
			file << char(0x00);
		}
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(std::make_unique<FileInputStream>("some-file.txt"));
			std::vector<uint8_t> memory(6u);
			BOOST_REQUIRE_THROW(input->ReadBlock(memory.data(), memory.size()), std::runtime_error);
		}
		RemoveFile("some-file.txt");
	}

	BOOST_AUTO_TEST_CASE(can_decompress_data_per_one_byte)
	{
		{
			std::ofstream file("some-file.txt", std::ofstream::binary);
			file << uint8_t(5) << '*' << uint8_t(1) << "/";
		}
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(std::make_unique<FileInputStream>("some-file.txt"));
			std::string content;
			while (!input->IsEOF())
			{
				content += static_cast<char>(input->ReadByte());
			}
			BOOST_CHECK_EQUAL(content, std::string("*****/"));
		}
		RemoveFile("some-file.txt");
	}

	BOOST_AUTO_TEST_CASE(can_decompress_data_via_read_block_method)
	{
		{
			std::ofstream file("some-file.txt", std::ofstream::binary);
			file << uint8_t(1) << 'h' << uint8_t(1) << "e" << uint8_t(2) << 'l' << uint8_t(1) << 'o';
		}
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(std::make_unique<FileInputStream>("some-file.txt"));
			std::string content(5, 'a');
			input->ReadBlock(&content[0], content.size());
			BOOST_CHECK_EQUAL(content, std::string("hello"));
		}
		RemoveFile("some-file.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
