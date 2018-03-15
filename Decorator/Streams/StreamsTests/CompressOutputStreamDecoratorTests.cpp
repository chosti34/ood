#include "stdafx.h"
#include "../CompressOutputStreamDecorator.h"
#include "../FileOutputStream.h"
#include "FileUtilities.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(CompressOutputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(stream_can_compress_data_per_byte)
	{
		{
			auto output = std::make_unique<CompressOutputStreamDecorator>(
				std::make_unique<FileOutputStream>("some-non-existing-file.txt"));
			for (unsigned i = 0u; i < 100u; ++i)
			{
				output->WriteByte(0x35);
			}
			for (unsigned i = 0u; i < 255u; ++i)
			{
				output->WriteByte(0x36);
			}
			for (unsigned i = 0u; i < 3u; ++i)
			{
				output->WriteByte(0x36);
			}
		}
		const auto content = GetFileContent("some-non-existing-file.txt");
		std::vector<uint8_t> bytes(content.begin(), content.end());
		const std::vector<uint8_t> expected = { 0x64, 0x35, 0xFF, 0x36, 0x03, 0x36 };
		for (size_t i = 0; i < bytes.size(); ++i)
		{
			BOOST_CHECK_EQUAL(bytes[i], expected[i]);
		}
		RemoveFile("some-non-existing-file.txt");
	}

	BOOST_AUTO_TEST_CASE(stream_can_compress_data_per_byte_block)
	{
		{
			auto output = std::make_unique<CompressOutputStreamDecorator>(
				std::make_unique<FileOutputStream>("some-non-existing-file.txt"));
			std::vector<uint8_t> memory = { 0x45, 0x45, 0x45, 0x45, 0x56 };
			output->WriteBlock(memory.data(), memory.size());
		}
		const auto content = GetFileContent("some-non-existing-file.txt");
		std::vector<uint8_t> bytes(content.begin(), content.end());
		const std::vector<uint8_t> expected = { 0x04, 0x45, 0x01, 0x56 };
		for (size_t i = 0; i < bytes.size(); ++i)
		{
			BOOST_CHECK_EQUAL(bytes[i], expected[i]);
		}
		RemoveFile("some-non-existing-file.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
