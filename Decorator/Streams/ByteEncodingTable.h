#pragma once
#include <vector>

class ByteEncodingTable
{
public:
	ByteEncodingTable(unsigned seed);

	uint8_t EncodeByte(uint8_t byte) const;
	uint8_t DecodeByte(uint8_t byte) const;

private:
	std::vector<uint8_t> m_table;
	std::vector<uint8_t> m_reversedTable;
};
