#include "stdafx.h"
#include "../DecryptInputStreamDecorator.h"
#include "../FileInputStream.h"
#include "../ByteEncodingTable.h"
#include "FileUtilities.h"

BOOST_AUTO_TEST_SUITE(DecryptInputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(can_read_and_decrypt_data)
	{
		const std::vector<uint8_t> data = { 0x34, 0x35, 0x36, 0x37, 0x38, 0x38 };
		unsigned seed = static_cast<unsigned>(rand());
		{
			std::ofstream file("some-file.txt");
			for (auto byte : data)
			{
				file << char(byte);
			}
		}
		{
			auto input = std::make_unique<DecryptInputStreamDecorator>(
				std::make_unique<FileInputStream>("some-file.txt"), seed);
			BOOST_CHECK(!input->IsEOF());

			std::vector<uint8_t> decrypted;
			decrypted.reserve(data.size());
			for (size_t i = 0; i < 3; ++i)
			{
				decrypted.push_back(input->ReadByte());
			}
			auto read = input->ReadBlock(decrypted.data() + 3u, 3u);
			BOOST_CHECK_EQUAL(read, 3u);

			ByteEncodingTable table(seed);
			for (unsigned i = 0u; i < data.size(); ++i)
			{
				BOOST_CHECK_EQUAL(decrypted[i], table.DecodeByte(data[i]));
			}
		}
		RemoveFile("some-file.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
