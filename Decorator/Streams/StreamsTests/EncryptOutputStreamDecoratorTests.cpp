#include "stdafx.h"
#include "../EncryptOutputStreamDecorator.h"
#include "../FileOutputStream.h"
#include "../ByteEncodingTable.h"
#include "FileUtilities.h"
#include <vector>

BOOST_AUTO_TEST_SUITE(EncryptOutputStreamDecoratorTests)
	BOOST_AUTO_TEST_CASE(can_write_encrypted_data_to_output)
	{
		auto seed = static_cast<unsigned>(rand());
		const std::vector<uint8_t> bytes = { 0x36, 0x33, 0x35, 0x34 };
		{
			auto output = std::make_unique<EncryptOutputStreamDecorator>(
				std::make_unique<FileOutputStream>("some-file.txt"), seed);
			output->WriteByte(bytes[0]);
			output->WriteByte(bytes[1]);
			output->WriteBlock(bytes.data() + 2u, 2u);
		}
		{
			const std::string content = GetFileContent("some-file.txt");
			ByteEncodingTable table(seed);
			for (size_t i = 0; i < content.length(); ++i)
			{
				BOOST_CHECK_EQUAL(static_cast<uint8_t>(content[i]), table.EncodeByte(bytes[i]));
			}
		}
		RemoveFile("some-file.txt");
	}
BOOST_AUTO_TEST_SUITE_END()
