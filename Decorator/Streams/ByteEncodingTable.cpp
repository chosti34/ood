#include "stdafx.h"
#include "ByteEncodingTable.h"

#include <numeric>
#include <algorithm>
#include <random>

ByteEncodingTable::ByteEncodingTable(unsigned seed)
	: m_table(256u)
	, m_reversedTable(256u)
{
	std::iota(m_table.begin(), m_table.end(), uint8_t(0u));
	std::shuffle(m_table.begin(), m_table.end(), std::mt19937(seed));
	for (size_t i = 0; i < m_table.size(); ++i)
	{
		m_reversedTable[m_table[i]] = static_cast<uint8_t>(i);
	}
}

uint8_t ByteEncodingTable::EncodeByte(uint8_t byte)const
{
	// no need for checking index bounds since uint8_t in [0 .. 255]
	return m_table[byte];
}

uint8_t ByteEncodingTable::DecodeByte(uint8_t byte)const
{
	// no need for checking index bounds since uint8_t in [0 .. 255]
	return m_reversedTable[byte];
}
