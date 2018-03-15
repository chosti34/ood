#include "stdafx.h"
#include "../ByteEncodingTable.h"
#include <numeric>

namespace
{
using ByteLimits = std::numeric_limits<uint8_t>;

std::vector<unsigned> GenerateRandomSeeds(unsigned count)
{
	std::vector<unsigned> seeds;
	seeds.reserve(count);
	for (unsigned i = 0u; i < count; ++i)
	{
		seeds.push_back(static_cast<unsigned>(rand()));
	}
	return seeds;
}

std::vector<uint8_t> GenerateByteSequence()
{
	std::vector<uint8_t> bytes(256u);
	std::iota(bytes.begin(), bytes.end(), 0);
	return bytes;
}
}

BOOST_AUTO_TEST_SUITE(ByteEncodingTableTests)
	BOOST_AUTO_TEST_CASE(table_produce_encoded_bytes_that_can_be_decoded)
	{
		for (unsigned seed : GenerateRandomSeeds(5u))
		{
			ByteEncodingTable table(seed);
			for (uint8_t byte : GenerateByteSequence())
			{
				BOOST_CHECK_EQUAL(byte, table.DecodeByte(table.EncodeByte(byte)));
			}
		}
	}

	BOOST_AUTO_TEST_CASE(tables_produces_same_bytes_when_they_have_same_seeds)
	{
		for (unsigned seed : GenerateRandomSeeds(5u))
		{
			ByteEncodingTable table1(seed);
			ByteEncodingTable table2(seed);
			for (uint8_t byte : GenerateByteSequence())
			{
				BOOST_CHECK_EQUAL(table1.EncodeByte(byte), table2.EncodeByte(byte));
				BOOST_CHECK_EQUAL(table1.DecodeByte(byte), table2.DecodeByte(byte));
			}
		}
	}
BOOST_AUTO_TEST_SUITE_END()
