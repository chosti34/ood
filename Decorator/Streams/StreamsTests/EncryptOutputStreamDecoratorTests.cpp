#include "stdafx.h"
#include "../EncryptOutputStreamDecorator.h"
#include "../ByteEncodingTable.h"
#include "../MemoryOutputStream.h"

BOOST_AUTO_TEST_SUITE(EncryptOutputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(can_write_encrypted_data_to_output)
	{
		auto seed = static_cast<unsigned>(rand());
		const std::vector<uint8_t> bytes = { 0x36, 0x33, 0x35, 0x34 };
		std::vector<uint8_t> memory;
		{
			auto output = std::make_unique<EncryptOutputStreamDecorator>(
				std::make_unique<MemoryOutputStream>(memory), seed);

			output->WriteByte(bytes[0]);
			output->WriteByte(bytes[1]);
			output->WriteBlock(bytes.data() + 2u, 2u);
		}
		{
			ByteEncodingTable table(seed);
			for (size_t i = 0; i < memory.size(); ++i)
			{
				BOOST_CHECK_EQUAL(static_cast<uint8_t>(memory[i]), table.EncodeByte(bytes[i]));
			}
		}
	}
BOOST_AUTO_TEST_SUITE_END()
