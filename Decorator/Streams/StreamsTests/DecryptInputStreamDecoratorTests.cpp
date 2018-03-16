#include "stdafx.h"
#include "../DecryptInputStreamDecorator.h"
#include "../ByteEncodingTable.h"
#include "../MemoryInputStream.h"

BOOST_AUTO_TEST_SUITE(DecryptInputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(can_read_and_decrypt_data)
	{
		const auto seed = static_cast<unsigned>(rand());
		const std::vector<uint8_t> data = { 0x34, 0x35, 0x36, 0x37, 0x38, 0x38 };
		{
			auto memory = data;
			auto input = std::make_unique<DecryptInputStreamDecorator>(
				std::make_unique<MemoryInputStream>(std::move(memory)), seed);

			BOOST_CHECK(!input->IsEOF());

			// reading per byte
			std::vector<uint8_t> decrypted(data.size());
			for (size_t i = 0; i < 3; ++i)
			{
				decrypted[i] = input->ReadByte();
			}

			// reading byte block
			auto read = input->ReadBlock(decrypted.data() + 3u, 3u);
			BOOST_CHECK_EQUAL(read, 3u);

			ByteEncodingTable table(seed);
			for (unsigned i = 0u; i < data.size(); ++i)
			{
				BOOST_CHECK_EQUAL(decrypted[i], table.DecodeByte(data[i]));
			}
		}
	}
BOOST_AUTO_TEST_SUITE_END()
