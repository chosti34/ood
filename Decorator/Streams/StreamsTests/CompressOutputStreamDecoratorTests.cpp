#include "stdafx.h"
#include "../CompressOutputStreamDecorator.h"
#include "../MemoryOutputStream.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(CompressOutputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(stream_can_compress_data_per_byte)
	{
		std::vector<uint8_t> memory;
		{
			auto output = std::make_unique<CompressOutputStreamDecorator>(
				std::make_unique<MemoryOutputStream>(memory));

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
		const std::vector<uint8_t> expected = { 0x64, 0x35, 0xFF, 0x36, 0x03, 0x36 };
		BOOST_CHECK(memory == expected);
	}

	BOOST_AUTO_TEST_CASE(stream_can_compress_data_per_byte_block)
	{
		std::vector<uint8_t> memory;
		{
			auto output = std::make_unique<CompressOutputStreamDecorator>(
				std::make_unique<MemoryOutputStream>(memory));

			std::vector<uint8_t> memory = { 0x45, 0x45, 0x45, 0x45, 0x56 };
			output->WriteBlock(memory.data(), memory.size());
		}
		const std::vector<uint8_t> expected = { 0x04, 0x45, 0x01, 0x56 };
		BOOST_CHECK(memory == expected);
	}
BOOST_AUTO_TEST_SUITE_END()
