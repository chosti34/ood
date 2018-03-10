#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

class ByteEncodingTable
{
public:
	ByteEncodingTable(unsigned seed)
		: m_table(256u)
		, m_reversedTable(256u)
	{
		std::iota(m_table.begin(), m_table.end(), 0u);
		std::shuffle(m_table.begin(), m_table.end(), std::mt19937(seed));
		for (size_t i = 0; i < m_table.size(); ++i)
		{
			m_reversedTable[m_table[i]] = static_cast<uint8_t>(i);
		}
	}

	uint8_t EncodeByte(uint8_t byte) const
	{
		return m_table[byte];
	}

	uint8_t DecodeByte(uint8_t byte) const
	{
		return m_reversedTable[byte];
	}

private:
	std::vector<uint8_t> m_table;
	std::vector<uint8_t> m_reversedTable;
};
