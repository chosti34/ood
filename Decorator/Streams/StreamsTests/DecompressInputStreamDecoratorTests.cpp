#include "stdafx.h"
#include "../DecompressInputStreamDecorator.h"
#include "../MemoryInputStream.h"

BOOST_AUTO_TEST_SUITE(DecompressInputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(throws_exception_on_corrupted_compression)
	{
		std::vector<uint8_t> memory{0x00};
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(
				std::make_unique<MemoryInputStream>(std::move(memory)));

			std::vector<uint8_t> bytes(6u);
			BOOST_REQUIRE_THROW(input->ReadBlock(bytes.data(), bytes.size()), std::runtime_error);
		}
	}

	BOOST_AUTO_TEST_CASE(can_decompress_data_per_one_byte)
	{
		// 5 звёздочек и одна палочка
		std::vector<uint8_t> memory{ 0x05, 0x2A, 0x01, 0x2F };
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(
				std::make_unique<MemoryInputStream>(std::move(memory)));

			std::string content;
			while (!input->IsEOF())
			{
				content += static_cast<char>(input->ReadByte());
			}

			BOOST_CHECK_EQUAL(content, std::string("*****/"));
		}
	}

	BOOST_AUTO_TEST_CASE(can_decompress_data_via_read_block_method)
	{
		// hello
		std::vector<uint8_t> memory{ 0x01, 0x68, 0x01, 0x65, 0x02, 0x6C, 0x01, 0x6F };
		{
			auto input = std::make_unique<DecompressInputStreamDecorator>(
				std::make_unique<MemoryInputStream>(std::move(memory)));

			std::string content(5, 'a');
			input->ReadBlock(&content[0], content.size());
			BOOST_CHECK_EQUAL(content, std::string("hello"));
		}
	}
BOOST_AUTO_TEST_SUITE_END()
